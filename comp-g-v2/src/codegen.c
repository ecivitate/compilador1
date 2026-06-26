#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "codegen.h"

/* helpers */

static void codegenFunction(CodeGen *cg, ASTNode *func);    
static void codegenFunctionList(CodeGen *cg, ASTNode *funcs);
static void emit(CodeGen *cg, const char *fmt, ...);

static void cgPushScope(CodeGen *cg);
static void cgPopScope(CodeGen *cg);
static CGEntry *cgLookup(CodeGen *cg, const char *name);

static void codegenAddress(CodeGen *cg, ASTNode *node);
static TipoVar codegenExpr(CodeGen *cg, ASTNode *node);
static void codegenNode(CodeGen *cg, ASTNode *node);
static void codegenBlock(CodeGen *cg, ASTNode *node);

static void codegenFunction(CodeGen *cg, ASTNode *func);
static void codegenFunctionList(CodeGen *cg, ASTNode *funcs);
static void codegenFunctionBlock(CodeGen *cg, ASTNode *block);

static void cgInsertFunc(CodeGen *cg, ASTNode *func) {
    CGEntry *e = calloc(1, sizeof(CGEntry));

    e->name      = strdup(func->lexeme);
    e->kind      = CG_FUNC;
    e->tipo      = func->tipo;
    e->isArray   = 0;
    e->arraySize = 0;
    e->offset    = 0;

    char buffer[256];
    snprintf(buffer, sizeof(buffer), "func_%s", func->lexeme);
    e->label = strdup(buffer);

    e->next = cg->scopeTop->entries;
    cg->scopeTop->entries = e;
}


static int countArgs(ASTNode *args) {
    int n = 0;
    for (ASTNode *a = args; a; a = a->next) n++;
    return n;
}

static char *makeGlobalLabel(const char *name) {
    char buffer[256];
    snprintf(buffer, sizeof(buffer), "global_%s", name);
    return strdup(buffer);
}

static void cgInsertGlobal(CodeGen *cg, ASTNode *decl) {
    CGEntry *e = calloc(1, sizeof(CGEntry));

    e->name      = strdup(decl->lexeme);
    e->kind      = CG_GLOBAL;
    e->tipo      = decl->tipo;
    e->isArray   = decl->isArray;
    e->arraySize = decl->arraySize;
    e->offset    = 0;
    e->label     = makeGlobalLabel(decl->lexeme);

    e->next = cg->scopeTop->entries;
    cg->scopeTop->entries = e;
}

static void emitGlobalDecls(CodeGen *cg, ASTNode *decls) {
    for (ASTNode *d = decls; d; d = d->next) {
        char *label = makeGlobalLabel(d->lexeme);

        if (d->isArray) {
            emit(cg, "%s: .space %d\n", label, 4 * d->arraySize);
        } else {
            emit(cg, "%s: .word 0\n", label);
        }

        free(label);
    }
}

static void cgInsertParam(CodeGen *cg, ASTNode *param, int position) {
    CGEntry *e = calloc(1, sizeof(CGEntry));

    e->name      = strdup(param->lexeme);
    e->kind      = CG_PARAM;
    e->tipo      = param->tipo;
    e->isArray   = param->isArray;
    e->arraySize = 0;
    e->offset    = 8 + 4 * position;
    e->label     = NULL;

    e->next = cg->scopeTop->entries;
    cg->scopeTop->entries = e;
}

static void codegenAddress(CodeGen *cg, ASTNode *node) {
    if (!node) return;

    switch (node->kind) {
        case NODE_IDENT: {
            CGEntry *e = cgLookup(cg, node->lexeme);

            if (e->kind == CG_GLOBAL) {
                emit(cg, "    la    $t2, %s          # address global %s\n",
                     e->label, node->lexeme);
            } else {
                emit(cg, "    addiu $t2, $fp, %d     # address %s\n",
                     e->offset, node->lexeme);
            }

            break;
        }

        case NODE_ARRAY_ACCESS: {
            CGEntry *e = cgLookup(cg, node->lexeme);

            /*
            Calcula o índice.
            Resultado fica em $t0.
            */
            codegenExpr(cg, node->child[0]);

            /*
            Cada posição ocupa 4 bytes.
            índice = índice * 4
            */
            emit(cg, "    sll   $t0, $t0, 2       # index * 4\n");

            if (e->kind == CG_GLOBAL) {
                emit(cg, "    la    $t2, %s          # base global array %s\n",
                    e->label, node->lexeme);
            } else if (e->kind == CG_PARAM && e->isArray) {
                
                // Parâmetro vetor é passado por referência.
                // O slot do parâmetro contém o endereço base.
                
                emit(cg, "    lw    $t2, %d($fp)     # base param array %s\n",
                    e->offset, node->lexeme);
            } else {
                
               // Vetor local.
                
                emit(cg, "    addiu $t2, $fp, %d     # base local array %s\n",
                    e->offset, node->lexeme);
            }

            emit(cg, "    addu  $t2, $t2, $t0     # address array element\n");

            break;
        }

        default:
            emit(cg, "    # ERRO INTERNO: lvalue invalido no codegenAddress\n");
            break;
    }
}

