#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"

static SemType makeType(TipoVar tipo, int isArray) {
    SemType t;
    t.tipo = tipo;
    t.isArray = isArray;
    return t;
}

static SemType makeType(TipoVar tipo, int isArray);
static int sameType(SemType a, SemType b);
static int isNoType(SemType t);

static SemType analyzeNode(ASTNode *node, SymTable *st, TipoVar currentReturnType);
static SemType analyzeLValue(ASTNode *node, SymTable *st);
static SemType analyzeArrayAccess(ASTNode *node, SymTable *st);

static void insertDeclList(ASTNode *decls, SymTable *st);
static void insertFunctionHeaders(ASTNode *funcs, SymTable *st);
static void analyzeFunctionList(ASTNode *funcs, SymTable *st);
static void analyzeFunction(ASTNode *func, SymTable *st);
static void insertParamList(ASTNode *params, SymTable *st);
static void analyzeFunctionBlock(ASTNode *block, SymTable *st, TipoVar returnType);

static ParamInfo *buildParamInfoList(ASTNode *params);
static void checkCallArguments(ASTNode *args, ParamInfo *params, SymTable *st);

static void insertFunctionHeaders(ASTNode *funcs, SymTable *st) {
    for (ASTNode *f = funcs; f; f = f->next) {
        ParamInfo *params = buildParamInfoList(f->child[0]);

        if (!symtableInsertFunc(st, f->lexeme, f->tipo, params, f->line)) {
            fprintf(stderr,
                "ERRO: FUNCAO JA DECLARADA %s linha %d\n",
                f->lexeme, f->line);
            exit(1);
        }

        paramInfoFreeList(params);
    }
}

static void checkCallArguments(ASTNode *args, ParamInfo *params, SymTable *st) {
    ASTNode *a = args;
    ParamInfo *p = params;

    while (a && p) {
        SemType argType = analyzeNode(a, st, TIPO_NENHUM);
        SemType paramType = makeType(p->tipo, p->isArray);

        if (!sameType(argType, paramType)) {
            fprintf(stderr,
                "ERRO: PARAMETRO DE CHAMADA INCOMPATIVEL linha %d\n",
                a->line);
            exit(1);
        }

        a = a->next;
        p = p->next;
    }

    if (a || p) {
        fprintf(stderr,
            "ERRO: NUMERO DE PARAMETROS INCOMPATIVEL\n");
        exit(1);
    }
}

static ParamInfo *buildParamInfoList(ASTNode *params) {
    ParamInfo *list = NULL;
    int position = 0;

    for (ASTNode *p = params; p; p = p->next) {
        position++;

        ParamInfo *info = paramInfoNew(
            p->lexeme,
            p->tipo,
            p->isArray,
            position,
            p->line
        );

        list = paramInfoAppend(list, info);
    }

    return list;
}

static void analyzeFunctionList(ASTNode *funcs, SymTable *st) {
    for (ASTNode *f = funcs; f; f = f->next) {
        analyzeFunction(f, st);
    }
}

static void analyzeFunction(ASTNode *func, SymTable *st) {
    symtablePushScope(st); /* escopo da função */

    insertParamList(func->child[0], st);

    /*
      Atenção:
      O bloco externo da função deve compartilhar o mesmo escopo
      dos parâmetros.
    */
    analyzeFunctionBlock(func->child[1], st, func->tipo);

    symtablePopScope(st);
}

static void insertParamList(ASTNode *params, SymTable *st) {
    int position = 0;

    for (ASTNode *p = params; p; p = p->next) {
        position++;

        if (!symtableInsertParam(
                st,
                p->lexeme,
                p->tipo,
                p->isArray,
                position,
                p->line
            )) {
            fprintf(stderr,
                "ERRO: PARAMETRO JA DECLARADO %s linha %d\n",
                p->lexeme, p->line);
            exit(1);
        }
    }
}

