type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec tag_bt t = 
  let rec aux t =
  match t with
  | Empty -> Empty, (-1)
  | Node(v, l, r) -> let le, hl = aux l in
                     let re, hr = aux r in
                     let h = 1 + max hl hr in
                     Node( (v,h), le, re), h
  in let ebtree, h = aux t in ebtree
;;

let t1 = Node(1, Node(2, Empty, Node(3, Empty, Node(4, Empty, Empty))),Empty);;

let res = tag_bt t1;;