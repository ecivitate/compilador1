#include <stdlib.h>
#include <string.h>
#include "symtable.h"

void symtableInit(SymTable *st) {
    st->top = NULL;
}

void symtablePushScope(SymTable *st) {
    Scope *s = calloc(1, sizeof(Scope));
    s->prev  = st->top;
    st->top  = s;
}

void symtablePopScope(SymTable *st) {
    if (!st->top) return;
    Scope *s = st->top;
    SymEntry *e = s->entries;
    while (e) {
        SymEntry *next = e->next;
        free(e->name);
        free(e);
        e = next;
    }
    st->top = s->prev;
    free(s);
}

int symtableInsert(SymTable *st, const char *name, TipoVar tipo, int line) {
    if (symtableLookupCurrent(st, name)) return 0;
    SymEntry *e = calloc(1, sizeof(SymEntry));
    e->name  = strdup(name);
    e->tipo  = tipo;
    e->line  = line;
    e->next  = st->top->entries;
    st->top->entries = e;
    return 1;
}

SymEntry *symtableLookup(SymTable *st, const char *name) {
    for (Scope *s = st->top; s; s = s->prev)
        for (SymEntry *e = s->entries; e; e = e->next)
            if (strcmp(e->name, name) == 0) return e;
    return NULL;
}

SymEntry *symtableLookupCurrent(SymTable *st, const char *name) {
    if (!st->top) return NULL;
    for (SymEntry *e = st->top->entries; e; e = e->next)
        if (strcmp(e->name, name) == 0) return e;
    return NULL;
}
