type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec btree_is_quasi_perfect t = 
  true
;;