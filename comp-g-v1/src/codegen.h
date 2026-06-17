#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include "ast.h"

/* Codegen symbol table — maps name → (offset from $fp, tipo) */
typedef struct CGEntry {
    char           *name;
    int             offset;    /* negative offset from $fp, e.g. -4 */
    TipoVar         tipo;
    struct CGEntry *next;
} CGEntry;

typedef struct CGScope {
    CGEntry        *entries;
    int             scopeSize; /* bytes allocated for this scope (4 * num_vars) */
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
} CodeGen;

void codegenProgram(ASTNode *root, FILE *out);

#endif
