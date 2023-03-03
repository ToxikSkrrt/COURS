type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec btree_height t =
  match t with
  | Empty -> -1
  | Node (v, l, r) -> 1 + max (btree_height l) (btree_height r)
;;

let rec btree_is_perfect t = 
  match t with
    | Empty -> true
    | Node (_, l, r) -> (btree_height l) = (btree_height r) && (btree_is_perfect l) && (btree_is_perfect r)
;;


let rec btree_is_quasi_perfect t = 
  match t with
    | Empty -> true
    | Node(_, l, r) -> if (btree_height l = btree_height r) && (btree_is_perfect l && btree_is_quasi_perfect r)
                       then true
                       else if (btree_height l = btree_height r + 1) && (btree_is_quasi_perfect l && btree_is_perfect r)
                            then true
                            else false
;;