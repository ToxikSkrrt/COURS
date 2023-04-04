type direction = L | R;;

type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

type binheap = Heap of int btree * int

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

let rec bubble_down btree =
  match btree with
  |Empty -> btree
  |Node(_,Empty,Empty) -> btree
  |Node(k, Node(kl, ll, lr), Empty) ->
  if k <= kl
  then btree
  else Node(kl, bubble_down (Node(k,ll,lr)), Empty)
  |Node(k, Empty, _ ) -> invalid_arg "bubble_down err: not qp"
  |Node(k, Node(kl,ll, lr), Node(kr, rl, rr)) ->
  if k <= (min kl kr)
  then btree
  else
  if kl < kr
  then Node(kl, bubble_down (Node(k,ll,lr)),Node(kr,rl,rr))
  else Node(kr, Node(kl,ll,lr), bubble_down (Node(k,rl,rr)))
;;

let rec delete btree dirlist =
  match btree, dirlist with
  |Empty, _ -> invalid_arg "delete err: on Empty"
  |Node(k,Empty,Empty),[] -> Empty, k
  |Node(k,Empty,Empty),_ -> invalid_arg "delete err: dirlist"
  |Node(k, l, r), [] -> invalid_arg "delete err: dirlist"
  |Node(k,l,r), head::tail ->
  if head = L
  then let ll, kl = delete l tail in Node(k, ll, r), kl
  else let rr, kr = delete r tail in Node(k, l, rr), kr
;;

let heap_delete h =
  let size = binheap_get_size h in
  let btree = binheap_get_btree h in
  let dirlist = get_dirlist size in
  let d_btree,d_k = delete btree dirlist in
  match d_btree with
  |Empty -> Heap(Empty,0)
  |Node(k, l, r) ->
  Heap ( bubble_down (Node(d_k, l, r)), size - 1)
;;

let get_min binheap =
  match binheap with
  |Heap(Empty,_) ->
  invalid_arg " err binheap_get_min on empty heap"
  |Heap(Node(k,_,_),size) -> k
;;

let list_to_heap list =
  let rec aux list acc =
  match list with
  |[] -> acc
  |head::tail -> aux tail (heap_insert head acc)
  in aux list (Heap(Empty,0))
;;

let rec heap_to_list binheap =
  match binheap with
  |Heap(Empty,0) -> []
  |Heap(btree,size) ->
  (get_min binheap) :: ( heap_to_list (heap_delete binheap))
  ;;

let rec heap_sort l =
  heap_to_list (list_to_heap l)
;;