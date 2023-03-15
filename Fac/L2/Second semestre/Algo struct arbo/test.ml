type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec size a =
  match a with
  | Empty -> 0
  | Node (e, fg, fd) -> 1 + size fg + size fd
;;

let n1 = Node (10, Empty, Empty);;

let n3 = Node (1, Node (2, Node (3, Empty, Empty), Empty), Empty);;

size n1;;

size n3;;

let rec fib n =
  if n = 0 || n = 1
  then 1
  else fib (n - 1) + fib (n - 2)
;;

fib 4;;

let rec bst_max t =
  match t with
  | Empty -> failwith "Empty tree"
  | Node (v, l, r) -> if r = Empty
                      then v
                      else bst_max r
;;

let rec bst_max_2 t =
  match t with
  | Empty -> failwith "Empty tree"
  | Node (v, _, Empty) -> v
  | Node (_, _, r) -> bst_max_2 r
;;

let t = Node( 45,
Node( 17,
Node( 15, Empty, Empty),
Node( 35, Empty, Empty)),
Node( 84, Empty, Node (99, Empty, Empty)));;

bst_max t;;
bst_max_2 t;;