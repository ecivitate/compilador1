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

%token PRINCIPAL LEIA ESCREVA NOVALINHA SE ENTAO SENAO FIMSE ENQUANTO
%token INT CAR
%token OU E IGUAL DIFERENTE MAIORIGUAL MENORIGUAL

%token <lexeme> IDENTIFICADOR INTCONST CARCONST CADEIACARACTERES

%type <node> programa declprograma bloco varsection
%type <node> listadeclvar declvar
%type <node> listacomando comando
%type <node> expr orexpr andexpr eqexpr desigexpr addexpr mulexpr unexpr primexpr
%type <tipo> tipo

%%

programa
    : declprograma
        { $$ = $1; ast_root = $$; }
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
    : '{' listadeclvar '}'
        { $$ = $2; }
    ;

listadeclvar
    : IDENTIFICADOR declvar ':' tipo ';' listadeclvar
        {
            ASTNode *first = newNode(NODE_DECL, @1.first_line);
            first->lexeme = $1;
            first->tipo   = $4;

            ASTNode *cur = $2;
            while (cur) { cur->tipo = $4; cur = cur->next; }

            if ($2) {
                ASTNode *tail = $2;
                while (tail->next) tail = tail->next;
                tail->next  = $6;
                first->next = $2;
            } else {
                first->next = $6;
            }
            $$ = first;
        }
    | IDENTIFICADOR declvar ':' tipo ';'
        {
            ASTNode *first = newNode(NODE_DECL, @1.first_line);
            first->lexeme = $1;
            first->tipo   = $4;

            ASTNode *cur = $2;
            while (cur) { cur->tipo = $4; cur = cur->next; }

            if ($2) {
                ASTNode *tail = $2;
                while (tail->next) tail = tail->next;
                first->next = $2;
            }
            $$ = first;
        }
    ;

declvar
    : /* vazio */
        { $$ = NULL; }
    | ',' IDENTIFICADOR declvar
        {
            $$ = newNode(NODE_DECL, @2.first_line);
            $$->lexeme = $2;
            $$->tipo   = TIPO_NENHUM;
            $$->next   = $3;
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
    | LEIA IDENTIFICADOR ';'
        {
            $$ = newNode(NODE_LEIA, @1.first_line);
            $$->lexeme = $2;
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
    ;

expr
    : orexpr
        { $$ = $1; }
    | IDENTIFICADOR '=' expr
        {
            $$ = newNode(NODE_ATRIB, @1.first_line);
            $$->lexeme   = $1;
            $$->child[0] = $3;
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
    : IDENTIFICADOR
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

%%

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso correto: ./g-v1 nome_arquivo\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "arquivo nao pode ser aberto\n");
        return 1;
    }

    yyparse();
    fclose(yyin);

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

        printAST(ast_root, 0);
        freeAST(ast_root);
    }

    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "ERRO: %s na linha %d\n", s, yylineno);
}
