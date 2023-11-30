(*
   Écrire une fonction iota_r de type  int -> int list telle que iota_r n renvoie la liste [n; n-1; ...; 1].
*)
let iota_r (n : int) =
  let rec aux n acc =
    if n = 0 then
        List.rev acc
    else
        aux (n - 1) (n::acc)
  in aux n []
