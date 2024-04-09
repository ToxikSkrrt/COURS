%{
//-----------------------------//
// Ne PAS modifier ce fichier. //
//-----------------------------//

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// gmp.h après stdio.h
#include <gmp.h>

#include "main.h"
#include "number.h"
#include "signed.h"
#include "test.h"

int yylex(void);

void yyerror(char *s);

void prompt(void);
%}

%code {
  void yyerror(char *s){
    if (s)
      fprintf(stderr, "Erreur syntaxique\n");
  }

  void prompt(void){
    printf("%s", PROMPT);
    fflush(stdout);
  }
}

%union{
    char          *name;
    short          int_value;
    signed_number *signed_number;
 }

%token <signed_number>NUMBER
%token <name>IDENTIFIER
%token <int_value>NEWBASE

%type  <signed_number>e

%left  <int_value>'<' <int_value>'>' <int_value>EQ
%right '='
%left  '+' '-'
%left  '*' MKAR
%nonassoc UMINUS
%nonassoc LENGTH
%token EXIT
%token BASETOK
%token LEXICAL_ERROR

%output "y.tab.c"

%%
s:              s ';' {prompt();}

        |       s e ';' {
  char *result = signed_number_to_string($2);
  printf("-- Calculé : %s\n", result);
  signed_number_free($2);
  free(result);
  prompt();
 }

        |       s LENGTH '(' e ')' ';' {
  printf("%d\n", signed_number_length($4));
  signed_number_free($4);
  prompt();
 }

        |       s EXIT {
  printf("Bye!\n");
  exit(0);
 }

        |       s BASETOK '(' NEWBASE ')' ';' {
  printf("Nouvelle base : %d\n", BASE = $4);
  prompt();
 }

        |       s e EQ e ';'    {
  comparison($2, $4, $3);
  prompt();
 }

        |       s e '<' e ';'   {
  comparison($2, $4, $3);
  prompt();
 }

        |       s e '>' e ';'   {
  comparison($2, $4, $3);
  prompt();
 }

        |       s LEXICAL_ERROR ';' {
  yyerrok;
  prompt();
 }
        |       s error ';' {
  yyerrok;
  prompt();
 }
        |       %empty
        ;

e:              e '+' e { $$ = signed_output_result($1, $3, signed_number_addition, mpz_add, "+"); }
        |       e '-' e { $$ = signed_output_result($1, $3, signed_number_substraction, mpz_sub, "-"); }
        |       e '*' e { $$ = signed_output_result($1, $3, signed_number_multiplication_recursive, mpz_mul, "*");}
        |       e MKAR e { $$ = signed_output_result($1, $3, signed_number_multiplication_karatsuba, mpz_mul, "*k");}
        |       '(' e ')' {$$ = $2;}
        |       '-' e %prec UMINUS { $$ = signed_number_negate($2); }
        |       NUMBER

%%