static void codegenArg(CodeGen *cg, ASTNode *arg) {
    if (arg->kind == NODE_IDENT) {
        CGEntry *e = cgLookup(cg, arg->lexeme);

        if (e && e->isArray) {
            /*
              Passa endereço base do vetor.
            */
            if (e->kind == CG_GLOBAL) {
                emit(cg, "    la    $t0, %s          # arg array global\n", e->label);
            } else if (e->kind == CG_PARAM) {
                emit(cg, "    lw    $t0, %d($fp)     # arg array param\n", e->offset);
            } else {
                emit(cg, "    addiu $t0, $fp, %d     # arg array local\n", e->offset);
            }

            emit(cg, "    addiu $sp, $sp, -4\n");
            emit(cg, "    sw    $t0, 0($sp)\n");
            return;
        }
    }

    codegenExpr(cg, arg);
    emit(cg, "    addiu $sp, $sp, -4\n");
    emit(cg, "    sw    $t0, 0($sp)\n");
}

static void codegenCallArgsReverse(CodeGen *cg, ASTNode *arg) {
    if (!arg) return;

    codegenCallArgsReverse(cg, arg->next);
    codegenArg(cg, arg);
}

static void codegenCallArgs(CodeGen *cg, ASTNode *args) {
    codegenCallArgsReverse(cg, args);
}

static int cgTypeSize(ASTNode *decl) {
    if (decl->isArray) {
        return 4 * decl->arraySize;
    }

    return 4;
}

static void emit(CodeGen *cg, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(cg->out, fmt, ap);
    va_end(ap);
}

/* Push $t0 onto the expression-evaluation stack */
static void pushT0(CodeGen *cg) {
    emit(cg, "    addiu $sp, $sp, -4\n");
    emit(cg, "    sw    $t0, 0($sp)        # push\n");
}

/* Pop top of expression-evaluation stack into $t1 */
static void popT1(CodeGen *cg) {
    emit(cg, "    lw    $t1, 0($sp)        # pop to $t1\n");
    emit(cg, "    addiu $sp, $sp, 4\n");
}

/* codegen symbol table */

static void cgPushScope(CodeGen *cg) {
    CGScope *s = calloc(1, sizeof(CGScope));
    s->prev      = cg->scopeTop;
    cg->scopeTop = s;
}

static void cgPopScope(CodeGen *cg) {
    if (!cg->scopeTop) return;
    CGScope  *s = cg->scopeTop;
    CGEntry  *e = s->entries;
    while (e) {
        CGEntry *nx = e->next;

        free(e->name);
        free(e->label);
        free(e);

        e = nx;
    }
    cg->scopeTop = s->prev;
    free(s);
}


static void cgInsertLocal(CodeGen *cg, ASTNode *decl) {
    int size = cgTypeSize(decl);

    cg->nextOffset -= size;

    CGEntry *e = calloc(1, sizeof(CGEntry));
    e->name      = strdup(decl->lexeme);
    e->kind      = CG_LOCAL;
    e->tipo      = decl->tipo;
    e->isArray   = decl->isArray;
    e->arraySize = decl->arraySize;
    e->offset    = cg->nextOffset;
    e->label     = NULL;

    e->next = cg->scopeTop->entries;
    cg->scopeTop->entries = e;

    cg->scopeTop->scopeSize += size;
}

static CGEntry *cgLookup(CodeGen *cg, const char *name) {
    for (CGScope *s = cg->scopeTop; s; s = s->prev)
        for (CGEntry *e = s->entries; e; e = e->next)
            if (strcmp(e->name, name) == 0) return e;
    return NULL;
}

