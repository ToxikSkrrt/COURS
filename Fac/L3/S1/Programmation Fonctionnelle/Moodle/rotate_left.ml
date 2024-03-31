(*
   Écrire une fonction rotate_left de type  'a list -> 'a list telle que rotate_left [e1; e2; ... ; en] renvoie la liste [e2;...; en; e1].
*)
let rotate_left l =
  let rec aux l acc found =
    match l with
    | [] -> List.rev ((List.hd l)::acc)
    | h::t ->
      if found = false then
        aux t acc true
      else
        aux t (h::acc) found
  in aux l [] false

let rotate_left l =
  match l with
  | [] -> []
  | h::t -> t@[h]