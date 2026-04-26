#ifndef AST_H
#define AST_H

typedef enum {
    NODE_PROGRAM,
    NODE_BLOCK,
    NODE_DECL,
    NODE_LEIA,
    NODE_ESCREVA,
    NODE_NOVALINHA,
    NODE_SE,
    NODE_ENQUANTO,
    NODE_ATRIB,
    NODE_BINOP,
    NODE_UNOP,
    NODE_IDENT,
    NODE_INTCONST,
    NODE_CARCONST,
    NODE_CADEIA
} NodeKind;

typedef enum {
    TIPO_INT,
    TIPO_CAR,
    TIPO_NENHUM
} TipoVar;

typedef struct ASTNode {
    NodeKind        kind;
    int             line;
    char           *lexeme;
    TipoVar         tipo;
    struct ASTNode *child[3];
    struct ASTNode *next;
} ASTNode;

ASTNode *newNode(NodeKind kind, int line);
void     freeAST(ASTNode *node);
void     printAST(ASTNode *node, int indent);

#endif
