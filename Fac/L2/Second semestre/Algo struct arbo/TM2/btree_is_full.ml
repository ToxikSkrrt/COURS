type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec btree_is_full t =
  match t with
  | Empty -> true
  | Node (_, Empty, Empty) -> true
  | Node (_, Empty, _) -> false
  | Node (_, _ , Empty) -> false
  | Node (_, l, r) -> (btree_is_full l) && (btree_is_full r)
;;