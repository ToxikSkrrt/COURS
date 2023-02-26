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