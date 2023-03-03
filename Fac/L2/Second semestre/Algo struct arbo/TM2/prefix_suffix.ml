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


let liste = [1; 2; 3; 4; 5];;

prefix liste 3;;
suffix liste 3;;