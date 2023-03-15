type 'a tree = Empty | Node of 'a * 'a tree * 'a tree;;

let rec btree_size t =
  match t with
  | Empty -> 0
  | Node (v, l, r) -> 1 + btree_size l + btree_size r
;;

let rec btree_height t =
  match t with
  | Empty -> -1
  | Node (v, l, r) -> 1 + max (btree_height l) (btree_height r)
;;