let rec insert l x = 
  match l with
  | [] -> [x]
  | h::t -> if x <= h
            then [x] @ [h] @ t
            else [h] @ insert t x
;;

let rec insertion_sort l = 
  match l with
  | [] -> []
  | h::t -> insert (insertion_sort t) h
;;


let liste = [1; 2; 3; 5; 6];;
insert liste 4;;

let liste2 = [2; 4; 3; 5; 1];;
insertion_sort liste2;;