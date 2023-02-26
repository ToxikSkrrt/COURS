type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let avl_insert t k = 
  Empty
;;