%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern FILE *yyin;
void yyerror(const char *s);
%}

/* Tokens que não correspondem a apenas um caractere */
%token PRINCIPAL IDENTIFICADOR INT CAR LEIA ESCREVA NOVALINHA
%token SE ENTAO SENAO FIMSE ENQUANTO
%token CADEIACARACTERES OU E IGUAL DIFERENTE MAIORIGUAL MENORIGUAL
%token CARCONST INTCONST

%%
programa : /* vazio */
         ;
%%

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Uso correto: ./g-v1 nome_arquivo\n");
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("arquivo nao pode ser aberto\n");
        return 1;
    }

    yyparse();
    fclose(yyin);
    return 0;
}

void yyerror(const char *s) {
    printf("ERRO: %s\n", s);
}