/* string pre-pass */

static void collectStrings(CodeGen *cg, ASTNode *node) {
    if (!node) return;
    if (node->kind == NODE_CADEIA) {
        if (cg->stringCount < MAX_STRINGS) {
            cg->strings[cg->stringCount].node = node;
            cg->strings[cg->stringCount].id   = cg->stringCount;
            cg->stringCount++;
        }
        return; /* no children on CADEIA */
    }
    for (int i = 0; i < 3; i++) collectStrings(cg, node->child[i]);
    collectStrings(cg, node->next);
}

static int stringId(CodeGen *cg, ASTNode *node) {
    for (int i = 0; i < cg->stringCount; i++)
        if (cg->strings[i].node == node) return cg->strings[i].id;
    return -1;
}

/* character-constant parser */

static int parseCarconst(const char *lex) {
    /* lexeme is 'x' or '\e' */
    if (lex[1] == '\\') {
        switch (lex[2]) {
            case 'n':  return 10;
            case 't':  return  9;
            case 'r':  return 13;
            case '\'': return 39;
            case '"':  return 34;
            case '\\': return 92;
        }
    }
    return (unsigned char)lex[1];
}

static void codegenFunctionList(CodeGen *cg, ASTNode *funcs) {
    for (ASTNode *f = funcs; f; f = f->next) {
        codegenFunction(cg, f);
    }
}

static void codegenFunctionBlock(CodeGen *cg, ASTNode *block) {
    if (!block) return;

    int savedOffset = cg->nextOffset;

    /*
      Não faz cgPushScope aqui.
      Usa o escopo atual, que já tem os parâmetros.
    */
    int localSizeBefore = cg->scopeTop->scopeSize;

    for (ASTNode *d = block->child[0]; d; d = d->next) {
        cgInsertLocal(cg, d);
    }

    int localSize = cg->scopeTop->scopeSize - localSizeBefore;

    if (localSize > 0) {
        emit(cg, "    addiu $sp, $sp, -%d    # function locals\n", localSize);
    }

    for (ASTNode *c = block->child[1]; c; c = c->next) {
        codegenNode(cg, c);
    }

    /*
      Não precisa desalocar locais aqui se o epílogo faz:
          move $sp, $fp
      Mas pode manter organizado se quiser.
    */
    cg->nextOffset = savedOffset;
}

static void codegenFunction(CodeGen *cg, ASTNode *func) {
    int savedOffset = cg->nextOffset;
    char savedEnd[128];

    strcpy(savedEnd, cg->currentFunctionEnd);
    snprintf(cg->currentFunctionEnd, sizeof(cg->currentFunctionEnd),
             "func_%s_end", func->lexeme);

    cg->nextOffset = 0;

    emit(cg, "\nfunc_%s:\n", func->lexeme);

    /*
      Prólogo.
    */
    emit(cg, "    addiu $sp, $sp, -8\n");
    emit(cg, "    sw    $fp, 0($sp)\n");
    emit(cg, "    sw    $ra, 4($sp)\n");
    emit(cg, "    move  $fp, $sp\n");

    /*
      Escopo da função.
    */
    cgPushScope(cg);

    /*
      Insere parâmetros.
    */
    int pos = 0;
    for (ASTNode *p = func->child[0]; p; p = p->next) {
        cgInsertParam(cg, p, pos);
        pos++;
    }

    /*
      O bloco externo da função deve usar esse mesmo escopo,
      porque os parâmetros já estão nele.
      Então não chame codegenBlock direto se ele criar outro escopo
      para as declarações externas.
    */
    codegenFunctionBlock(cg, func->child[1]);

    emit(cg, "%s:\n", cg->currentFunctionEnd);

    /*
      Epílogo.
    */
    emit(cg, "    move  $sp, $fp\n");
    emit(cg, "    lw    $fp, 0($sp)\n");
    emit(cg, "    lw    $ra, 4($sp)\n");
    emit(cg, "    addiu $sp, $sp, 8\n");
    emit(cg, "    jr    $ra\n");

    cgPopScope(cg);

    cg->nextOffset = savedOffset;
    strcpy(cg->currentFunctionEnd, savedEnd);
}



/* expression code generation (result always in $t0) */

