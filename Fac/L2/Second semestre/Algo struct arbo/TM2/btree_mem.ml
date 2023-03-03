type 'a tree = Empty | Node of 'a * 'a tree * 'a tree;;

let rec btree_mem x t = 
  match t with
    | Empty -> false
    | Node (v, g, d) -> if v = x 
                        then true 
                        else (btree_mem x g) || (btree_mem x d)
;;