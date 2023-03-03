type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec bst_range_search t min max = 
  match t with
  | Empty -> []
  | Node(v, l, r) -> if v >= min && v <= max 
                     then bst_range_search l min max@ [v] @ bst_range_search r min max
                     else bst_range_search l min max @ bst_range_search r min max
;;

let t1 = Node( 45, Node( 17, Node( 15, Empty, Empty), Node( 35, Empty, Empty)),
                                     Node( 84, Empty, Node (99, Empty, Empty)));;

bst_range_search t1 14 100;;
bst_range_search t1 14 50;;
bst_range_search t1 100 200;;