static TipoVar codegenExpr(CodeGen *cg, ASTNode *node) {
    if (!node) return TIPO_NENHUM;

    switch (node->kind) {

        /* integer constant */
        case NODE_INTCONST:
            emit(cg, "    li    $t0, %s          # intconst\n", node->lexeme);
            return TIPO_INT;

        /* character constant */
        case NODE_CARCONST:
            emit(cg, "    li    $t0, %d          # carconst %s\n",
                 parseCarconst(node->lexeme), node->lexeme);
            return TIPO_CAR;

        /* identifier */
        case NODE_IDENT: {
            CGEntry *e = cgLookup(cg, node->lexeme);

            if (e->isArray) {
                /*
                Usar vetor inteiro como expressão comum não deveria passar
                pelo semântico, exceto em casos especiais como argumento.
                Aqui, como fallback, carregamos o endereço base.
                */
                if (e->kind == CG_GLOBAL) {
                    emit(cg, "    la    $t0, %s          # array address %s\n",
                        e->label, node->lexeme);
                } else if (e->kind == CG_PARAM) {
                    emit(cg, "    lw    $t0, %d($fp)     # param array address %s\n",
                        e->offset, node->lexeme);
                } else {
                    emit(cg, "    addiu $t0, $fp, %d     # local array address %s\n",
                        e->offset, node->lexeme);
                }

                return e->tipo;
            }

            codegenAddress(cg, node);
            emit(cg, "    lw    $t0, 0($t2)       # load %s\n", node->lexeme);

            return e->tipo;
        }

        /* assignment (also an expression) */
        case NODE_ATRIB: {
            /*
            Primeiro calcula o valor.
            Resultado em $t0.
            */
            TipoVar t = codegenExpr(cg, node->child[1]);

            /*
            Salva o valor, porque codegenAddress pode usar $t0
            para calcular índice de vetor.
            */
            pushT0(cg);

            /*
            Calcula endereço do destino em $t2.
            */
            codegenAddress(cg, node->child[0]);

            /*
            Recupera valor em $t1 e armazena no endereço.
            */
            popT1(cg);
            emit(cg, "    sw    $t1, 0($t2)       # assignment\n");

            /*
            Como atribuição também é expressão, deixa valor em $t0.
            */
            emit(cg, "    move  $t0, $t1\n");

            return t;
        }

        /* unary op */
        case NODE_UNOP: {
            TipoVar t = codegenExpr(cg, node->child[0]);
            if (node->lexeme[0] == '-') {
                emit(cg, "    sub   $t0, $zero, $t0  # negate\n");
            } else { /* '!' */
                emit(cg, "    seq   $t0, $t0, $zero  # logical not\n");
                t = TIPO_INT;
            }
            return t;
        }

        /* binary op */
        case NODE_BINOP: {
            TipoVar lt = codegenExpr(cg, node->child[0]);
            pushT0(cg);
            TipoVar rt = codegenExpr(cg, node->child[1]);
            popT1(cg);
            /* $t1 = left, $t0 = right */
            const char *op = node->lexeme;

            if      (!strcmp(op, "+"))  emit(cg, "    add   $t0, $t1, $t0   # +\n");
            else if (!strcmp(op, "-"))  emit(cg, "    sub   $t0, $t1, $t0   # -\n");
            else if (!strcmp(op, "*"))  emit(cg, "    mul   $t0, $t1, $t0   # *\n");
            else if (!strcmp(op, "/"))  emit(cg, "    div   $t0, $t1, $t0   # /\n");
            else if (!strcmp(op, "<"))  emit(cg, "    slt   $t0, $t1, $t0   # <\n");
            else if (!strcmp(op, ">"))  emit(cg, "    slt   $t0, $t0, $t1   # >\n");
            else if (!strcmp(op, "<=")) emit(cg, "    sle   $t0, $t1, $t0   # <=\n");
            else if (!strcmp(op, ">=")) emit(cg, "    sge   $t0, $t1, $t0   # >=\n");
            else if (!strcmp(op, "==")) emit(cg, "    seq   $t0, $t1, $t0   # ==\n");
            else if (!strcmp(op, "!=")) emit(cg, "    sne   $t0, $t1, $t0   # !=\n");
            else if (!strcmp(op, "||")) {
                emit(cg, "    sne   $t1, $t1, $zero  # left != 0\n");
                emit(cg, "    sne   $t0, $t0, $zero  # right != 0\n");
                emit(cg, "    or    $t0, $t1, $t0    # logical or\n");
            }
            else if (!strcmp(op, "&")) {
                emit(cg, "    sne   $t1, $t1, $zero  # left != 0\n");
                emit(cg, "    sne   $t0, $t0, $zero  # right != 0\n");
                emit(cg, "    and   $t0, $t1, $t0    # logical and\n");
            }

            /* comparisons/logical produce int */
            if (!strcmp(op,"<") || !strcmp(op,">") || !strcmp(op,"<=") ||
                !strcmp(op,">=")|| !strcmp(op,"==")|| !strcmp(op,"!=") ||
                !strcmp(op,"||")|| !strcmp(op,"&"))
                return TIPO_INT;
            return (lt != TIPO_NENHUM) ? lt : rt;
        }

        case NODE_ARRAY_ACCESS: {
            CGEntry *e = cgLookup(cg, node->lexeme);

            codegenAddress(cg, node);
            emit(cg, "    lw    $t0, 0($t2)       # load %s[index]\n",
                node->lexeme);

            return e->tipo;
        }

        case NODE_CALL: {
            CGEntry *f = cgLookup(cg, node->lexeme);
            int argc = countArgs(node->child[0]);

            codegenCallArgs(cg, node->child[0]);

            emit(cg, "    jal   func_%s           # call %s\n",
                node->lexeme, node->lexeme);

            if (argc > 0) {
                emit(cg, "    addiu $sp, $sp, %d      # pop args\n", 4 * argc);
            }

            emit(cg, "    move  $t0, $v0          # call result\n");

            return f ? f->tipo : TIPO_INT;
        }

        

        default:
            return TIPO_NENHUM;
    }
}

