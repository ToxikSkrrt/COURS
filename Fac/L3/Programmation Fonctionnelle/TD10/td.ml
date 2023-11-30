(* 10.1 *)

(* 1. *)

(*
  op = fun x y -> x + y
  l = [1; 2; 3]   
  a = 0
  b = 0

  left_fold op a l :
    sum1 = op a 1 = 1
    sum2 = op sum1 2 = 3
    sum3 = op sum2 3 = 6
    total = 6

  right_fold op l b :
    sum1 = op 3 b = 3
    sum2 = op 2 sum1 = 5
    sum3 = op 1 sum2 = 6
    total = 6
*)

(* 2. *)

let right_fold op l b =
  let rec aux l acc =
    match l with
    | [] -> acc
    | h :: t -> aux t (op h acc)
  in aux (List.rev l) b

let _ = right_fold (fun x y -> x + y) [1; 2; 3] 0

(* 3. *)

let left_fold op a l =
  let rec aux l acc =
    match l with
    | [] -> acc
    | h :: t -> aux t (op h acc)
  in aux l a

let _ = left_fold (fun x y -> x + y) 0 [1; 2; 3]

(* 10.2 *)

(* 1. *)

let length l = List.fold_left (fun x _ -> x + 1) 0 l

let _ = length [1; 2; 3]

(* 2. *)

let reverse l = List.fold_right (fun x y -> x :: y) (List.rev l) []

let _ = reverse [1; 2; 3]

(* 3. *)

let maximum l = List.fold_left (fun x y -> if x > y then x else y) 0 l

let _ = maximum [1; 2; 4; 3]

(* 4. *)

let filter p l = List.fold_right (fun x y -> if p x then x :: y else y) l []

let _ = filter (fun x -> x mod 2 = 0) [1; 2; 3; 4; 5]

(* 5. *)  (* TODO *)

let remove_duplicates l = []

let _ = remove_duplicates [1; 2; 3; 1; 4; 2; 3; 3]

(* 6. *)

let append l1 l2 = (List.fold_right (fun x y -> x :: y) l1 []) @ (List.fold_right (fun x y -> x :: y) l2 [])

let _ = append [1; 2; 3] [4; 5; 6]

(* 7. *)

let map f l = List.fold_right (fun x y -> (f x) :: y) l []

let _ = map (fun x -> x * x) [1; 2; 3; 4]
