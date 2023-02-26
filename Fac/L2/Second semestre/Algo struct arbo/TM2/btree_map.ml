type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec btree_map f btree = 
  Empty
;;