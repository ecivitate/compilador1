%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantic.h"
#include "codegen.h"

extern int   yylineno;
extern char *yytext;
extern int   yylex();
extern FILE *yyin;

void yyerror(const char *s);

ASTNode *ast_root = NULL;
%}

%locations

%union {
    ASTNode *node;
    TipoVar  tipo;
    char    *lexeme;
}

%token GLOBAL FUNCAO RETORNE PRINCIPAL LEIA ESCREVA NOVALINHA SE ENTAO SENAO FIMSE ENQUANTO
%token INT CAR
%token OU E IGUAL DIFERENTE MAIORIGUAL MENORIGUAL

%token <lexeme> IDENTIFICADOR INTCONST CARCONST CADEIACARACTERES

%type <node> programa declvarglobais declfunc declprograma
%type <node> listafuncoes listaparametros listaparametrostail
%type <node> bloco varsection
%type <node> listadeclvar listvar
%type <node> listacomando comando
%type <node> expr lvalueexpr orexpr andexpr eqexpr desigexpr addexpr mulexpr unexpr primexpr
%type <node> listexpr
%type <tipo> tipo

%%

programa
    : declvarglobais declfunc declprograma
        {
            $$ = newNode(NODE_PROGRAM, @3.first_line);
            $$->child[0] = $1;  /* variaveis globais */
            $$->child[1] = $2;  /* funcoes */
            $$->child[2] = $3;  /* principal */
            ast_root = $$;
        }
    ;

declvarglobais
    : GLOBAL varsection
        { $$ = $2; }
    | /* vazio */
        { $$ = NULL; }
    ;

declfunc
    : FUNCAO '[' IDENTIFICADOR '(' listaparametros ')' ':' tipo bloco listafuncoes ']'
        {
            ASTNode *f = newNode(NODE_FUNC, @3.first_line);
            f->lexeme = $3;
            f->tipo = $8;
            f->child[0] = $5;   /* parametros */
            f->child[1] = $9;   /* bloco */
            f->next = $10;      /* proximas funcoes */
            $$ = f;
        }
    | /* vazio */
        { $$ = NULL; }
    ;

listafuncoes
    : IDENTIFICADOR '(' listaparametros ')' ':' tipo bloco listafuncoes
        {
            ASTNode *f = newNode(NODE_FUNC, @1.first_line);
            f->lexeme = $1;
            f->tipo = $6;
            f->child[0] = $3;
            f->child[1] = $7;
            f->next = $8;
            $$ = f;
        }
    | /* vazio */
        { $$ = NULL; }
    ;

listaparametros
    : listaparametrostail
        { $$ = $1; }
    | /* vazio */
        { $$ = NULL; }
    ;

listaparametrostail
    : IDENTIFICADOR ':' tipo
        {
            $$ = newNode(NODE_PARAM, @1.first_line);
            $$->lexeme = $1;
            $$->tipo = $3;
        }
    | IDENTIFICADOR '[' ']' ':' tipo
        {
            $$ = newNode(NODE_PARAM, @1.first_line);
            $$->lexeme = $1;
            $$->tipo = $5;
            $$->isArray = 1;
        }
    | IDENTIFICADOR ':' tipo ',' listaparametrostail
        {
            $$ = newNode(NODE_PARAM, @1.first_line);
            $$->lexeme = $1;
            $$->tipo = $3;
            $$->next = $5;
        }
    | IDENTIFICADOR '[' ']' ':' tipo ',' listaparametrostail
        {
            $$ = newNode(NODE_PARAM, @1.first_line);
            $$->lexeme = $1;
            $$->tipo = $5;
            $$->isArray = 1;
            $$->next = $7;
        }
    ;

declprograma
    : PRINCIPAL bloco
        {
            $$ = newNode(NODE_PROGRAM, @1.first_line);
            $$->child[0] = $2;
        }
    ;

