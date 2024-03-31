(* 
   Écrire une fonction seq_max_len de type 'a list -> 'a -> int, telle que seq_max_len l e renvoie la longueur de la plus grande séquence d'éléments e consécutifs  présents dans la liste l.
Exemples:
# seq_max_len [1; 0; 0; 1; 1; 1; 0; 0; 1] 0;;
- : int = 2
# seq_max_len [1; 0; 0; 1; 1; 1; 0; 0; 1] 1;;
- : int = 3 .
*)

let seq_max_len l e =
  let rec aux l acc max =
    match l with
    | [] -> max + 1
    | h :: t ->
      if h = e then
        if acc > max then
          aux t (acc + 1) acc
        else
          aux t (acc + 1) max
      else
        aux t 0 max
  in aux l 0 (-1)


let _ = seq_max_len [1; 0; 0; 1; 1; 1; 0; 0; 1] 0

let _ = seq_max_len [1; 0; 0; 1; 1; 1; 0; 0; 1] 1

let _ = seq_max_len [0; 0; 0; 0; 0; 0; 0; 0; 0] 1