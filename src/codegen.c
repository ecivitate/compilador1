#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "codegen.h"

/* ── helpers ────────────────────────────────────────────────── */

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
    emit(cg, "    lw    $t1, 0($sp)        # pop → $t1\n");
    emit(cg, "    addiu $sp, $sp, 4\n");
}

/* ── codegen symbol table ────────────────────────────────────── */

static void cgPushScope(CodeGen *cg) {
    CGScope *s = calloc(1, sizeof(CGScope));
    s->prev      = cg->scopeTop;
    cg->scopeTop = s;
}

static void cgPopScope(CodeGen *cg) {
    if (!cg->scopeTop) return;
    CGScope  *s = cg->scopeTop;
    CGEntry  *e = s->entries;
    while (e) { CGEntry *nx = e->next; free(e->name); free(e); e = nx; }
    cg->scopeTop = s->prev;
    free(s);
}

static void cgInsert(CodeGen *cg, const char *name, TipoVar tipo) {
    cg->nextOffset -= 4;
    CGEntry *e  = calloc(1, sizeof(CGEntry));
    e->name     = strdup(name);
    e->offset   = cg->nextOffset;
    e->tipo     = tipo;
    e->next     = cg->scopeTop->entries;
    cg->scopeTop->entries = e;
}

static CGEntry *cgLookup(CodeGen *cg, const char *name) {
    for (CGScope *s = cg->scopeTop; s; s = s->prev)
        for (CGEntry *e = s->entries; e; e = e->next)
            if (strcmp(e->name, name) == 0) return e;
    return NULL;
}

/* ── string pre-pass ─────────────────────────────────────────── */

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

/* ── character-constant parser ───────────────────────────────── */

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

/* ── forward declarations ────────────────────────────────────── */

static TipoVar codegenExpr(CodeGen *cg, ASTNode *node);
static void    codegenNode(CodeGen *cg, ASTNode *node);
static void    codegenBlock(CodeGen *cg, ASTNode *node);

/* ── expression code generation (result always in $t0) ───────── */

static TipoVar codegenExpr(CodeGen *cg, ASTNode *node) {
    if (!node) return TIPO_NENHUM;

    switch (node->kind) {

        /* ── integer constant ── */
        case NODE_INTCONST:
            emit(cg, "    li    $t0, %s          # intconst\n", node->lexeme);
            return TIPO_INT;

        /* ── character constant ── */
        case NODE_CARCONST:
            emit(cg, "    li    $t0, %d          # carconst %s\n",
                 parseCarconst(node->lexeme), node->lexeme);
            return TIPO_CAR;

        /* ── identifier ── */
        case NODE_IDENT: {
            CGEntry *e = cgLookup(cg, node->lexeme);
            emit(cg, "    lw    $t0, %d($fp)     # load %s\n",
                 e->offset, node->lexeme);
            return e->tipo;
        }

        /* ── assignment (also an expression) ── */
        case NODE_ATRIB: {
            CGEntry *e = cgLookup(cg, node->lexeme);
            TipoVar  t = codegenExpr(cg, node->child[0]);
            emit(cg, "    sw    $t0, %d($fp)     # store %s\n",
                 e->offset, node->lexeme);
            return t;
        }

        /* ── unary op ── */
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

        /* ── binary op ── */
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
            else if (!strcmp(op, "||")) emit(cg, "    or    $t0, $t1, $t0   # ||\n");
            else if (!strcmp(op, "&"))  emit(cg, "    and   $t0, $t1, $t0   # &\n");

            /* comparisons/logical produce int */
            if (!strcmp(op,"<") || !strcmp(op,">") || !strcmp(op,"<=") ||
                !strcmp(op,">=")|| !strcmp(op,"==")|| !strcmp(op,"!=") ||
                !strcmp(op,"||")|| !strcmp(op,"&"))
                return TIPO_INT;
            return (lt != TIPO_NENHUM) ? lt : rt;
        }

        default:
            return TIPO_NENHUM;
    }
}

/* ── control flow ────────────────────────────────────────────── */

