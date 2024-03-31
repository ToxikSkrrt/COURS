(* TD 2 *)

(* Exercice 2.1 *)
let test x y z =
  z = x + y
;;

(* Exercice 2.2 *)
let valeur_p4 x =
  3 * (x * x * x * x) + 7 * x - 1
;;

(* Exercice 2.3 *)
let polynome3 a b c =
  fun x -> a * (x * x) + b * x + c
;;

(* Exercice 2.4 *)
(*
  fact 5 -> 5 /= 0 -> 5 * fact 4
    -> 4 /= 0 -> 5 * 4 * fact 3
      -> 3 /= 0 -> 5 * 4 * 3 * fact 2
        -> 2 /= 0 -> 5 * 4 * 3 * 2 * fact 1
          -> 0 /= 0 -> 5 * 4 * 3 * 2 * 1 * fact 0
            -> 0 == 0 -> 5 * 4 * 3 * 2 * 1 = 120
*)

(* Exercice 2.5 *)
let rec pgcd n p =
  if p = 0
  then n
  else pgcd p (n mod p)
;;

(* Exercice 2.6 *)
let rec ack m n =
  if m = 0 then n + 1 else if m > 0 && n = 0 then ack (m - 1) n else ack (m - 1) (ack m (n - 1))
;;

(* Exercice 2.7 *)

(* 1. *)
let rec fib n = if n = 0 || n = 1 then 1 else fib (n - 1) + fib (n - 2)

(*
  2. Oui
*)

(* 3. *)
let rec fib n =
  let rec aux n (a, b) =
    match n with
    | 0 -> 1
    | 1 -> b
    | _ -> aux (n - 1) (b, a + b)
  in
  aux n (1, 1)
;;

(* Exercice 2.8 *)
let rec stairs n =
  match n with
  | 0 -> failwith "bah comment ça 0 marche frérot ??"
  | 1 -> 1
  | 2 -> 2
  | 3 -> 4
  | _ -> stairs (n - 1) + stairs (n - 2) + stairs (n - 3)
;;

(* Exercice 2.9 *)
let rec power b n =
  match b, n with
  | 0, _ -> failwith "Error"
  | _, 0 -> 1
  | _ -> b * power b (n - 1)
;;

(*
  2. Il y a n multiplications effectuées

  3. Si on prend le cas n = 1 comme cas de sortie on peut retirer une multiplication (??)
*)

(* Exercice 2.10 *)
let rec iterate f k =
  match k with
  | 1 -> f
  | _ -> fun x -> f (iterate f (k - 1) x)
;;

(* ------------------------------ *)

(* TD 2 BIS *)

(* Exercice 2.1 *)
let multiplicateur n i = n * i

(* Exercice 2.2 *)
let rec seq_aux n =
  match n with
  | 0 -> 0, 3
  | _ ->
    let u, v = seq_aux (n - 1) in
    v, -v + (2 * u)
;;

let seq n =
  let u, _ = seq_aux n in
  u
;;

(* Exercice 2.3 *)
let derivee f h =
  match h with
  | 0. -> failwith "erreur"
  | _ -> fun x -> (f (x +. h) -. f (x -. h)) /. (2. *. h)
;;

let rec derivee_n n f h = failwith "A FAIRE";;

(* ------------------------------ *)

(* TD 3 *)

(* Exercice 3.1 *)

fun x y -> x, y
(* - : 'a -> 'b -> 'a * 'b = <fun> *)

(* Exercice 3.2 *)
let compose f g x = f (g x)
(* ('a -> 'b) -> ('c -> 'a) -> 'c -> 'b *)

(* Exercice 3.3 *)
let rec fib n =
  match n with
  | 0 -> 1
  | 1 -> 1
  | _ -> fib (n - 2) + fib (n - 1)
;;

let fib n =
  let rec aux n =
    if n = 0
    then 1, 1
    else (
      let u0, u1 = aux (n - 1) in
      u1, u0 + u1)
  in
  let u, _ = aux n in
  u
;;

(* Exercice 3.4 *)

'x', 2.1, (true, 0);;

(* char * float * (bool * int) = 'x', 2.1, (true, 0) *)

