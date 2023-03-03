type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec btree_map f btree = 
  match btree with
  | Empty -> Empty
  | Node(v, l, r) -> Node(f v, btree_map f l,  btree_map f r)
;;