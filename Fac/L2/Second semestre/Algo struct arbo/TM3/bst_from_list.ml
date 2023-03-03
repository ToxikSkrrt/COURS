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

let bst_from_list l = 
  let rec aux l acc =
    match l with
    | [] -> acc
    | h::t -> aux t (bst_insert acc h)
  in aux l Empty
;;

let liste = [1; 2; 3; 4; 5; 6; 7];;
bst_from_list liste;;