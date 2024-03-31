(* 9.1 *)
type 'a option = Some of 'a | None
(* VU *)

(* 9.2 *)

(* 1. *)
type ('k, 'v) dict = 'k -> 'v option

(* 2. *)
let empty_dict : ('k, 'v) dict = fun (k : 'k) -> None

(* 3. *)
let find (key : 'k) (dict : ('k, 'v) dict) : 'v option =
  dict key

(* 4. *)
let add_or_update (key : 'k) (value : 'v) (dict : ('k, 'v) dict) : ('k, 'v) dict =
  fun (k : 'k) -> if k = key then Some(value) else dict k
  

let remove (key : 'k) (dict : ('k, 'v) dict) : ('k, 'v) dict =
  fun (k : 'k) -> if k = key then None else dict k

(*
(* 9.3 *)

(* 1. *)
type ('k, 'v) dict = ('k * 'v) list

(* 2. *)
let empty_dict : ('k, 'v) dict = []

(* 3. *)
let rec find (key : 'k) (dict : ('k, 'v) dict) : 'v option =
  match dict with
  | [] -> None
  | (k, v)::t ->
    if k = key then
      Some(v)
    else
      find key t

(* 4. *)
let rec add_or_update (key : 'k) (value : 'v) (dict : ('k, 'v) dict) : ('k, 'v) dict = 
  match dict with
  | [] -> [(key, value)]
  | (k, v)::t ->
    if k = key then
      (key, value)::t
    else
      (k, v)::(add_or_update key value t)

let add_or_update_term (key : 'k) (value : 'v) (dict : ('k, 'v) dict) : ('k, 'v) dict =
  let rec aux dict acc found =
    match dict with
    | [] -> if found = true then List.rev acc else List.rev ((key, value)::acc)
    | (k, v)::t ->
      if k = key then
        aux t ((key, value)::acc) true
      else aux t ((k, v)::acc) found
  in aux dict [] false

(* 5. *)
let remove_default (key : 'k) (dict : ('k, 'v) dict) = raise (Failure "Unimplemented")

let remove (key : 'k) (dict : ('k, 'v) dict) : ('k, 'v) dict =
  let rec aux dict acc =
    match dict with
    | [] -> List.rev acc
    | (k, v)::t ->
      if k = key then
        aux t acc
      else
        aux t ((k, v)::acc)
  in aux dict []
*)