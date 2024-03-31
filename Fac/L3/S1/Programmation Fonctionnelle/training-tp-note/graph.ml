
(****** Définition du type graph *******)

type graph = G of int * (int * int) list;;

(***** Exemples *****)

(* Exemple de la feuille *)
let exemple_01 = G(8,[(1,2);(2,4);(2,5);(3,1);
	(5,2);(5,7);(6,7);(7,6);(7,7)]);;

(* Graphe vide (à 0 sommets) *)
let g_empty = G(0,[]);;


(* Graphes sans arêtes *)
let isolated_01 = G(1,[]);; (* 1 sommet *)
let isolated_02 = G(2,[]);; (* 2 sommets *)
let isolated_03 = G(3,[]);; (* 3 sommets *)
let isolated_04 = G(4,[]);; (* 4 sommets *) 


(* Graphes contenant un unique chemin (question 2 de l'exercice 1) *)
let path_01 = G(1,[]);; (* 1 sommet *)
let path_02 = G(2,[(1,2)]);; (* 2 sommets *)
let path_03 = G(3,[(1,2);(2,3)]);; (* 3 sommets *)
let path_04 = G(4,[(1,2);(2,3);(3,4)]);; (* 4 sommets *) 

(* Cycles (question 3 de l'exercice 1) *)
let cycle_01 = G(1,[(1,1)]);; (* 1 sommet *)
let cycle_02 = G(2,[(1,2);(2,1)]);; (* 2 sommets *)


(******* Exercice 1 *******)
(*   Exemples de Graphes  *)

(* Question 1: représentation de l'exemple 02 *)

let exemple_02 = G(9, [(1, 2); (1, 5); (2, 3); (2, 6); (3, 4); (5, 8); (6, 8); (7, 9); (8, 5); (8, 8); (9, 3); (9, 9)]);;

(* Question 2: génération d'un chemin*)

let gen_path n =
	let rec aux count acc =
		if count = 1 then
			acc
		else
			aux (count - 1) ((count - 1, count) :: acc)
		in G(n, aux n [])

(* Question 3: génération d'un cycle *)

let gen_cycle n =
	let rec aux count acc =
		if count = 1 then
			acc @ [(n, 1)]
		else
			aux (count - 1) ((count - 1, count) :: acc)
		in G(n, aux n [])


(* Question 4: génération d'un graphe complet *)

let gen_complete n =
	let rec aux count c2 acc =
		if count > n then
			acc
		else
			if c2 <= n then
				aux count (c2 + 1) ((count, c2) :: acc)
			else
				aux (count + 1) 1 acc
		in G(n, aux 1 1 [])

(******* Exercice 2 *******)
(* Fonctions sur les Graphes *)


(* Question 1: tester si la représentation d'un graphe est correcte *)

let is_correct g =
		match g with
		| G(n, l) ->
			let rec aux l nb_arete =
				match l with
				| [] -> if n = nb_arete then true else false
				| (h1, h2) :: t ->
				if h1 > n || h2 > n then
					false
				else
					if h1 = h2 then
						aux t nb_arete
					else
						aux t (nb_arete + 1)
			in aux l 0


(* Question 2: tester si un graphe contient l'inverse de chacune de ses arêtes *)

let is_inverse g =
	let G(n, l) = g in
	let rec aux aretes =
		match aretes with
		| [] -> true
		| (h1, h2) :: t ->
			if List.mem (h2, h1) aretes then
				aux t
			else
				false
	in aux l

(* Question 3: simplifier la représentation d'un graphe en retirant les mentions redondantes de la même arête *)

let simplify = fun g -> failwith "à écrire";;

(* Question 4: compter le nombre d'arêtes dans un graphe *)

let number_of_edges = fun g -> failwith "à écrire";;

(* Question 5: liste d'adjacence d'un sommet *)

let list_adj = fun g i -> failwith "à écrire";;

(* Question 6: chemin de longueur bornée *)

let rec bounded_path = fun g i j n -> failwith "à écrire";;

(* Question 7: chemin de longueur arbitraire *)

let exists_path = fun g r s -> failwith "à écrire";;
