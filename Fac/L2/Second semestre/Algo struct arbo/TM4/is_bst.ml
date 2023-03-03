type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec is_bst btree = 
  match btree with
    | Empty -> failwith "not applicable to Empty tree"
    | Node(x, Empty, Empty) -> true
    | Node(x, l, Empty) -> let bstl, minl, maxl = is_bst l in bstl && minl < x
    | Node(x, Empty, r) -> let bstr, minr, maxr = is_bst r in bstr && x > maxr
    | Node(x, l ,r) -> let bstl, minl, maxl = is_bst l in 
                       let bstr, minr, maxr = is_bst r in bstl && bstr && maxl < x && x < minr
                                                      
                                                       
;;