3 + 2, false || 2 = 3, "bonjour";;

(* int * bool * char = 5, false, "bonjour" *)

let p = 1, 2 in
snd p, fst p
(* int * int = (2, 1) *)

(* Exercice 3.5 *)

(* int * bool * string *)
(* 2 + 3, 3 = 2, "UwU" = 5, false, "UwU" *)

(* (int * bool) * string *)
(* (2 + 3), 3 = 2), "UwU" = (5, false), "UwU" *)

(* int * (bool * string) *)
(* 2 + 3, (3 = 2, "UwU") = 5, (false, "UwU") *)

(* Exercice 3.6 *)
(* 1. *)
type couleur =
  | Pique
  | Coeur
  | Carreau
  | Trefle

type carte =
  | As of couleur
  | Roi of couleur
  | Dame of couleur
  | Valet of couleur
  | Numero of int * couleur

let couleur_carte carte =
  match carte with
  | As c | Roi c | Dame c | Valet c | Numero (_, c) -> c
;;

(* 2. *)
let est_de_couleur carte couleur = if couleur_carte carte = couleur then true else false

(* 3. *)
let est_une_figure carte =
  match carte with
  | Roi _ | Dame _ | Valet _ -> true
  | _ -> false
;;

(* Exercice 3.7 *)

(* 1. *)
type carburant =
  | Diesel
  | Essence
  | Electrique

(* 2. *)
type vehicule = carburant * int
type vehicule_bis = Vehicule_bis of carburant * int

(* 3. *)
let make_vehicule (carburant : carburant) (nb_wheels : int) : vehicule =
  carburant, nb_wheels
;;

let make_vehicule carburant nb_wheels = Vehicule_bis (carburant, nb_wheels)

(* 4. *)
let carburant_of (vehicule : vehicule) =
  match vehicule with
  | carburant, _ -> carburant
;;

let carburant_of vehicule =
  match vehicule with
  | Vehicule_bis (carburant, _) -> carburant
;;

let nb_wheels_of (vehicule : vehicule) =
  match vehicule with
  | _, nb_wheels -> nb_wheels
;;

let nb_wheels_of vehicule =
  match vehicule with
  | Vehicule_bis (_, nb_wheels) -> nb_wheels
;;

(* 5. *)
let can_run vehicule =
  if carburant_of vehicule = Diesel && nb_wheels_of vehicule >= 4 then false else true
;;

(* 6. *)
let consommation vehicule (n : int) =
  match carburant_of vehicule with
  | Electrique -> 0.1 *. float_of_int n *. 0.25
  | Diesel -> 0.06 *. float_of_int n *. 1.5
  | Essence -> 0.08 *. float_of_int n *. 1.5
;;

let vroum1 = Diesel, 4
let vroum2 = Vehicule_bis (Diesel, 4)

(* ------------------------------ *)

(* TD 3 (BIS) *)

type expr =
Var of string
| Number of float
| Plus of expr * expr
| Minus of expr * expr
| Mult of expr * expr
| Exp of expr

(* Exercice 3.1 *)

(* 1. *)
let vx = Var "x"
let vy = Var "y"

(* 2. *)
let e1 = Plus (Mult (Number 2., vx), Number 1.)

(* 3. *)
let e2 = Plus (Mult (Number 3., Mult (vx, vx)), Plus (Mult (Number 2., vx), Number 1.))

(* 4. *)
let rec derivee var expr =
  match expr with
  | Number c -> Number 0.
  | Var x -> Number 1.
  | Plus (u, v) -> Plus (derivee var u, derivee var v)
  | Minus (u, v) -> Minus (derivee var u, derivee var v)
  | Mult (u, v) -> Plus (Mult (u, derivee var v), Mult (v, derivee var u))
  | Exp u -> Mult (derivee var u, Exp u)
;;

(* 5. *)
let rec derivee_n var expr n =
  let rec aux n acc =
    match n with
    | 1 -> derivee var acc
    | _ -> derivee_n var (derivee var acc) (n - 1)
  in aux n expr
;;

(* ------------------------------ *)

(* TD 4 *)

