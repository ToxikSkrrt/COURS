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
  | Array_val (tab, e,annotation) -> Array_val (tab, simplify_expr e, annotation)
  | Func (name, args,annotation) ->
    (let rec aux l acc =
      match l with
      | [] -> Func (name, List.rev acc, annotation)
      | h :: t -> aux t ((simplify_expr h) :: acc)
    in aux args [])
  | Cst_i (i,annotation) -> expr
  | Cst_f (f,annotation) -> expr
  | Cst_b (b,annotation) -> expr
  | Var (s,annotation) -> expr
  | Size_tab (s,annotation) -> expr)
    
  
let rec simplify_instruction instruction =
  (match instruction with
  | Affect (name, expr,annotation) -> Affect (name, simplify_expr expr, annotation)
  | Block (l,annotation) ->
    (let rec aux l acc =
      match l with
      | [] -> Block (List.rev acc, annotation)
      | h :: t -> aux t ((simplify_instruction h) :: acc)
    in aux l [])
  | IfThenElse (test, i_then, i_else,annotation) ->
    (match test with
    | Cst_b (true, _) -> i_then
    | Cst_b (false, _) -> i_else
    | _ -> instruction)
  | While (test, body,annotation) ->
    (match test with
    | Cst_b (false, _) -> Block ([], annotation)
    | _ -> instruction) (* uwu *)
  | Affect_array (name, pos, value,annotation) -> Affect_array (name, simplify_expr pos, simplify_expr value, annotation)
  | Array_decl (typ, name, size,annotation) -> Array_decl (typ, name, simplify_expr size, annotation)
  | Proc (name, args,annotation) ->
    (let rec aux l acc =
      match l with
      | [] -> Proc (name, List.rev acc, annotation)
      | h :: t -> aux t ((simplify_expr h) :: acc)
    in aux args [])
  | Return (o,annotation) ->
    (match o with
    | Some v -> Return (Some (simplify_expr v), annotation)
    | None -> Return (None, annotation))
  | Print_str (s,annotation) -> instruction
  | Print_expr (expr,annotation) -> Print_expr (simplify_expr expr, annotation)
  | Var_decl (typ, name,annotation) -> instruction)


let simplify_func_decl = function
  | Func_decl (typ, name, args, body, annotation) ->
      Func_decl (typ, name, args, simplify_instruction body, annotation)
