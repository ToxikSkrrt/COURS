(* Exercice 7.1 *)

(* 1. *)
let interval_list (n : int) (p : int) : int list =
  let rec aux n acc =
    if n > p then
      List.rev acc
    else
      aux (n + 1) (n::acc)
  in aux n []

let map (f : 'a -> 'b) (l : 'a list) : 'b list =
  let rec aux l acc =
    match l with
    | [] -> List.rev acc
    | h::t -> aux t ((f h)::acc)
  in aux l []

let list_length (l : 'a list) : int =
  let rec aux l acc =
    match l with
    | [] -> acc
    | h::t -> aux t (acc + 1)
  in aux l 0

let filter (pred : 'a -> bool) (l : 'a list) : 'a list =
  let rec aux l acc =
    match l with
    | [] -> List.rev acc
    | h::t ->
      if pred h then
        aux t (h::acc)
      else
        aux t acc
  in aux l []

(* 2. *)
type 'a mylist = Nil | C of 'a * 'a mylist

let list_of_mylist (l : 'a mylist) : 'a list =
  let rec aux l acc =
    match l with
    | Nil -> List.rev acc
    | C(h, t) -> aux t (h::acc)
  in aux l []

let mylist_of_list (l : 'a list) : 'a mylist =
  let rec aux l acc =
    match l with
    | [] -> acc
    | h::t -> aux t (C(h, acc))
  in aux (List.rev l) Nil

let replicate (x : 'a) (k : int) : 'a list =
  let rec aux c acc =
    if c > k then
      acc
    else
      aux (c + 1) (x::acc)
  in aux 1 []

(*
   type : 'a -> int -> 'a list
*)