static void codegenSe(CodeGen *cg, ASTNode *node) {
    int id = cg->labelCount++;

    /* evaluate condition → $t0 */
    codegenExpr(cg, node->child[0]);

    if (node->child[2]) {
        /* se … entao … senao … fimse */
        emit(cg, "    beq   $t0, $zero, se_else_%d  # if false → else\n", id);
        codegenNode(cg, node->child[1]);                /* then branch */
        emit(cg, "    j     se_fim_%d               # skip else\n", id);
        emit(cg, "se_else_%d:\n", id);
        codegenNode(cg, node->child[2]);                /* else branch */
        emit(cg, "se_fim_%d:\n", id);
    } else {
        /* se … entao … fimse */
        emit(cg, "    beq   $t0, $zero, se_fim_%d   # if false → end\n", id);
        codegenNode(cg, node->child[1]);                /* then branch */
        emit(cg, "se_fim_%d:\n", id);
    }
}

static void codegenEnquanto(CodeGen *cg, ASTNode *node) {
    int id = cg->labelCount++;

    emit(cg, "enq_%d:\n", id);
    codegenExpr(cg, node->child[0]);                    /* condition → $t0 */
    emit(cg, "    beq   $t0, $zero, enq_fim_%d    # if false → exit loop\n", id);
    codegenNode(cg, node->child[1]);                    /* body */
    emit(cg, "    j     enq_%d                    # back to test\n", id);
    emit(cg, "enq_fim_%d:\n", id);
}

/* ── statement dispatcher (stubs for LEIA/ESCREVA/NOVALINHA remain) ── */

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
            CGEntry *e = cgLookup(cg, node->lexeme);
            if (e->tipo == TIPO_INT) {
                emit(cg, "    li    $v0, 5             # read int\n");
                emit(cg, "    syscall\n");
            } else {
                emit(cg, "    li    $v0, 12            # read char\n");
                emit(cg, "    syscall\n");
            }
            emit(cg, "    sw    $v0, %d($fp)     # store → %s\n",
                 e->offset, node->lexeme);
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

        default:
            emit(cg, "    # unhandled node kind %d\n", node->kind);
            break;
    }
}

static void codegenBlock(CodeGen *cg, ASTNode *node) {
    int hasDecls = (node->child[0] != NULL);
    int n = 0;
    if (hasDecls) {
        cgPushScope(cg);
        for (ASTNode *d = node->child[0]; d; d = d->next) {
            cgInsert(cg, d->lexeme, d->tipo);
            n++;
        }
        emit(cg, "    addiu $sp, $sp, -%d    # enter scope (%d var%s)\n",
             4*n, n, n==1?"":"s");
    }
    for (ASTNode *c = node->child[1]; c; c = c->next)
        codegenNode(cg, c);
    if (hasDecls) {
        emit(cg, "    addiu $sp, $sp, %d     # exit scope\n", 4*n);
        cgPopScope(cg);
    }
}

/* ── top-level entry point ───────────────────────────────────── */

void codegenProgram(ASTNode *root, FILE *out) {
    CodeGen cg = {0};
    cg.out        = out;
    cg.nextOffset = 0;

    /* pass 1: collect all string literals */
    collectStrings(&cg, root);

    /* write .data section */
    fprintf(out, "# Gerado pelo compilador G-V1\n");
    fprintf(out, "    .data\n");
    for (int i = 0; i < cg.stringCount; i++) {
        /* lexeme already includes surrounding quotes */
        fprintf(out, "str_%d:  .asciiz %s\n", i, cg.strings[i].node->lexeme);
    }

    /* write .text section */
    fprintf(out, "\n    .text\n");
    fprintf(out, "    .globl main\n");
    fprintf(out, "main:\n");
    fprintf(out, "    move  $fp, $sp          # fix frame pointer\n");

    /* pass 2: generate code (root is NODE_PROGRAM → child[0] is NODE_BLOCK) */
    if (root && root->kind == NODE_PROGRAM)
        codegenBlock(&cg, root->child[0]);

    fprintf(out, "    li    $v0, 10           # exit\n");
    fprintf(out, "    syscall\n");
}
