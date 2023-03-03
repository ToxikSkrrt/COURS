type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec bst_insert t x = 
  match t with
    | Empty -> Node(x, Empty, Empty)
    | Node(v, l, r) -> if v = x
                       then Node (v, l, r)
                       else if v < x
                            then Node (v, l, bst_insert r x)
                            else Node (v, bst_insert l x, r)
;;

let t1 = Empty;;
let t2 = bst_insert t1 1;;
let t3 = bst_insert t2 2;;
let t4 = bst_insert t3 3;;
let t5 = bst_insert t4 4;;
let t6 = bst_insert t5 5;;