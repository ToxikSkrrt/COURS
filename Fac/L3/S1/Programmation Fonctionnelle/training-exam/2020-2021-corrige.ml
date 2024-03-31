(* Exercice 1 *)
(* 1. à tester soi-même *)
(* 2. à tester soi-même *)
(* 3. mystere = remove_duplicates *)
(* 4. *)
let remove_duplicates_rt l =
  let rec aux l nl =
    match l with
      [] -> List.rev nl
    | x :: tl ->  aux (remove x tl) (x :: nl)
  in aux l []

(* Exercice 2 *)
(* 5. *)   
let couples_elements couples =
  remove_duplicates
    (List.fold_right
       (fun couple l -> (fst couple) :: (snd couple) :: l)
       couples
       [])

(* Exercice 3 *)
(* 6. *)
let rec rel_adds couples relation =
  match  couples with
    [] -> relation
  | couple :: couples' ->
     rel_adds couples' (rel_add couple relation)

(* 7 *)
let add_reflexive_couples elements relation =
  rel_adds
    (List.map (fun e -> (e, e)) elements)
    relation

(* 8 *)
let rel_make_reflexive relation =
  add_reflexive_couples (rel_elements relation) relation

(* 9 *)
let rel_add couple (relation : 'a relation) =
  if List.mem couple relation then relation
  else couple :: relation

(* 10 *)
let rel_member couple relation = relation.rel_fun couple

(* 11 *)                               
let rel_add couple relation =
  if rel_member couple relation
  then relation
  else
    { rel_elts = add_couple_to_elements couple relation.rel_elts;
      rel_fun = fun c -> c = couple || rel_member c relation
    }

(* 12 *)  
let couple_rev couple = (snd couple, fst couple)

let rel_make_symmetric relation =
  { rel_elts = relation.rel_elts;
    rel_fun =
      fun c ->
      rel_member c relation || rel_member (couple_rev c) relation
  }
