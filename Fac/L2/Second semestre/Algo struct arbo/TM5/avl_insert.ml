type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let get_height ebtree =
  match ebtree with
  | Empty -> (-1)
  | (Node((_,h), _, _)) -> h
;;

let tag_node v l r =
  let hl, hr = get_height l, get_height r in
  Node((v, 1 + max hl hr), l, r)
;;

let r_ro ebtree =
  match ebtree with
  | Node((kc,_), Node((ka, _), t1, t2), t3) ->
  let c_new = tag_node kc t2 t3 in
  tag_node ka t1 c_new
  | _ -> failwith ("rotate right impossible") 
;;

let l_ro t =
  match t with
  | Node((ka,_),t1,Node((kc,_),t2,t3)) ->
  let a_new = tag_node ka t1 t2 in
  tag_node kc a_new t3
  | _ -> failwith ("rotate left impossible") 
;;

let lr_ro t =
  match t with
  | Node((kc,_), Node((ka,_), t1, Node((kb,_), t2, t3)), t4) ->
  let a_new= tag_node ka t1 t2 in
  let c_new= tag_node kc t3 t4 in
  tag_node kb a_new c_new
  | _ -> failwith ("rotate_left_right impossible") 
;;

let rl_ro t =
  match t with
  | Node((ka,_), t1, Node((kc,_), Node((kb,_), t2, t3), t4)) ->
  let a_new= tag_node ka t1 t2 in
  let c_new= tag_node kc t3 t4 in
  tag_node kb a_new c_new
  | _ -> failwith ("rotate_right_left impossible") 
;;

let get_balance t =
  match t with
  | Empty -> 0
  | Node((v, h), l, r) -> get_height l - get_height r
;;

let avl_repair_balance avl =
  match avl with
  | Empty -> Empty
  | Node(_, l, r) ->
  let coef = get_balance avl in
  let coef_l = get_balance l in
  let coef_r = get_balance r in
  match coef, coef_l, coef_r with
  | 0, _, _ | 1, _, _ | -1, _, _ -> avl
  | 2, coef_l, _ -> if coef_l = 0 || coef_l = 1
  then r_ro avl
  else lr_ro avl
  | -2, _, coef_r -> if coef_r = 0 || coef_r = -1
  then l_ro avl
  else rl_ro avl
  | _ -> failwith ("avl_fix impossible")
;;

let rec avl_insert t k = 
    match t with
  | Empty -> tag_node k Empty Empty
  | Node((x,_),l,r) when k = x -> t
  | Node((x,_),l,r) ->
  if k < x
  then avl_repair_balance (tag_node x (avl_insert l k) r)
  else avl_repair_balance (tag_node x l (avl_insert r k) )
;;

