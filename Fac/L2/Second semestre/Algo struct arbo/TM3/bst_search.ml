type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec bst_search t x = 
  match t with
    | Empty -> false
    | Node (v, l, r) -> if v = x
                             then true
                             else if v < x
                                  then bst_search r x
                                  else bst_search l x
;;