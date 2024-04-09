%{
//-----------------------------//
// Ne PAS modifier ce fichier. //
//-----------------------------//

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tp.h"
#include "signed.h"
#include "y.tab.h"

void yyerror(char *);
%}

%option noinput nounput

%x SET_BASE

%%

[[:digit:]]+	{
    yylval.signed_number = signed_number_new(yyleng, 1);
    for (int i = 0; i < yyleng; i++) {
      yylval.signed_number->number->digit[yylval.signed_number->number->n - 1 - i] = yytext[i] - '0';
      if (yytext[i] - '0' >= BASE){
        fprintf(stderr, "Nombre %s : chiffre %c trop grand pour la base (base actuelle : %d)\n", yytext, yytext[i], BASE);
        return LEXICAL_ERROR;
      }
    }
    return NUMBER;
}

<SET_BASE>[[:digit:]]+  {
    BEGIN INITIAL;
    yylval.int_value = atoi(yytext);
    if (yylval.int_value < 2 || yylval.int_value > 10) {
        fprintf(stderr, "Base %d invalide (elle doit être entre 2 et 10)\n", yylval.int_value);
        return LEXICAL_ERROR;
    }
    return NEWBASE;
}

<SET_BASE>"("  { return '('; }

"len"          { return LENGTH; }

"exit" |
"quit"         { return EXIT; }

"base"         { BEGIN SET_BASE; return BASETOK; }

[[:alpha:]_][[:alnum:]_]*   {
    yylval.name = strdup(yytext);
    return IDENTIFIER;
}

"\n"            { return ';'; }

"*k"            |
"**"            { return MKAR; }
"=="            { yylval.int_value = 0; return EQ; }
"<"             { yylval.int_value = -1; return '<'; }
">"             { yylval.int_value = 1; return '>'; }

[[:space:]]     {}

.			    { return yytext[0]; }

%%
