%{
#include <stdio.h>
#include <stdlib.h>

extern int yylineno;
extern char *yytext;
extern int yylex();
extern FILE *yyin;

void yyerror(const char *s);
%}

/* Tokens que nao correspondem a apenas um caractere */
%token PRINCIPAL IDENTIFICADOR INT CAR LEIA ESCREVA NOVALINHA
%token SE ENTAO SENAO FIMSE ENQUANTO
%token CADEIACARACTERES OU E IGUAL DIFERENTE MAIORIGUAL MENORIGUAL
%token CARCONST INTCONST

%%
programa : declprograma
         ;

declprograma : PRINCIPAL bloco
             ;

bloco : '{' listacomando '}'
      | varsection '{' listacomando '}'
      ;

varsection : '{' listadeclvar '}'
           ;

listadeclvar : IDENTIFICADOR declvar ':' tipo ';' listadeclvar
             | IDENTIFICADOR declvar ':' tipo ';'
             ;

declvar : /* cadeia vazia */
        | ',' IDENTIFICADOR declvar
        ;

tipo : INT
     | CAR
     ;

listacomando : comando
             | comando listacomando
             ;

comando : ';'
        | expr ';'
        | LEIA IDENTIFICADOR ';'
        | ESCREVA expr ';'
        | ESCREVA CADEIACARACTERES ';'
        | NOVALINHA ';'
        | SE '(' expr ')' ENTAO comando FIMSE
        | SE '(' expr ')' ENTAO comando SENAO comando FIMSE
        | ENQUANTO '(' expr ')' comando
        | bloco
        ;

expr : orexpr
     | IDENTIFICADOR '=' expr
     ;

orexpr : orexpr OU andexpr
       | andexpr
       ;

andexpr : andexpr E eqexpr
        | eqexpr
        ;

eqexpr : eqexpr IGUAL desigexpr
       | eqexpr DIFERENTE desigexpr
       | desigexpr
       ;

desigexpr : desigexpr '<' addexpr
          | desigexpr '>' addexpr
          | desigexpr MAIORIGUAL addexpr
          | desigexpr MENORIGUAL addexpr
          | addexpr
          ;

addexpr : addexpr '+' mulexpr
        | addexpr '-' mulexpr
        | mulexpr
        ;

mulexpr : mulexpr '*' unexpr
        | mulexpr '/' unexpr
        | unexpr
        ;

unexpr : '-' primexpr
       | '!' primexpr
       | primexpr
       ;

primexpr : IDENTIFICADOR
         | CARCONST
         | INTCONST
         | '(' expr ')'
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
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "ERRO: %s na linha %d\n", s, yylineno);
}