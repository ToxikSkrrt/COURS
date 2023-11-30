(*
  Écrire une fonction suffix de type 'a list -> int -> 'a list, telle que suffit l n renvoie la liste des n derniers éléments de l.
  Si n est négatif, renvoyer [] et si l a moins de n éléments, renvoyer l.
  Exemple :suffix [1; 2; 3; 4] 2 doit renvoyer [3; 4].   
*)

let suffix l n =
  let rec aux l m len acc =
    match l with
    | [] -> List.rev acc
    | h :: t ->
      if n < 0 then
        acc
      else
        if m >= len - n then
          aux t (m + 1) len (h :: acc)
        else
          aux t (m + 1) len acc
  in aux l 0 (List.length l) []

let _ = suffix [1; 2; 3; 4] 2