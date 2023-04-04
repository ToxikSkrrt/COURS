type direction = L | R;;

type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

type binheap = Heap of int btree * int;;

let binheap_get_size (Heap(btree,size)) = size;;
let binheap_get_btree (Heap(btree,size)) = btree;;

let get_dirlist n =
  let rec aux n acc =
  if n = 0 || n = 1
  then acc
  else aux (n/2) ((if n mod 2 = 0 then L else R) :: acc)
  in aux n [] ;;

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