/* control flow */

static void codegenSe(CodeGen *cg, ASTNode *node) {
    int id = cg->labelCount++;

    /* evaluate condition to $t0 */
    codegenExpr(cg, node->child[0]);

    if (node->child[2]) {
        /* se … entao … senao … fimse */
        emit(cg, "    beq   $t0, $zero, se_else_%d  # if false go to else\n", id);
        codegenNode(cg, node->child[1]);                /* then branch */
        emit(cg, "    j     se_fim_%d               # skip else\n", id);
        emit(cg, "se_else_%d:\n", id);
        codegenNode(cg, node->child[2]);                /* else branch */
        emit(cg, "se_fim_%d:\n", id);
    } else {
        /* se … entao … fimse */
        emit(cg, "    beq   $t0, $zero, se_fim_%d   # if false go to end\n", id);
        codegenNode(cg, node->child[1]);                /* then branch */
        emit(cg, "se_fim_%d:\n", id);
    }
}

static void codegenEnquanto(CodeGen *cg, ASTNode *node) {
    int id = cg->labelCount++;

    emit(cg, "enq_%d:\n", id);
    codegenExpr(cg, node->child[0]);                    /* condition to $t0 */
    emit(cg, "    beq   $t0, $zero, enq_fim_%d    # if false go to exit loop\n", id);
    codegenNode(cg, node->child[1]);                    /* body */
    emit(cg, "    j     enq_%d                    # back to test\n", id);
    emit(cg, "enq_fim_%d:\n", id);
}

/* statement dispatcher (stubs for LEIA/ESCREVA/NOVALINHA remain)*/

