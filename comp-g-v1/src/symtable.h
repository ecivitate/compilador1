#ifndef SYMTABLE_H
#define SYMTABLE_H

#include "ast.h"

typedef struct SymEntry {
    char           *name;
    TipoVar         tipo;
    int             line;
    struct SymEntry *next;
} SymEntry;

typedef struct Scope {
    SymEntry     *entries;
    struct Scope *prev;
} Scope;

typedef struct {
    Scope *top;
} SymTable;

void     symtableInit(SymTable *st);
void     symtablePushScope(SymTable *st);
void     symtablePopScope(SymTable *st);
int      symtableInsert(SymTable *st, const char *name, TipoVar tipo, int line);
SymEntry *symtableLookup(SymTable *st, const char *name);
SymEntry *symtableLookupCurrent(SymTable *st, const char *name);

#endif
