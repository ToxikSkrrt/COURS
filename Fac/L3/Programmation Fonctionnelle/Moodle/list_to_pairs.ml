(*
   Écrire une fonction list_to_pairs l de type  'a list -> ('a * int) list qui retourne une liste dont les éléments sont les paires (e, k) où e est une élément de l et k son nombre d'occurrences dans l.
   L'ordre des paires n'est pas important.


  Exemple : list_to_pairs [1; 1; 2; 2; 5; 1; 1; 42; 2] renvoie la liste [(1, 4); (2, 3); (5, 1); (42, 1)]. On pourra utiliser des fonctions auxiliaires et des fonctions du module List.  
*)

let update_aux elem (x, n) =
  if elem = x then
    (x, n + 1)
  else
    (x, n)

let list_to_pairs l =
  let rec aux l acc =
    match l with
    | [] -> List.rev acc
    | h :: t ->
      let update_acc = List.map (update_aux h) acc in
      if List.exists (fun (x, _) -> x = h) acc then
        aux t update_acc
      else
        aux t ((h, 1) :: acc)
  in aux l []


let _ = list_to_pairs [1; 1; 2; 2; 5; 1; 1; 42; 2]