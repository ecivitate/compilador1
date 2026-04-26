%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "g-v1.tab.h"

#define YY_USER_ACTION \
    yylloc.first_line = yylloc.last_line = yylineno;
%}

%option yylineno noyywrap

LETRA       [a-zA-Z]
DIGITO      [0-9]
ID          ({LETRA}|_)(({LETRA}|{DIGITO}|_))*
INTCONST_R  {DIGITO}+
CAR_ESC     \\[ntr'\"\\]
CAR_NORM    [^\\'\n]
CARCONST_R  \'({CAR_ESC}|{CAR_NORM})\'

%x comentario

%%
"/*"                    { BEGIN(comentario); }

<comentario>[^*\n]+     ;
<comentario>"*"+[^*/\n]* ;
<comentario>\n          ;
<comentario>"*"+"/"     { BEGIN(INITIAL); }

<comentario><<EOF>>     {
                           printf("ERRO: COMENTARIO NAO TERMINA %d\n", yylineno);
                           exit(1);
                        }

"principal"             { return PRINCIPAL; }
"int"                   { return INT; }
"car"                   { return CAR; }
"leia"                  { return LEIA; }
"escreva"               { return ESCREVA; }
"novalinha"             { return NOVALINHA; }
"se"                    { return SE; }
"entao"                 { return ENTAO; }
"senao"                 { return SENAO; }
"fimse"                 { return FIMSE; }
"enquanto"              { return ENQUANTO; }

"||"                    { return OU; }
"&"                     { return E; }
"=="                    { return IGUAL; }
"!="                    { return DIFERENTE; }
">="                    { return MAIORIGUAL; }
"<="                    { return MENORIGUAL; }

\"([^\"\n]|\\.)*\"      { yylval.lexeme = strdup(yytext); return CADEIACARACTERES; }

\"([^\"\n]|\\.)*\n      {
                           printf("ERRO: CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA %d\n", yylineno);
                           exit(1);
                        }

{CARCONST_R}            { yylval.lexeme = strdup(yytext); return CARCONST; }
{INTCONST_R}            { yylval.lexeme = strdup(yytext); return INTCONST; }
{ID}                    { yylval.lexeme = strdup(yytext); return IDENTIFICADOR; }

"{"                     { return '{'; }
"}"                     { return '}'; }
"("                     { return '('; }
")"                     { return ')'; }
";"                     { return ';'; }
","                     { return ','; }
":"                     { return ':'; }
"="                     { return '='; }
"+"                     { return '+'; }
"-"                     { return '-'; }
"*"                     { return '*'; }
"/"                     { return '/'; }
"<"                     { return '<'; }
">"                     { return '>'; }
"!"                     { return '!'; }

[ \t\r]+                ;
\n                      ;

.                       {
                           printf("ERRO: CARACTERE INVALIDO %d\n", yylineno);
                           exit(1);
                        }

<<EOF>>                 { return 0; }
%%