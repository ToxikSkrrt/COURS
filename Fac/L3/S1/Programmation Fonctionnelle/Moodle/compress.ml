(*
  Écrire une fonction compress de type 'a list -> ('a * int) list,
  telle que compress l renvoie une liste de couples (e,ne) construite à partir de la liste l en remplaçant ne éléments e consécutifs par le couple (e, ne).
  Exemples:
  # compress [1;1;1;1];;
  - : (int * int) list = [(1, 4)]
  # compress [1;1;1;1;2;2;1;1;1;3;3;3];;
  - : (int * int) list = [(1, 4); (2, 2); (1, 3); (3, 3)]   
*)


let compress l =
  let rec aux l acc count =
    match l with
    | [] -> List.rev acc
    | h :: t ->
      match t with
      | [] -> List.rev ((h, count) :: acc)
      | h2 :: t2 ->
        if h = h2 then
          aux t acc (count + 1)
        else
          aux t ((h, count) :: acc) 1
    in aux l [] 1
    

let _ = compress [1;1;1;1]

let _ = compress [1;1;1;1;2;2;1;1;1;3;3;3]

let _ = compress []

let _ = compress [1; 0]