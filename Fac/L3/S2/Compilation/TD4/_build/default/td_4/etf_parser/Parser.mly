%token ADD SUB
%token MUL DIV REC
%token LPAR RPAR
%token <int> INT
%token EOF

%start <unit> main

%%

main:
| EOF         {}
// | ADD SUB MUL DIV REC LPAR RPAR INT EOF { (* À enlever -- ici pour éviter des warnings !*)}
| expr EOF {}

expr:
| expr ADD term {}
| SUB term {}
| term {}

term:
| term MUL factor {}
| term DIV factor {}
| term REC {}
| factor {}

factor:
| LPAR expr RPAR {}
| INT {}