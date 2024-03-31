open Ast

let rec simplify_expr expr =
  (match expr with
  | Binop (op, e1, e2, annotation) ->
    let s1 = simplify_expr e1 in let s2 = simplify_expr e2 in 
    (match op with
    | Add ->
      (match s1, s2 with
      | Cst_i (v1, _), Cst_i (v2, _) -> Cst_i (v1 + v2, annotation)
      | Cst_f (v1, _), Cst_f (v2, _) -> Cst_f (v1 +. v2, annotation)
      | _ -> failwith "type error")
    | Sub ->
      (match s1, s2 with
      | Cst_i (v1, _), Cst_i (v2, _) -> Cst_i (v1 - v2, annotation)
      | Cst_f (v1, _), Cst_f (v2, _) -> Cst_f (v1 -. v2, annotation)
      | _ -> failwith "type error")
    | Mul ->
      (match s1, s2 with
      | Cst_i (v1, _), Cst_i (v2, _) -> Cst_i (v1 - v2, annotation)
      | Cst_f (v1, _), Cst_f (v2, _) -> Cst_f (v1 *. v2, annotation)
      | _ -> failwith "type error")
    | Div ->
      (match s1, s2 with
      | Cst_i (v1, _), Cst_i (v2, _) -> Cst_i (v1 / v2, annotation)
      | Cst_f (v1, _), Cst_f (v2, _) -> Cst_f (v1 /. v2, annotation)
      | _ -> failwith "type error")
    | Mod ->
      (match s1, s2 with
      | Cst_i (v1, _), Cst_i (v2, _) -> Cst_i (v1 mod v2, annotation)
      | Cst_f (v1, _), Cst_f (v2, _) -> Cst_f (mod_float v1 v2, annotation)
      | _ -> failwith "type error")
    | And ->
      (match s1, s2 with
      | Cst_b (v1, _), Cst_b (v2, _) -> Cst_b (v1 && v2, annotation)
      | _ -> failwith "type error")
    | Or ->
      (match s1, s2 with
      | Cst_b (v1, _), Cst_b (v2, _) -> Cst_b (v1 || v2, annotation)
      | _ -> failwith "type error")
    | Eq ->
      (match s1, s2 with
      | Cst_i (v1, _), Cst_i (v2, _) -> Cst_b (v1 = v2, annotation)
      | Cst_f (v1, _), Cst_f (v2, _) -> Cst_b (v1 = v2, annotation)
      | Cst_b (v1, _), Cst_b (v2, _) -> Cst_b (v1 = v2, annotation)
      | _ -> failwith "type error")
    | Neq ->
      (match s1, s2 with
      | Cst_i (v1, _), Cst_i (v2, _) -> Cst_b (not (v1 = v2), annotation)
      | Cst_f (v1, _), Cst_f (v2, _) -> Cst_b (not (v1 = v2), annotation)
      | Cst_b (v1, _), Cst_b (v2, _) -> Cst_b (not (v1 = v2), annotation)
      | _ -> failwith "type error")
    | Lt ->
      (match s1, s2 with
      | Cst_i (v1, _), Cst_i (v2, _) -> Cst_b (v1 < v2, annotation)
      | Cst_f (v1, _), Cst_f (v2, _) -> Cst_b (v1 < v2, annotation)
      | _ -> failwith "type error")
    | Gt ->
      (match s1, s2 with
      | Cst_i (v1, _), Cst_i (v2, _) -> Cst_b (v1 > v2, annotation)
      | Cst_f (v1, _), Cst_f (v2, _) -> Cst_b (v1 > v2, annotation)
      | _ -> failwith "type error")
    | Leq ->
      (match s1, s2 with
      | Cst_i (v1, _), Cst_i (v2, _) -> Cst_b (v1 <= v2, annotation)
      | Cst_f (v1, _), Cst_f (v2, _) -> Cst_b (v1 <= v2, annotation)
      | _ -> failwith "type error")
    | Geq ->
      (match s1, s2 with
      | Cst_i (v1, _), Cst_i (v2, _) -> Cst_b (v1 >= v2, annotation)
      | Cst_f (v1, _), Cst_f (v2, _) -> Cst_b (v1 >= v2, annotation)
      | _ -> failwith "type error"))
  | Unop (op, e,annotation) ->
    let s = simplify_expr e in
    (match op with
    | UMin ->
      (match s with
      | Cst_i (v, _) -> Cst_i (0 - v, annotation)
      | Cst_f (v, _) -> Cst_f (0. -. v, annotation)
      | _ -> failwith "type error")
    | Not ->
      (match s with
      | Cst_b (v, _) -> Cst_b (not (v), annotation)
      | _ -> failwith "type error"))
  | Array_val (_, _,_) -> expr
  | Func (name, args,annotation) -> expr
  | Cst_i (_,_) -> expr
  | Cst_f (_,_) -> expr
  | Cst_b (_,_) -> expr
  | Var (_,_) -> expr
  | Size_tab (_,_) -> expr
    

  
(*to modify*)
(*match expr with
  | Unop (op, e,annotation) -> expr
  | Binop (op, e1, e2,annotation) -> expr
  | Array_val (tab, e,annotation) -> expr
  | Func (name, args,annotation) -> expr
  | Cst_i (i,annotation) -> expr
  | Cst_f (f,annotation) -> expr
  | Cst_b (b,annotation) -> expr
  | Var (s,annotation) -> expr
  | Size_tab (s,annotation) -> expr*)

let rec simplify_instruction instruction =
  ignore simplify_instruction;
  instruction
(*to modify*)
(*match instruction with
  | Affect (name, expr,annotation) -> instruction
  | Block (l,annotation) -> instruction
  | IfThenElse (test, i_then, i_else,annotation) -> instruction
  | While (test, body,annotation) -> instruction
  | Affect_array (name, pos, value,annotation) -> instruction
  | Array_decl (typ, name, size,annotation) -> instruction
  | Proc (name, args,annotation) -> instruction
  | Return (o,annotation) -> instruction
  | Print_str (s,annotation) -> instruction
  | Print_expr (expr,annotation) -> instruction
  | Var_decl (typ, name,annotation) -> instruction*)

let simplify_func_decl = function
  | Func_decl (typ, name, args, body, annotation) ->
      Func_decl (typ, name, args, simplify_instruction body, annotation)
