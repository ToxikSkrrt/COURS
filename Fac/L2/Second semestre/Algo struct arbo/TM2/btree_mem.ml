type 'a tree = Empty | Node of 'a * 'a tree * 'a tree;;

let rec btree_mem x t = 
  false
;;