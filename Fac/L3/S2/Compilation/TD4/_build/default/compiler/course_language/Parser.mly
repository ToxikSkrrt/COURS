%{
    open Ast
%}

%token IF
%token THEN
%token ELSE
%token WHILE
%token L_PAR
%token R_PAR
%token L_CUR_BRK
%token R_CUR_BRK
%token L_SQ_BRK
%token R_SQ_BRK
%token ADD
%token SUB
%token MUL
%token DIV
%token MOD
%token AND
%token OR
%token NOT
%token EQ
%token NEQ
%token LT
%token GT
%token LEQ
%token GEQ
%token COMMA
%token SEMICOLON
%token ASSIGN
%token DEF
%token DOT
%token PRINT
%token SIZE
%token RETURN
%token INT_TYP
%token FLOAT_TYP
%token BOOL_TYP
%token NULL_TYP
%token VAR
%token <string> ID
%token <string> STRING
%token <int> INT
%token <float> FLOAT
%token <bool> BOOL
%token EOF

%start <Ast.t> main

%left ADD SUB OR
%left EQ NEQ LEQ GEQ LT GT
%left MUL DIV AND MOD
%nonassoc NOT

%%

main:
| l = function_list EOF { Program (List.rev l) (*Le List.rev est là si vous construisez la liste à l’envers (ce qui arrive si vous le faites avec une associativité à gauche (si vous voulez que l’arbre reste petit)). Si vous la construisez dans le bon sens, retirez le List.rev.*)}
| i = instruction EOF { Instruction i }
| e = expression EOF { Expression e }

function_list:
|  { [] }
// | IF THEN ELSE WHILE L_PAR R_PAR L_CUR_BRK R_CUR_BRK L_SQ_BRK R_SQ_BRK ADD SUB MUL DIV MOD AND OR NOT EQ NEQ LT GT LEQ GEQ COMMA SEMICOLON ASSIGN DEF DOT PRINT SIZE RETURN INT_TYP FLOAT_TYP BOOL_TYP NULL_TYP VAR ID STRING INT FLOAT BOOL EOF { (*À retirer -- ici pour éviter les warnings avant de commencer*) []}

// Pour la définition de fonction, je ne vois pas comment gérer une liste de tokens, ni où mettre la définition,
// donc j'ai décidé de la mettre à part même si elle ne sert à rien en l'état.
func:
| t = typ s = ID L_PAR i1 = instruction COMMA i2 = instruction R_PAR DEF L_CUR_BRK i = instruction R_CUR_BRK { Func_decl (t, s, [i1; i2], i, Annotation.create $loc) }

instruction:
| s = ID ASSIGN e = expression { Affect (s, e,  Annotation.create $loc) }
// Je pense qu'il faut modifier SEMICOLON, mais après un nombre beaucoup trop élevé de tentatives,
// cela n'a jamais rien donné de concluant, notamment l'impossibilté d'avoir à la fois les accolades fonctionnelles
// et le ";". Donc j'ai fini par tenter de faire tout le reste à la place.
| SEMICOLON { Block ([], Annotation.create $loc) }
| IF L_PAR e = expression R_PAR THEN L_CUR_BRK iTrue = instruction R_CUR_BRK ELSE L_CUR_BRK iFalse = instruction R_CUR_BRK { IfThenElse (e, iTrue, iFalse, Annotation.create $loc) }
| WHILE e = expression L_CUR_BRK i = instruction R_CUR_BRK { While (e, i, Annotation.create $loc) }
| s = ID L_SQ_BRK eIndex = expression R_SQ_BRK ASSIGN eValue = expression { Affect_array (s, eIndex, eValue, Annotation.create $loc) }
| t = typ s = ID L_SQ_BRK e = expression R_SQ_BRK { Array_decl (t, s, e, Annotation.create $loc) }
| RETURN e = expression { Return (Some (e), Annotation.create $loc) }
| PRINT s = STRING { Print_str (s, Annotation.create $loc) }
| PRINT e = expression { Print_expr(e, Annotation.create $loc) }
| t = typ s = ID { Var_decl (t, s, Annotation.create $loc) }

expression:
| L_PAR e = expression R_PAR { e }
| i = INT { Cst_i (i, Annotation.create $loc) }
| f = FLOAT { Cst_f (f, Annotation.create $loc) }
| b = BOOL { Cst_b (b, Annotation.create $loc) }
| VAR typ s = ID { Var (s, Annotation.create $loc) }
| e1 = expression bin = binop e2 = expression { Binop (bin, e1, e2, Annotation.create $loc) }
| u = unop e = expression { Unop (u, e, Annotation.create $loc) }
| s = ID L_SQ_BRK e = expression R_SQ_BRK { Array_val (s, e, Annotation.create $loc) }
| s = ID DOT SIZE { Size_tab (s, Annotation.create $loc) }
| s = ID L_PAR e1 = expression COMMA e2 = expression R_PAR { Func (s, [e1; e2], Annotation.create $loc) }

%inline binop:
| ADD { Add }
| SUB { Sub }
| MUL { Mul }
| DIV { Div }
| MOD { Mod }
| AND { And }
| OR { Or }
| EQ { Eq }
| NEQ { Neq }
| LT { Lt }
| GT { Gt }
| LEQ { Leq }
| GEQ { Geq }

%inline unop:
| SUB { UMin }
| NOT { Not }

%inline typ:
| INT_TYP { TInt }
| BOOL_TYP { TBool }
| NULL_TYP { TNull }
| FLOAT_TYP { TFloat }
