%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "g-v1.tab.h"
%}

%option yylineno noyywrap

LETRA       [a-zA-Z]
DIGITO      [0-9]
ID          ({LETRA}|_)(({LETRA}|{DIGITO}|_))*
INTCONST_R  [+-]?{DIGITO}+
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
                           printf("ERRO: COMENTÁRIO NAO TERMINA %d\n", yylineno);
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

\"([^\"\n]|\\.)*\"      { return CADEIACARACTERES; }

\"([^\"\n]|\\.)*\n      {
                           printf("ERRO: CADEIA DE CARACTERES OCUPA MAIS DE UMA LINHA %d\n", yylineno);
                           exit(1);
                        }

{CARCONST_R}            { return CARCONST; }
{INTCONST_R}            { return INTCONST; }
{ID}                    { return IDENTIFICADOR; }

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
                           printf("ERRO: CARACTERE INVÁLIDO %d\n", yylineno);
                           exit(1);
                        }
%%