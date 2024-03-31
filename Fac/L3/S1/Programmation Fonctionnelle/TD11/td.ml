(* Exercice 9.1 *)

(* 1. *)
let rec append l1 l2 =
  match l1 with
  [] -> l2
  | h :: t -> h :: append t l2

(*
   Il y a n appels récursifs, n étant la taille de l1.
*)

(* 2. *)
(*
   L'opérateur :: est utilisé n fois, n étant la taille de l1
*)

(* 3. *)
let rec reverse l =
  match l with
  [] -> []
  | h :: t -> append (reverse t) [h]
