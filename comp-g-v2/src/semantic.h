#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "symtable.h"

typedef struct {
    TipoVar tipo;   // TIPO_INT ou TIPO_CAR
    int isArray;    // 0 = simples, 1 = vetor
} SemType;

void semanticAnalyze(ASTNode *root);

#endif
