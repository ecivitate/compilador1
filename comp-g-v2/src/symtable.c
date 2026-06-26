#include <stdlib.h>
#include <string.h>
#include "symtable.h"

static char *dupString(const char *s) {
    if (!s) return NULL;

    char *copy = malloc(strlen(s) + 1);
    if (!copy) exit(1);

    strcpy(copy, s);
    return copy;
}

static void freeEntry(SymEntry *e) {
    if (!e) return;

    free(e->name);

    if (e->kind == SYM_FUNC) {
        paramInfoFreeList(e->params);
    }

    free(e);
}

void symtableInit(SymTable *st) {
    st->top = NULL;
}

void symtablePushScope(SymTable *st) {
    Scope *s = calloc(1, sizeof(Scope));
    if (!s) exit(1);

    s->prev = st->top;
    st->top = s;
}

void symtablePopScope(SymTable *st) {
    if (!st->top) return;

    Scope *s = st->top;
    SymEntry *e = s->entries;

    while (e) {
        SymEntry *next = e->next;
        freeEntry(e);
        e = next;
    }

    st->top = s->prev;
    free(s);
}

void symtableFree(SymTable *st) {
    while (st->top) {
        symtablePopScope(st);
    }
}

SymEntry *symtableLookupCurrent(SymTable *st, const char *name) {
    if (!st->top) return NULL;

    for (SymEntry *e = st->top->entries; e; e = e->next) {
        if (strcmp(e->name, name) == 0) {
            return e;
        }
    }

    return NULL;
}

SymEntry *symtableLookup(SymTable *st, const char *name) {
    for (Scope *s = st->top; s; s = s->prev) {
        for (SymEntry *e = s->entries; e; e = e->next) {
            if (strcmp(e->name, name) == 0) {
                return e;
            }
        }
    }

    return NULL;
}

static int insertEntry(SymTable *st, SymEntry *e) {
    if (!st->top) {
        /*
          Você pode escolher dar erro aqui.
          Eu prefiro criar o primeiro escopo automaticamente
          para evitar segfault caso esqueça de chamar push.
        */
        symtablePushScope(st);
    }

    if (symtableLookupCurrent(st, e->name)) {
        freeEntry(e);
        return 0;
    }

    e->next = st->top->entries;
    st->top->entries = e;

    return 1;
}

int symtableInsertVar(
    SymTable *st,
    const char *name,
    TipoVar tipo,
    int isArray,
    int arraySize,
    int position,
    int line
) {
    SymEntry *e = calloc(1, sizeof(SymEntry));
    if (!e) exit(1);

    e->name      = dupString(name);
    e->kind      = SYM_VAR;
    e->tipo      = tipo;
    e->line      = line;
    e->isArray   = isArray;
    e->arraySize = arraySize;
    e->position  = position;

    return insertEntry(st, e);
}

int symtableInsertParam(
    SymTable *st,
    const char *name,
    TipoVar tipo,
    int isArray,
    int position,
    int line
) {
    SymEntry *e = calloc(1, sizeof(SymEntry));
    if (!e) exit(1);

    e->name      = dupString(name);
    e->kind      = SYM_PARAM;
    e->tipo      = tipo;
    e->line      = line;
    e->isArray   = isArray;
    e->arraySize = 0;
    e->position  = position;

    return insertEntry(st, e);
}

int symtableInsertFunc(
    SymTable *st,
    const char *name,
    TipoVar returnType,
    ParamInfo *params,
    int line
) {
    SymEntry *e = calloc(1, sizeof(SymEntry));
    if (!e) exit(1);

    e->name       = dupString(name);
    e->kind       = SYM_FUNC;
    e->tipo       = returnType;
    e->line       = line;
    e->isArray    = 0;
    e->arraySize  = 0;
    e->position   = 0;
    e->paramCount = paramInfoCount(params);

    /*
      Clonamos a lista para a tabela de símbolos ser dona
      da sua própria cópia. Assim, não dependemos da AST.
    */
    e->params = paramInfoCloneList(params);

    return insertEntry(st, e);
}


ParamInfo *paramInfoNew(
    const char *name,
    TipoVar tipo,
    int isArray,
    int position,
    int line
) {
    ParamInfo *p = calloc(1, sizeof(ParamInfo));
    if (!p) exit(1);

    p->name     = dupString(name);
    p->tipo     = tipo;
    p->isArray  = isArray;
    p->position = position;
    p->line     = line;
    p->next     = NULL;

    return p;
}

ParamInfo *paramInfoAppend(ParamInfo *list, ParamInfo *param) {
    if (!list) return param;

    ParamInfo *cur = list;
    while (cur->next) {
        cur = cur->next;
    }

    cur->next = param;
    return list;
}

int paramInfoCount(ParamInfo *list) {
    int count = 0;

    for (ParamInfo *p = list; p; p = p->next) {
        count++;
    }

    return count;
}

ParamInfo *paramInfoCloneList(ParamInfo *list) {
    ParamInfo *copy = NULL;

    for (ParamInfo *p = list; p; p = p->next) {
        ParamInfo *newParam = paramInfoNew(
            p->name,
            p->tipo,
            p->isArray,
            p->position,
            p->line
        );

        copy = paramInfoAppend(copy, newParam);
    }

    return copy;
}

void paramInfoFreeList(ParamInfo *list) {
    ParamInfo *p = list;

    while (p) {
        ParamInfo *next = p->next;
        free(p->name);
        free(p);
        p = next;
    }
}