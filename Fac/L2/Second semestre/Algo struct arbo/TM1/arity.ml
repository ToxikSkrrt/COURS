type 'a tree = Empty | Node of 'a * 'a tree * 'a tree;;

let arity t =
  match t with
  | Empty -> -1
  | Node (v, Empty, Empty) -> 0
  | Node (v, l, Empty) -> 1
  | Node (v, Empty, r) -> 1
  | Node (v, l, r) -> 2
;;