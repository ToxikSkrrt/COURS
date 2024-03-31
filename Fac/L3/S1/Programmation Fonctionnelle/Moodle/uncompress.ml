(*
  Écrire une fonction uncompress de type ('a * int) list -> 'a list, telle que uncompress couples renvoie la liste
  contenant les éléments e présents dans les couples (e,ne) de la liste couples répétés ne fois. 
  Pour obtenir une fonction linéaire, il est conseillé d'utiliser une fonction auxiliaire add_k_e k e qui ajoute k fois e en tête de la liste. 
  Pour uncompress, on pourra utiliser List.fold_right
  Exemples:
  # uncompress [];;
  - : 'a list = []
  # uncompress [(1, 4); (2, 5); (1, 3); (3, 4)];;
  - : int list = [1; 1; 1; 1; 2; 2; 2; 2; 2; 1; 1; 1; 3; 3; 3; 3]   
*)

let add_k_e k e =
  let rec aux acc count =
    if count = k then
      acc
    else
      aux (e :: acc) (count + 1)
  in aux [] 0

let uncompress couples =
  let rec aux couples acc =
    match couples with
    | [] -> List.rev acc
    | (h, c) :: t ->
      aux t ((add_k_e c h) @ acc)
  in aux couples []


let _ = uncompress []

let _ = uncompress [(1, 4); (2, 5); (1, 3); (3, 4)]