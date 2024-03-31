(*
   Écrire une fonction mapcan f l de type 
  ('a -> 'b list) -> 'a list -> 'b list
  qui prend en paramètres :
  une fonction f de type  ('a -> 'b list).
  une liste  l = [e1; e2; ... ; en] de type 'a list.
  Remarquez que comme  l est de type   ('a list), la fonction f peut s'appliquer aux éléments de l.

  L'appel mapcan f l doit retourner la concaténation des listes f(ei).


  Exemple : mapcan (fun x -> [x; x*x; x*x*x]) [1; 2; 3] retourne la liste d'entiers [1; 1; 1; 2; 4; 8; 3; 9; 27].   
*)

let mapcan f l =
  let rec aux l acc =
    match l with
    | [] -> List.concat (List.rev acc)
    | h :: t -> aux t ((f h) :: acc)
  in aux l []

let _ = mapcan (fun x -> [x; x*x; x*x*x]) [1; 2; 3]
