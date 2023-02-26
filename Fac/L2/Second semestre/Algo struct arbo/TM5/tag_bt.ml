type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec get_height t = 
  match t with
  | Empty -> -1
  | Node((v, h), l, r) -> h
;;

let rec tag_bt t = 
  match t with
  | Empty -> Empty
  | Node(v, l, r) -> let c = 0 in Node((v, c + 1), tag_bt l, tag_bt r)
;;

let t1 = Node(1, Node(2, Empty, Node(3, Empty, Node(4, Empty, Empty))),Empty);;

let res = tag_bt t1;;