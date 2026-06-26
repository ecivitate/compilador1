#ifndef SYMTABLE_H
#define SYMTABLE_H

#include "ast.h"

typedef struct ParamInfo {
    char             *name;
    TipoVar           tipo;
    int               isArray;
    int               position;
    int               line;
    struct ParamInfo *next;
} ParamInfo;

typedef enum {
    SYM_VAR,
    SYM_PARAM,
    SYM_FUNC
} SymKind;

typedef struct SymEntry {
    char            *name;
    SymKind          kind;

    /*
      Para variável/parâmetro:
        tipo = tipo base: TIPO_INT ou TIPO_CAR

      Para função:
        tipo = tipo de retorno
    */
    TipoVar          tipo;
    int              line;

    /*
      Usado por variável e parâmetro.
      Para função, normalmente fica 0.
    */
    int              isArray;
    int              arraySize;

    /*
      Posição na lista de declaração ou na lista de parâmetros.
      Útil depois para geração de código.
    */
    int              position;

    /*
      Usado apenas quando kind == SYM_FUNC.
    */
    int              paramCount;
    ParamInfo       *params;

    struct SymEntry *next;
} SymEntry;

typedef struct Scope {
    SymEntry     *entries;
    struct Scope *prev;
} Scope;

typedef struct {
    Scope *top;
} SymTable;

void symtableInit(SymTable *st);
void symtablePushScope(SymTable *st);
void symtablePopScope(SymTable *st);
void symtableFree(SymTable *st);

/* Inserções específicas */
int symtableInsertVar(
    SymTable *st,
    const char *name,
    TipoVar tipo,
    int isArray,
    int arraySize,
    int position,
    int line
);

int symtableInsertParam(
    SymTable *st,
    const char *name,
    TipoVar tipo,
    int isArray,
    int position,
    int line
);

int symtableInsertFunc(
    SymTable *st,
    const char *name,
    TipoVar returnType,
    ParamInfo *params,
    int line
);

/* Buscas */
SymEntry *symtableLookup(SymTable *st, const char *name);
SymEntry *symtableLookupCurrent(SymTable *st, const char *name);

/* Utilidades para lista de parâmetros */
ParamInfo *paramInfoNew(
    const char *name,
    TipoVar tipo,
    int isArray,
    int position,
    int line
);

ParamInfo *paramInfoAppend(ParamInfo *list, ParamInfo *param);
ParamInfo *paramInfoCloneList(ParamInfo *list);
int        paramInfoCount(ParamInfo *list);
void       paramInfoFreeList(ParamInfo *list);

#endif
