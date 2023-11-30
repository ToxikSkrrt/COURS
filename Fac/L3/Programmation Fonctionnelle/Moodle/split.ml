(*
  Écrire une fonction split de type ('a -> bool) -> 'a list -> 'a list * 'a list  qui, étant donnés un prédicat pred et une liste l, renvoie un couple de listes (l1,l2) tel que : 
    l1 contient tous les éléments de la liste l qui vérifient  pred.
    l2 contient tous les éléments de la liste l qui ne vérifent pas pred.
  L’ordre des éléments dans l1 et l2 doit être identique à celui dans l.

  Par exemple split (fun x -> x mod 2 = 0) [1; 2; 3; 4; 5; 6] retourne ([2; 4; 6], [1; 3; 5]).   
*)

let split pred l =
  let rec aux l l1 l2 =
    match l with
    | [] -> (List.rev l1, List.rev l2)
    | h::t ->
      if pred h then
        aux t (h::l1) l2
      else
        aux t l1 (h::l2)
  in aux l [] []