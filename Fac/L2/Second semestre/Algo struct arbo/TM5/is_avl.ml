type 'a btree = Empty | Node of 'a * 'a btree * 'a btree

let is_avl t = 
  true
;;