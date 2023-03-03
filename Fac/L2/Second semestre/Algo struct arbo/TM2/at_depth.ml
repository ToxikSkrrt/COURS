type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec at_depth t d = 
  match t with
  | Empty -> []
  | Node(v, l, r) -> if d = 0
                     then [v]
                     else at_depth l (d - 1) @ at_depth r (d - 1)
;;

let t1 = Node( 45, Node( 17, Node( 15, Empty, Empty), Node( 35, Empty, Empty)),
                                     Node( 84, Empty, Node (99, Empty, Empty)));;

at_depth t1 3;;