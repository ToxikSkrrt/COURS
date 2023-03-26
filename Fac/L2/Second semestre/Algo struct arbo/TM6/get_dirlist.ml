type direction = L | R;;

let rec get_dirlist n =
  let rec aux n acc =
    if n = 1 || n = 0 then acc
    else if n mod 2 = 0 then aux (n / 2) (L :: acc)
    else aux ((n - 1) / 2) (R :: acc)
  in aux n []
;;

get_dirlist 2;;