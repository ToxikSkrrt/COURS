(* FONCTIONS FOLD => TD 10 *)

let addition_liste l = List.fold_left (fun x y -> x + y) 0 l

let reverse l = List.fold_right (fun x y -> x :: y) (List.rev l) []

let maximum l = List.fold_left (fun x y -> if x > y then x else y) 0 l

let filter p l = List.fold_right (fun x y -> if p x then x :: y else y) l []