static void codegenNode(CodeGen *cg, ASTNode *node) {
    if (!node) return;
    switch (node->kind) {
        case NODE_ATRIB:
        case NODE_BINOP:
        case NODE_UNOP:
        case NODE_IDENT:
        case NODE_INTCONST:
        case NODE_CARCONST:
            codegenExpr(cg, node);
            break;
        case NODE_BLOCK:
            codegenBlock(cg, node);
            break;
        case NODE_SE:
            codegenSe(cg, node);
            break;
        case NODE_ENQUANTO:
            codegenEnquanto(cg, node);
            break;
        case NODE_NOVALINHA:
            emit(cg, "    li    $a0, 10            # '\\n'\n");
            emit(cg, "    li    $v0, 11            # print char\n");
            emit(cg, "    syscall\n");
            break;

        case NODE_LEIA: {
            ASTNode *dest = node->child[0];

            /*
            Descobrir o tipo do destino.
            Para x, busca x.
            Para v[i], busca v.
            */
            const char *name = NULL;

            if (dest->kind == NODE_IDENT || dest->kind == NODE_ARRAY_ACCESS) {
                name = dest->lexeme;
            }

            CGEntry *e = cgLookup(cg, name);

            if (e->tipo == TIPO_INT) {
                emit(cg, "    li    $v0, 5            # read int\n");
                emit(cg, "    syscall\n");
            } else {
                emit(cg, "    li    $v0, 12           # read char\n");
                emit(cg, "    syscall\n");
            }

            /*
            Salva valor lido porque codegenAddress pode usar $t0.
            Aqui o valor está em $v0.
            */
            emit(cg, "    move  $t0, $v0\n");
            pushT0(cg);

            codegenAddress(cg, dest);

            popT1(cg);
            emit(cg, "    sw    $t1, 0($t2)       # leia store\n");

            break;
        }

        case NODE_ESCREVA: {
            ASTNode *arg = node->child[0];
            if (arg->kind == NODE_CADEIA) {
                int sid = stringId(cg, arg);
                emit(cg, "    la    $a0, str_%d         # string literal\n", sid);
                emit(cg, "    li    $v0, 4             # print string\n");
                emit(cg, "    syscall\n");
            } else {
                TipoVar t = codegenExpr(cg, arg);
                emit(cg, "    move  $a0, $t0\n");
                if (t == TIPO_CAR) {
                    emit(cg, "    li    $v0, 11            # print char\n");
                } else {
                    emit(cg, "    li    $v0, 1             # print int\n");
                }
                emit(cg, "    syscall\n");
            }
            break;
        }

        case NODE_ARRAY_ACCESS:
        case NODE_CALL:
            codegenExpr(cg, node);
            break;
        
        case NODE_RETORNE:
            codegenExpr(cg, node->child[0]);
            emit(cg, "    move  $v0, $t0          # return value\n");
            emit(cg, "    j     %s                # return\n", cg->currentFunctionEnd);
            break;


        default:
            emit(cg, "    # unhandled node kind %d\n", node->kind);
            break;
    }
}

static void codegenBlock(CodeGen *cg, ASTNode *node) {
    int savedOffset = cg->nextOffset;
    int hasDecls = (node->child[0] != NULL);

    if (hasDecls) {
        cgPushScope(cg);

        for (ASTNode *d = node->child[0]; d; d = d->next) {
            cgInsertLocal(cg, d);
        }

        emit(cg, "    addiu $sp, $sp, -%d    # enter scope\n",
             cg->scopeTop->scopeSize);
    }

    for (ASTNode *c = node->child[1]; c; c = c->next) {
        codegenNode(cg, c);
    }

    if (hasDecls) {
        emit(cg, "    addiu $sp, $sp, %d     # exit scope\n",
             cg->scopeTop->scopeSize);

        cgPopScope(cg);
        cg->nextOffset = savedOffset;
    }
}

/* top-level entry point */

void codegenProgram(ASTNode *root, FILE *out) {
    CodeGen cg = {0};
    cg.out        = out;
    cg.nextOffset = 0;
    cg.currentFunctionEnd[0] = '\0';

    collectStrings(&cg, root);

    fprintf(out, "# Gerado pelo compilador G-V2\n");
    fprintf(out, "    .data\n");

    
      //Strings.
    
    for (int i = 0; i < cg.stringCount; i++) {
        fprintf(out, "str_%d:  .asciiz %s\n",
                i,
                cg.strings[i].node->lexeme);
    }

    
      //Globais.
    
    if (root && root->kind == NODE_PROGRAM) {
        emitGlobalDecls(&cg, root->child[0]);
    }

    fprintf(out, "\n    .text\n");
    fprintf(out, "    .globl main\n");

    /*
      Escopo global do codegen.
      Aqui entram as globais para cgLookup encontrar depois.
    */
    cgPushScope(&cg);

    if (root && root->kind == NODE_PROGRAM) {
        for (ASTNode *d = root->child[0]; d; d = d->next) {
            cgInsertGlobal(&cg, d);
        }

        for (ASTNode *f = root->child[1]; f; f = f->next) {
            cgInsertFunc(&cg, f);
        }
        
        codegenFunctionList(&cg, root->child[1]);

        
          //Gera main.
        
        fprintf(out, "\nmain:\n");
        fprintf(out, "    move  $fp, $sp          # fix frame pointer\n");

        cg.nextOffset = 0;
        codegenBlock(&cg, root->child[2]);

        fprintf(out, "    li    $v0, 10           # exit\n");
        fprintf(out, "    syscall\n");
    }

    cgPopScope(&cg);
}
