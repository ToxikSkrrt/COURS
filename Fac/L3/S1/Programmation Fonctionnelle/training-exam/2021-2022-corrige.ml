(* Exercice 1 /2 *)
(* 1 *)
let f1 pred e = if pred e then 1 else 0
 
(* 2 *)
let f2 a l = l = [a]

(* 3 *)
(*
- : int = 25
 *)
(* 4 *)
(* 
- : int -> int = <fun>
 *)

(* Exercice 2 /6*)
(* 5 *)
(*
val mystere : 'a list -> 'a list -> 'a list = <fun>
 *)
(* 6 *)
(*
utop[5]> mystere [1;2;3] [4;5];;
- : int list = [1; 2; 3; 4; 5]
*)

(* 7 *)
(* Concténation de deux listes d'éléments de même type *)

(* 8 O(length(l1)) *)

(* 9 *)
let mystere_rt l1 l2 =
  let rec aux l1 l2 = 
    match l1 with
      [] -> l2
    | h1 :: t1 -> aux t1 (h1 :: l2)
in aux (List.rev l1) l2

(* Exercice 3 *)
(* 10 *)
let compose f g = fun x -> f (g x)

(* 11 *)
let compose_gen fonctions =
  List.fold_left compose  (fun x -> x) fonctions

(* Exercice 3 *)
(* 12 *)
let make_point x y = P(x, y)

(* 13 *)
let cx point = let P(x, y) = point in x
let cy point = let P(x, y) = point in y

(* 14 *)
let next_point point (transformation : transformation) = transformation point

(* 15 *)
let translation dx dy =
  fun point -> make_point
                 (cx point +. dx)
                 (cy point +. dy)

(* 16 *)
let rec next_point_gen point transformations =
  next_point point (compose_gen transformations)
    
(* 17 *)
let count_sequences l n =
  let rec aux l x nb_x nb_seq =
    match l with
      [] -> if nb_x >= n then succ nb_seq else nb_seq
    | e :: t -> if x = e then aux t x (succ nb_x) nb_seq
                else aux t e 1 (if nb_x >= n then succ nb_seq else nb_seq)
  in match l with
       [] -> 0
     | x :: t -> aux t x 1 0
                   
