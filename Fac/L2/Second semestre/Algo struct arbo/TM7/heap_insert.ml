type direction = L | R;;

type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

type binheap = Heap of int btree * int;;

let get_dirlist n =
  let rec aux n acc =
  if n = 0 || n = 1
  then acc
  else aux (n/2) ((if n mod 2 = 0 then L else R) :: acc)
  in aux n [] ;;

let binheap_get_size (Heap(btree,size)) = size;;
let binheap_get_btree (Heap(btree,size)) = btree;;

let switch_left btree =
  match btree with
  |Node(k, Node(kl,ll,lr), r) ->
  if k < kl
  then btree
  else Node(kl, Node(k, ll,lr), r)
  | _ -> btree
;;

let switch_right btree =
  match btree with
  |Node(k, l, Node(kr,rl,rr)) ->
  if k < kr
  then btree
  else Node(kr, l, Node(k, rl,rr))
  | _ -> btree
;;

let rec bubble_up btree dirlist =
  match btree, dirlist with
  |Node(k,l,r), [] -> Node(k,l,r)
  |Node(k,l,r), L::tail -> let newl= bubble_up l tail in
  switch_left (Node(k,newl,r))
  |Node(k,l,r), R::tail -> let newr= bubble_up r tail in
  switch_right (Node(k,l,newr))
  |_ -> failwith "should not happen"
;;

let rec insert x btree dirlist =
  match btree, dirlist with
  |Empty, [] -> Node(x, Empty, Empty)
  |Node(v, l, r), head :: tail ->
  if head = L
  then Node(v, insert x l tail, r)
  else Node(v, l, insert x r tail)
  |_ -> invalid_arg "insert err"
;;

let heap_insert k h =
  let new_size= 1 + binheap_get_size h in
  let dirlist = get_dirlist new_size in
  let new_btree = insert k (binheap_get_btree h) dirlist
  in Heap( (bubble_up new_btree dirlist), new_size)
;;