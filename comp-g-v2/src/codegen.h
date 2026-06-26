#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include "ast.h"

/* Codegen symbol table — maps name → (offset from $fp, tipo) */

typedef enum {
    CG_LOCAL,
    CG_PARAM,
    CG_GLOBAL,
    CG_FUNC
} CGKind;

typedef struct CGEntry {
    char           *name;
    CGKind          kind;

    TipoVar         tipo;
    int             isArray;
    int             arraySize;

    /*
      Para local e parâmetro:
        offset em relação a $fp.

      Para global:
        offset não é usado.
    */
    int             offset;

    /*
      Para global:
        label no .data.

      Exemplo:
        global_x
        global_v
    */
    char           *label;

    struct CGEntry *next;
} CGEntry;

typedef struct CGScope {
    CGEntry        *entries;
    int             scopeSize; /* bytes allocated for this scope */
    struct CGScope *prev;
} CGScope;

/* String literal table — collects all NODE_CADEIA nodes in a pre-pass */
typedef struct {
    ASTNode *node;
    int      id;
} StringEntry;

#define MAX_STRINGS 256

typedef struct {
    FILE        *out;
    int          labelCount;  /* global counter for unique labels */
    int          nextOffset;  /* next available var offset (starts at -4) */
    CGScope     *scopeTop;

    StringEntry  strings[MAX_STRINGS];
    int          stringCount;

    char         currentFunctionEnd[128];
} CodeGen;

void codegenProgram(ASTNode *root, FILE *out);

#endif
