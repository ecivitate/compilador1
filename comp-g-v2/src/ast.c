#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode *newNode(NodeKind kind, int line) {
    ASTNode *n = calloc(1, sizeof(ASTNode));
    if (!n) { fprintf(stderr, "erro: sem memoria\n"); exit(1); }
    n->kind = kind;
    n->line = line;
    n->tipo = TIPO_NENHUM;
    return n;
}

void freeAST(ASTNode *node) {
    if (!node) return;
    for (int i = 0; i < 3; i++) freeAST(node->child[i]);
    freeAST(node->next);
    free(node->lexeme);
    free(node);
}

static const char *kindName(NodeKind k) {
    switch (k) {
        case NODE_PROGRAM:   return "PROGRAM";
        case NODE_BLOCK:     return "BLOCK";
        case NODE_DECL:      return "DECL";
        case NODE_LEIA:      return "LEIA";
        case NODE_ESCREVA:   return "ESCREVA";
        case NODE_NOVALINHA: return "NOVALINHA";
        case NODE_SE:        return "SE";
        case NODE_ENQUANTO:  return "ENQUANTO";
        case NODE_ATRIB:     return "ATRIB";
        case NODE_BINOP:     return "BINOP";
        case NODE_UNOP:      return "UNOP";
        case NODE_IDENT:     return "IDENT";
        case NODE_INTCONST:  return "INTCONST";
        case NODE_CARCONST:  return "CARCONST";
        case NODE_CADEIA:    return "CADEIA";
        default:             return "???";
    }
}

void printAST(ASTNode *node, int indent) {
    if (!node) return;

    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->kind) {
        case NODE_DECL:
            printf("DECL %s: %s [linha %d]\n",
                   node->lexeme,
                   node->tipo == TIPO_INT ? "int" : "car",
                   node->line);
            break;
        case NODE_LEIA:
        case NODE_ATRIB:
        case NODE_IDENT:
        case NODE_BINOP:
        case NODE_UNOP:
        case NODE_INTCONST:
        case NODE_CARCONST:
        case NODE_CADEIA:
            printf("%s %s [linha %d]\n", kindName(node->kind), node->lexeme, node->line);
            break;
        default:
            printf("%s [linha %d]\n", kindName(node->kind), node->line);
            break;
    }

    for (int i = 0; i < 3; i++) printAST(node->child[i], indent + 1);
    printAST(node->next, indent);
}
