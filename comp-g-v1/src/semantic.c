#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"

static TipoVar analyzeNode(ASTNode *node, SymTable *st);

static TipoVar analyzeNode(ASTNode *node, SymTable *st) {
    if (!node) return TIPO_NENHUM;

    switch (node->kind) {

        case NODE_PROGRAM:
            analyzeNode(node->child[0], st);
            break;

        case NODE_BLOCK: {
            int hasDecls = (node->child[0] != NULL);
            if (hasDecls) {
                symtablePushScope(st);
                for (ASTNode *d = node->child[0]; d; d = d->next) {
                    if (!symtableInsert(st, d->lexeme, d->tipo, d->line)) {
                        fprintf(stderr,
                            "ERRO: VARIAVEL JA DECLARADA NESTE ESCOPO %s linha %d\n",
                            d->lexeme, d->line);
                        exit(1);
                    }
                }
            }
            for (ASTNode *c = node->child[1]; c; c = c->next)
                analyzeNode(c, st);
            if (hasDecls)
                symtablePopScope(st);
            break;
        }

        case NODE_LEIA: {
            if (!symtableLookup(st, node->lexeme)) {
                fprintf(stderr,
                    "ERRO: VARIAVEL NAO DECLARADA %s linha %d\n",
                    node->lexeme, node->line);
                exit(1);
            }
            break;
        }

        case NODE_ESCREVA:
            analyzeNode(node->child[0], st);
            break;

        case NODE_NOVALINHA:
        case NODE_CADEIA:
            break;

        case NODE_SE:
            analyzeNode(node->child[0], st);
            analyzeNode(node->child[1], st);
            analyzeNode(node->child[2], st);
            break;

        case NODE_ENQUANTO:
            analyzeNode(node->child[0], st);
            analyzeNode(node->child[1], st);
            break;

        case NODE_ATRIB: {
            SymEntry *e = symtableLookup(st, node->lexeme);
            if (!e) {
                fprintf(stderr,
                    "ERRO: VARIAVEL NAO DECLARADA %s linha %d\n",
                    node->lexeme, node->line);
                exit(1);
            }
            TipoVar rhs = analyzeNode(node->child[0], st);
            if (rhs != TIPO_NENHUM && e->tipo != rhs) {
                fprintf(stderr,
                    "ERRO: ATRIBUICAO COM TIPOS INCOMPATIVEIS linha %d\n",
                    node->line);
                exit(1);
            }
            return e->tipo;
        }

        case NODE_BINOP: {
            TipoVar left  = analyzeNode(node->child[0], st);
            TipoVar right = analyzeNode(node->child[1], st);
            const char *op = node->lexeme;

            if (left != TIPO_NENHUM && right != TIPO_NENHUM && left != right) {
                fprintf(stderr,
                    "ERRO: OPERACAO COM TIPOS INCOMPATIVEIS linha %d\n",
                    node->line);
                exit(1);
            }

            if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0 ||
                strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
                if (left != TIPO_INT || right != TIPO_INT) {
                    fprintf(stderr,
                        "ERRO: OPERADOR ARITMETICO EXIGE INT linha %d\n",
                        node->line);
                    exit(1);
                }
                return TIPO_INT;
            }

            if (strcmp(op, "||") == 0 || strcmp(op, "&") == 0 ||
                strcmp(op, "==") == 0 || strcmp(op, "!=") == 0 ||
                strcmp(op, "<")  == 0 || strcmp(op, ">")  == 0 ||
                strcmp(op, ">=") == 0 || strcmp(op, "<=") == 0) {
                return TIPO_INT;
            }

            return TIPO_NENHUM;
        }

        case NODE_UNOP: {
            TipoVar t = analyzeNode(node->child[0], st);

            if (strcmp(node->lexeme, "-") == 0) {
                if (t != TIPO_INT) {
                    fprintf(stderr,
                            "ERRO: OPERADOR UNARIO '-' EXIGE INT linha %d\n",
                            node->line);
                    exit(1);
                }

                return TIPO_INT;
            }

            if (strcmp(node->lexeme, "!") == 0) {
                if (t != TIPO_INT) {
                    fprintf(stderr,
                            "ERRO: OPERADOR LOGICO '!' EXIGE INT linha %d\n",
                            node->line);
                    exit(1);
                }

                return TIPO_INT;
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
            return e->tipo;
        }

        case NODE_INTCONST:
            return TIPO_INT;

        case NODE_CARCONST:
            return TIPO_CAR;

        default:
            break;
    }

    return TIPO_NENHUM;
}

void semanticAnalyze(ASTNode *root) {
    SymTable st;
    symtableInit(&st);
    analyzeNode(root, &st);
}