static void analyzeFunctionBlock(ASTNode *block, SymTable *st, TipoVar returnType) {
    if (!block) return;

    /*
      Não cria escopo novo aqui.
      Usa o escopo da função, onde os parâmetros já foram inseridos.
    */
    insertDeclList(block->child[0], st);

    for (ASTNode *c = block->child[1]; c; c = c->next) {
        analyzeNode(c, st, returnType);
    }
}

static int sameType(SemType a, SemType b) {
    return a.tipo == b.tipo && a.isArray == b.isArray;
}

static int isNoType(SemType t) {
    return t.tipo == TIPO_NENHUM;
}
static void insertDeclList(ASTNode *decls, SymTable *st) {
    int position = 0;

    for (ASTNode *d = decls; d; d = d->next) {
        position++;

        if (d->isArray && d->arraySize <= 0) {
            fprintf(stderr,
                "ERRO: TAMANHO DE VETOR INVALIDO %s linha %d\n",
                d->lexeme, d->line);
            exit(1);
        }

        if (!symtableInsertVar(
                st,
                d->lexeme,
                d->tipo,
                d->isArray,
                d->arraySize,
                position,
                d->line
            )) {
            fprintf(stderr,
                "ERRO: VARIAVEL JA DECLARADA NESTE ESCOPO %s linha %d\n",
                d->lexeme, d->line);
            exit(1);
        }
    }
}

static SemType analyzeLValue(ASTNode *node, SymTable *st) {
    if (!node) return makeType(TIPO_NENHUM, 0);

    switch (node->kind) {
        case NODE_IDENT: {
            SymEntry *e = symtableLookup(st, node->lexeme);

            if (!e) {
                fprintf(stderr,
                    "ERRO: VARIAVEL NAO DECLARADA %s linha %d\n",
                    node->lexeme, node->line);
                exit(1);
            }

            if (e->kind == SYM_FUNC) {
                fprintf(stderr,
                    "ERRO: FUNCAO USADA COMO VARIAVEL %s linha %d\n",
                    node->lexeme, node->line);
                exit(1);
            }

            return makeType(e->tipo, e->isArray);
        }

        case NODE_ARRAY_ACCESS:
            return analyzeArrayAccess(node, st);

        default:
            fprintf(stderr,
                "ERRO: EXPRESSAO NAO PODE RECEBER ATRIBUICAO linha %d\n",
                node->line);
            exit(1);
    }
}

static SemType analyzeArrayAccess(ASTNode *node, SymTable *st) {
    SymEntry *e = symtableLookup(st, node->lexeme);

    if (!e) {
        fprintf(stderr,
            "ERRO: VETOR NAO DECLARADO %s linha %d\n",
            node->lexeme, node->line);
        exit(1);
    }

    if (e->kind == SYM_FUNC) {
        fprintf(stderr,
            "ERRO: FUNCAO USADA COMO VETOR %s linha %d\n",
            node->lexeme, node->line);
        exit(1);
    }

    if (!e->isArray) {
        fprintf(stderr,
            "ERRO: VARIAVEL SIMPLES USADA COMO VETOR %s linha %d\n",
            node->lexeme, node->line);
        exit(1);
    }

    SemType indexType = analyzeNode(node->child[0], st, TIPO_NENHUM);

    if (indexType.tipo != TIPO_INT || indexType.isArray) {
        fprintf(stderr,
            "ERRO: INDICE DE VETOR DEVE SER INT linha %d\n",
            node->line);
        exit(1);
    }

    /*
      v[i] não é vetor.
      É um elemento do vetor.
    */
    return makeType(e->tipo, 0);
}

