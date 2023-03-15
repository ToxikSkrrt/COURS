type 'a btree = Empty | Node of 'a * 'a btree * 'a btree

let get_height ebtree =
  match ebtree with
  | Empty -> (-1)
  | (Node((_,h), _, _)) -> h
;;

let get_balance t =
  match t with
  | Empty -> 0
  | Node((v, h), l, r) -> get_height l - get_height r
;;

let is_avl t = 
  let rec aux t =
    let b = get_balance t in
    let bok = (-2) < b && b < 2 in
    match t with
    | Empty -> failwith "aux on Empty"
    | Node((e,_), Empty, Empty) ->
    bok && true, e
     , e
    (* is_avl, min, max *)
    | Node((e,_), Empty, r) ->
    let bst_r, min_r, max_r =
    aux r in bok && bst_r && e < min_r, e, max_r
    | Node((e,_), l, Empty) ->
    let bst_l, min_l, max_l =
    aux l in bok && bst_l && max_l < e, min_l, e
    | Node((e,_), l, r) ->
      let bst_l, min_l, max_l = aux l
      and bst_r, min_r, max_r = aux r in
      bok && bst_l && bst_r && max_l < e && e < min_r,
      min_l,
      max_r
  in t = Empty || let bst, _, _ = aux t in bst;
;;