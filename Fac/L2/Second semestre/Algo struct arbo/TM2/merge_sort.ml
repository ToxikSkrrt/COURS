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

let rec prefix l n = 
  match l with
  | [] -> []
  | h::t -> if n <= 0
            then []
            else [h] @ (prefix t (n - 1))
;;

let rec suffix l n = 
  match l with
  | [] -> []
  | h::t -> let len = List.length l - n + 1 in 
            if n <= 0
            then []
            else if len - 1 <= 0
                 then [h] @ (suffix t (n - 1))
                 else suffix t n
;;

let rec merge l1 l2 = 
  insertion_sort (l1 @ l2)
;;

let rec merge_sort l = 
  let l1 = prefix l (List.length l / 2) in let l2 = suffix l (List.length l / 2) in merge l1 l2
;;

let l1 = [1; 3; 5; 7; 9];;
let l2 = [2; 4; 6; 8; 10];;

let l3 = [4; 3; 6; 1; 10; 7];;

merge l1 l2;;

merge_sort l3;;