static SemType analyzeNode(ASTNode *node, SymTable *st, TipoVar currentReturnType){
    if (!node) return makeType(TIPO_NENHUM, 0);

    switch (node->kind) {

        case NODE_PROGRAM:
            symtablePushScope(st); /* escopo global */

            insertDeclList(node->child[0], st);        /* variáveis globais */
            insertFunctionHeaders(node->child[1], st); /* assinaturas das funções */

            analyzeFunctionList(node->child[1], st);   /* corpos das funções */
            analyzeNode(node->child[2], st, TIPO_NENHUM); /* principal */

            symtablePopScope(st);
            break;

        case NODE_BLOCK: {
            int hasDecls = (node->child[0] != NULL);

            if (hasDecls) {
                symtablePushScope(st);
                insertDeclList(node->child[0], st);
            }

            for (ASTNode *c = node->child[1]; c; c = c->next) {
                analyzeNode(c, st, currentReturnType);
            }

            if (hasDecls) {
                symtablePopScope(st);
            }

            break;
        }

        case NODE_LEIA: {
            SemType t = analyzeLValue(node->child[0], st);

            if (t.isArray) {
                fprintf(stderr,
                    "ERRO: LEIA NAO PODE RECEBER VETOR INTEIRO linha %d\n",
                    node->line);
                exit(1);
            }

            break;
        }

        case NODE_ESCREVA: {
            SemType t = analyzeNode(node->child[0], st, currentReturnType);

            if (t.isArray) {
                fprintf(stderr,
                    "ERRO: ESCREVA NAO PODE IMPRIMIR VETOR INTEIRO linha %d\n",
                    node->line);
                exit(1);
            }

            break;
        }

        case NODE_NOVALINHA:
        case NODE_CADEIA:
            break;

        case NODE_SE:{
            SemType cond = analyzeNode(node->child[0], st, currentReturnType);

            if (cond.isArray) {
                fprintf(stderr,
                    "ERRO: CONDICAO NAO PODE SER VETOR linha %d\n",
                    node->line);
                exit(1);
            }

            analyzeNode(node->child[1], st, currentReturnType);
            analyzeNode(node->child[2], st, currentReturnType);
            break;
        }
        

        case NODE_ENQUANTO:{
            SemType cond = analyzeNode(node->child[0], st, currentReturnType);

            if (cond.isArray) {
                fprintf(stderr,
                    "ERRO: CONDICAO NAO PODE SER VETOR linha %d\n",
                    node->line);
                exit(1);
            }

            analyzeNode(node->child[1], st, currentReturnType);
            break;
        }

        case NODE_ATRIB: {
            SemType lhs = analyzeLValue(node->child[0], st);
            SemType rhs = analyzeNode(node->child[1], st, currentReturnType);

            if (!sameType(lhs, rhs)) {
                fprintf(stderr,
                    "ERRO: ATRIBUICAO COM TIPOS INCOMPATIVEIS linha %d\n",
                    node->line);
                exit(1);
            }

            return lhs;
        }
        
        case NODE_ARRAY_ACCESS:
            return analyzeArrayAccess(node, st);

        case NODE_BINOP: {
            SemType left  = analyzeNode(node->child[0], st, currentReturnType);
            SemType right = analyzeNode(node->child[1], st, currentReturnType);
            const char *op = node->lexeme;

            if (left.isArray || right.isArray) {
                fprintf(stderr,
                    "ERRO: OPERADOR NAO ACEITA VETOR INTEIRO linha %d\n",
                    node->line);
                exit(1);
            }

            if (!isNoType(left) && !isNoType(right) && left.tipo != right.tipo) {
                fprintf(stderr,
                    "ERRO: OPERACAO COM TIPOS INCOMPATIVEIS linha %d\n",
                    node->line);
                exit(1);
            }

            if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 ||
                strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {

                if (left.tipo != TIPO_INT || right.tipo != TIPO_INT) {
                    fprintf(stderr,
                        "ERRO: OPERADOR ARITMETICO EXIGE INT linha %d\n",
                        node->line);
                    exit(1);
                }

                return makeType(TIPO_INT, 0);
            }

            if (strcmp(op, "||") == 0 || strcmp(op, "&") == 0 ||
                strcmp(op, "==") == 0 || strcmp(op, "!=") == 0 ||
                strcmp(op, "<")  == 0 || strcmp(op, ">")  == 0 ||
                strcmp(op, ">=") == 0 || strcmp(op, "<=") == 0) {
                return makeType(TIPO_INT, 0);
            }

            return makeType(TIPO_NENHUM, 0);
        }

        case NODE_UNOP: {
            SemType t = analyzeNode(node->child[0], st, currentReturnType);

            if (t.isArray) {
                fprintf(stderr,
                    "ERRO: OPERADOR UNARIO NAO ACEITA VETOR linha %d\n",
                    node->line);
                exit(1);
            }

            if (strcmp(node->lexeme, "-") == 0) {
                if (t.tipo != TIPO_INT) {
                    fprintf(stderr,
                        "ERRO: OPERADOR UNARIO '-' EXIGE INT linha %d\n",
                        node->line);
                    exit(1);
                }

                return makeType(TIPO_INT, 0);
            }

            if (strcmp(node->lexeme, "!") == 0) {
                if (t.tipo != TIPO_INT) {
                    fprintf(stderr,
                        "ERRO: OPERADOR LOGICO '!' EXIGE INT linha %d\n",
                        node->line);
                    exit(1);
                }

                return makeType(TIPO_INT, 0);
            }

            fprintf(stderr,
                "ERRO: OPERADOR UNARIO INVALIDO %s linha %d\n",
                node->lexeme ? node->lexeme : "",
                node->line);
            exit(1);
        }

        case NODE_IDENT: {
            SymEntry *e = symtableLookup(st, node->lexeme);

            if (!e) {
                fprintf(stderr,
                    "ERRO: VARIAVEL NAO DECLARADA %s linha %d\n",
                    node->lexeme, node->line);
                exit(1);
            }

            if (e->kind == SYM_FUNC) {
                fprintf(stderr,
                    "ERRO: FUNCAO USADA COMO VARIAVEL %s linha %d\n",
                    node->lexeme, node->line);
                exit(1);
            }

            return makeType(e->tipo, e->isArray);
        }

        case NODE_INTCONST:
            return makeType(TIPO_INT, 0);

        case NODE_CARCONST:
            return makeType(TIPO_CAR, 0);

        case NODE_RETORNE: {
            if (currentReturnType == TIPO_NENHUM) {
                fprintf(stderr,
                    "ERRO: RETORNE FORA DE FUNCAO linha %d\n",
                    node->line);
                exit(1);
            }

            SemType t = analyzeNode(node->child[0], st, currentReturnType);

            if (t.isArray) {
                fprintf(stderr,
                    "ERRO: FUNCAO NAO PODE RETORNAR VETOR linha %d\n",
                    node->line);
                exit(1);
            }

            if (t.tipo != currentReturnType) {
                fprintf(stderr,
                    "ERRO: TIPO DE RETORNO INCOMPATIVEL linha %d\n",
                    node->line);
                exit(1);
            }

            return t;
        }
        case NODE_CALL: {
            SymEntry *f = symtableLookup(st, node->lexeme);

            if (!f) {
                fprintf(stderr,
                    "ERRO: FUNCAO NAO DECLARADA %s linha %d\n",
                    node->lexeme, node->line);
                exit(1);
            }

            if (f->kind != SYM_FUNC) {
                fprintf(stderr,
                    "ERRO: IDENTIFICADOR NAO E FUNCAO %s linha %d\n",
                    node->lexeme, node->line);
                exit(1);
            }

            checkCallArguments(node->child[0], f->params, st);

            return makeType(f->tipo, 0);
        }

        default:
            break;
    }

    return makeType(TIPO_NENHUM, 0);
}

void semanticAnalyze(ASTNode *root) {
    SymTable st;
    symtableInit(&st);
    analyzeNode(root, &st, TIPO_NENHUM);
}
