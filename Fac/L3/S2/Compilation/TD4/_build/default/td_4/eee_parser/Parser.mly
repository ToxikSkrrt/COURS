%token ADD SUB
%token MUL DIV REC
%token LPAR RPAR
%token <int> INT
%token EOF

%start <unit> main

%left ADD SUB
%left MUL DIV

%%

main:
| EOF   {}
// | ADD SUB MUL DIV REC LPAR RPAR INT EOF { (* À enlever -- ici pour éviter des warnings !*)}
| expr EOF {}

expr:
| expr ADD expr {}
| expr SUB expr {}
// | SUB expr {}
| expr MUL expr {}
| expr DIV expr {}
// | expr REC {}
| LPAR expr RPAR {}
| INT {}
