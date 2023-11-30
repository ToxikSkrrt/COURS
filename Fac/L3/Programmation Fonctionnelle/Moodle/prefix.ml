(*
  Écrire une fonction prefix de type 'a list -> int -> 'a list, telle que prefix l n renvoie la liste des n premiers éléments de l.
  Si n est négatif, renvoyer [] et si l a moins de n éléments, renvoyer l.
  Exemple :prefix [1; 2; 3; 4] 2 doit renvoyer [1; 2].   
*)

let prefix l n =
  let rec aux l n acc =
    match l with
    | [] -> List.rev acc
    | h :: t ->
      if n < 1 then
        List.rev acc
      else
        aux t (n - 1) (h :: acc)
  in aux l n []

let _ = prefix [1; 2; 3; 4] 2