bloco
    : '{' listacomando '}'
        {
            $$ = newNode(NODE_BLOCK, @1.first_line);
            $$->child[1] = $2;
        }
    | varsection '{' listacomando '}'
        {
            $$ = newNode(NODE_BLOCK, @2.first_line);
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    ;

varsection
    : '[' listadeclvar ']'
        { $$ = $2; }
    ;

listadeclvar
    : listvar ':' tipo ';' listadeclvar
        {
            ASTNode *cur = $1;
            while (cur) {
                cur->tipo = $3;
                cur = cur->next;
            }

            ASTNode *tail = $1;
            while (tail && tail->next) tail = tail->next;
            if (tail) tail->next = $5;

            $$ = $1;
        }
    | listvar ':' tipo ';'
        {
            ASTNode *cur = $1;
            while (cur) {
                cur->tipo = $3;
                cur = cur->next;
            }

            $$ = $1;
        }
    ;

listvar
    : IDENTIFICADOR ',' listvar
        {
            $$ = newNode(NODE_DECL, @1.first_line);
            $$->lexeme = $1;
            $$->tipo = TIPO_NENHUM;
            $$->next = $3;
        }
    | IDENTIFICADOR '[' INTCONST ']' ',' listvar
        {
            $$ = newNode(NODE_DECL, @1.first_line);
            $$->lexeme = $1;
            $$->tipo = TIPO_NENHUM;
            $$->isArray = 1;
            $$->arraySize = atoi($3);
            free($3);
            $$->next = $6;
        }
    | IDENTIFICADOR
        {
            $$ = newNode(NODE_DECL, @1.first_line);
            $$->lexeme = $1;
            $$->tipo = TIPO_NENHUM;
        }
    | IDENTIFICADOR '[' INTCONST ']'
        {
            $$ = newNode(NODE_DECL, @1.first_line);
            $$->lexeme = $1;
            $$->tipo = TIPO_NENHUM;
            $$->isArray = 1;
            $$->arraySize = atoi($3);
            free($3);
        }
    ;

tipo
    : INT { $$ = TIPO_INT; }
    | CAR { $$ = TIPO_CAR; }
    ;

listacomando
    : comando
        { $$ = $1; }
    | comando listacomando
        {
            if ($1) {
                ASTNode *tail = $1;
                while (tail->next) tail = tail->next;
                tail->next = $2;
                $$ = $1;
            } else {
                $$ = $2;
            }
        }
    ;

comando
    : ';'
        { $$ = NULL; }
    | expr ';'
        { $$ = $1; }
    | LEIA lvalueexpr ';'
    {
        $$ = newNode(NODE_LEIA, @1.first_line);
        $$->child[0] = $2;
    }
    | ESCREVA expr ';'
        {
            $$ = newNode(NODE_ESCREVA, @1.first_line);
            $$->child[0] = $2;
        }
    | ESCREVA CADEIACARACTERES ';'
        {
            ASTNode *cad = newNode(NODE_CADEIA, @2.first_line);
            cad->lexeme  = $2;
            $$ = newNode(NODE_ESCREVA, @1.first_line);
            $$->child[0] = cad;
        }
    | NOVALINHA ';'
        { $$ = newNode(NODE_NOVALINHA, @1.first_line); }
    | SE '(' expr ')' ENTAO comando FIMSE
        {
            $$ = newNode(NODE_SE, @1.first_line);
            $$->child[0] = $3;
            $$->child[1] = $6;
        }
    | SE '(' expr ')' ENTAO comando SENAO comando FIMSE
        {
            $$ = newNode(NODE_SE, @1.first_line);
            $$->child[0] = $3;
            $$->child[1] = $6;
            $$->child[2] = $8;
        }
    | ENQUANTO '(' expr ')' comando
        {
            $$ = newNode(NODE_ENQUANTO, @1.first_line);
            $$->child[0] = $3;
            $$->child[1] = $5;
        }
    | bloco
        { $$ = $1; }
    | RETORNE expr ';'
        {
            $$ = newNode(NODE_RETORNE, @1.first_line);
            $$->child[0] = $2;
        }
    ;

expr
    : lvalueexpr '=' expr
        {
            $$ = newNode(NODE_ATRIB, @2.first_line);
            $$->child[0] = $1;  /* destino */
            $$->child[1] = $3;  /* valor */
        }
    | orexpr
        { $$ = $1; }
    ;

lvalueexpr
    : IDENTIFICADOR
        {
            $$ = newNode(NODE_IDENT, @1.first_line);
            $$->lexeme = $1;
        }
    | IDENTIFICADOR '[' expr ']'
        {
            $$ = newNode(NODE_ARRAY_ACCESS, @1.first_line);
            $$->lexeme = $1;
            $$->child[0] = $3;  /* indice */
        }
    ;

orexpr
    : orexpr OU andexpr
        {
            $$ = newNode(NODE_BINOP, @2.first_line);
            $$->lexeme   = strdup("||");
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    | andexpr
        { $$ = $1; }
    ;

andexpr
    : andexpr E eqexpr
        {
            $$ = newNode(NODE_BINOP, @2.first_line);
            $$->lexeme   = strdup("&");
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    | eqexpr
        { $$ = $1; }
    ;

eqexpr
    : eqexpr IGUAL desigexpr
        {
            $$ = newNode(NODE_BINOP, @2.first_line);
            $$->lexeme   = strdup("==");
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    | eqexpr DIFERENTE desigexpr
        {
            $$ = newNode(NODE_BINOP, @2.first_line);
            $$->lexeme   = strdup("!=");
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    | desigexpr
        { $$ = $1; }
    ;

desigexpr
    : desigexpr '<' addexpr
        {
            $$ = newNode(NODE_BINOP, @2.first_line);
            $$->lexeme   = strdup("<");
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    | desigexpr '>' addexpr
        {
            $$ = newNode(NODE_BINOP, @2.first_line);
            $$->lexeme   = strdup(">");
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    | desigexpr MAIORIGUAL addexpr
        {
            $$ = newNode(NODE_BINOP, @2.first_line);
            $$->lexeme   = strdup(">=");
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    | desigexpr MENORIGUAL addexpr
        {
            $$ = newNode(NODE_BINOP, @2.first_line);
            $$->lexeme   = strdup("<=");
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    | addexpr
        { $$ = $1; }
    ;

addexpr
    : addexpr '+' mulexpr
        {
            $$ = newNode(NODE_BINOP, @2.first_line);
            $$->lexeme   = strdup("+");
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    | addexpr '-' mulexpr
        {
            $$ = newNode(NODE_BINOP, @2.first_line);
            $$->lexeme   = strdup("-");
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    | mulexpr
        { $$ = $1; }
    ;

mulexpr
    : mulexpr '*' unexpr
        {
            $$ = newNode(NODE_BINOP, @2.first_line);
            $$->lexeme   = strdup("*");
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    | mulexpr '/' unexpr
        {
            $$ = newNode(NODE_BINOP, @2.first_line);
            $$->lexeme   = strdup("/");
            $$->child[0] = $1;
            $$->child[1] = $3;
        }
    | unexpr
        { $$ = $1; }
    ;

unexpr
    : '-' primexpr
        {
            $$ = newNode(NODE_UNOP, @1.first_line);
            $$->lexeme   = strdup("-");
            $$->child[0] = $2;
        }
    | '!' primexpr
        {
            $$ = newNode(NODE_UNOP, @1.first_line);
            $$->lexeme   = strdup("!");
            $$->child[0] = $2;
        }
    | primexpr
        { $$ = $1; }
    ;

primexpr
    : IDENTIFICADOR '(' listexpr ')'
        {
            $$ = newNode(NODE_CALL, @1.first_line);
            $$->lexeme = $1;
            $$->child[0] = $3;
        }
    | IDENTIFICADOR '(' ')'
        {
            $$ = newNode(NODE_CALL, @1.first_line);
            $$->lexeme = $1;
        }
    | IDENTIFICADOR '[' expr ']'
        {
            $$ = newNode(NODE_ARRAY_ACCESS, @1.first_line);
            $$->lexeme = $1;
            $$->child[0] = $3;
        }
    | IDENTIFICADOR
        {
            $$ = newNode(NODE_IDENT, @1.first_line);
            $$->lexeme = $1;
        }
    | INTCONST
        {
            $$ = newNode(NODE_INTCONST, @1.first_line);
            $$->lexeme = $1;
        }
    | CARCONST
        {
            $$ = newNode(NODE_CARCONST, @1.first_line);
            $$->lexeme = $1;
        }
    | '(' expr ')'
        { $$ = $2; }
    ;

listexpr
    : expr
        { $$ = $1; }
    | listexpr ',' expr
        {
            ASTNode *tail = $1;
            while (tail->next) tail = tail->next;
            tail->next = $3;
            $$ = $1;
        }
    ;

%%

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso correto: ./g-v2 nome_arquivo\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "arquivo nao pode ser aberto\n");
        return 1;
    }

    int parseResult = yyparse();
    fclose(yyin);

    if (parseResult != 0) {
        freeAST(ast_root);
        return 1;
    }

    if (ast_root) {
        semanticAnalyze(ast_root);

        char outname[512];
        strncpy(outname, argv[1], sizeof(outname) - 5);
        outname[sizeof(outname) - 5] = '\0';
        char *dot = strrchr(outname, '.');
        if (dot) strcpy(dot, ".asm");
        else strcat(outname, ".asm");

        FILE *out = fopen(outname, "w");
        if (!out) { fprintf(stderr, "erro: nao foi possivel criar %s\n", outname); return 1; }
        codegenProgram(ast_root, out);
        fclose(out);

        freeAST(ast_root);
    }

    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "ERRO: %s na linha %d\n", s, yylineno);
}
