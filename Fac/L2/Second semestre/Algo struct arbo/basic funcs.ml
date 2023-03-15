type 'a btree =
  | Empty
  | Node of 'a * 'a btree * 'a btree

let rec btree_height t =
  match t with
  | Empty -> -1
  | Node (v, l, r) -> 1 + max (btree_height l) (btree_height r)
;;

let rec btree_size t =
  match t with
  | Empty -> 0
  | Node (v, l, r) -> 1 + btree_size l + btree_size r

let rec btree_internal_nodes t = 
  match t with
  | Empty -> 0
  | Node (v, l, r) -> if l == Empty && r == Empty
                      then 0 
                      else 1 + btree_internal_nodes l + btree_internal_nodes r

let rec btree_leaves t = 
  match t with
  | Empty -> 0
  | Node (v, l, r) -> if l == Empty && r == Empty 
                      then 1 
                      else btree_leaves l + btree_leaves r

(* EXEMPLES *)

let t1 = Node (10, Node (20, Empty, Empty), Empty);;

btree_height t1;;
btree_size t1;;
btree_internal_nodes t1;;
btree_leaves t1;;