type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec bst_pop_max t =
  match t with
  | Empty -> failwith "Empty tree"
  | Node(v, l, Empty) -> l, v
  | Node(v, l, r) -> let bstr, maxr = bst_pop_max r in Node(v, l, bstr), maxr
;;

let rec bst_remove t c = 
  match t with
    | Empty -> t
    | Node(v, l, r) -> if c = v
                       then if l = Empty
                            then r
                            else let l_without_max, max = bst_pop_max l 
                                 in Node(max, l_without_max, r)
                       else if c < v
                            then Node(v, bst_remove l c, r)
                            else Node(v, l, bst_remove r c)
;;

let t1 = Node(4, Node(2, Node(1, Empty, Empty), Node(3, Empty, Empty)), Node(6, Node(5, Empty, Empty), Node(7, Empty, Empty)));;

bst_pop_max t1;;
bst_remove t1 3;;