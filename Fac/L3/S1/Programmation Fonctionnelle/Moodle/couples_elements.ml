(* 
  Écrire une fonction couple_elements de type ('a * 'a) list -> 'a list,
  telle que couples_elements couples renvoie la liste des éléments présents dans les couples de la liste couples dans n'importe quel ordre.
  Exemple :couples_elements [(1,2); (5,3); (2,3); (5,1)] doit renvoyer une liste contenant
  les mêmes éléments que ceux contenus dans la liste [1; 2; 3; 5]. 
*)

let couples_elements l =
  let rec aux l acc =
    match l with
    | [] -> acc
    | (h1, h2) :: t ->
      if not (List.mem h1 acc) && not (List.mem h2 acc) && h1 != h2 then
        aux t (h1 :: h2 :: acc)
      else
        if not (List.mem h1 acc) then
          aux t (h1 :: acc)
        else
          if not (List.mem h2 acc) then
            aux t (h2 :: acc)
          else
            aux t acc
    in aux l []


let _ = couples_elements [(1,2); (5,3); (2,3); (5,1)]

let _ = couples_elements [(5, 5)]