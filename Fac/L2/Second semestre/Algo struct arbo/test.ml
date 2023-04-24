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

let rec insert_sorted x l key_fun =
  match l with
  | [] -> [x]
  | h::t -> if key_fun x <= key_fun h
            then x::l
            else h::insert_sorted x t key_fun 
;;

let rec insertion_sort l key_fun =
  let rec aux l key_fun acc =
    match l with
      | [] -> acc
      | h::t -> aux t key_fun (insert_sorted h acc key_fun)
    in aux l key_fun []
;;

let rec insertion_sort l key_fun =
  match l with
  | [] -> []
  | h::t -> insert_sorted h (insertion_sort t key_fun) key_fun
;;

type htree = Leaf of char | Node of htree * htree;;

let rec charlist_of_string s =
  let rec trav l i =
    if i = l then [] else s.[i]::trav l (i + 1)
  in trav (String.length s) 0
;;

let rec string_of_charlist l =
  match l with
  | [] -> ""
  | h::t -> String.make 1 h ^ string_of_charlist t
;;

let rec add_char c occlist =
  match occlist with
  | [] -> [(c, 1)]
  | (cchar, cocc)::t -> if c < cchar
                        then (c, 1)::occlist
                        else 
                          if c = cchar
                          then (c, cocc + 1)::t
                          else (cchar, cocc)::add_char c t
;;

let rec charlist_to_treelist charlist =
  match charlist with
  | [] -> []
  | (c, occ)::t -> (Leaf(c), occ)::charlist_to_treelist t
;;

let rec treelist_to_hufftree treelist =
  match treelist with
  | [] -> failwith "error"
  | (t, _)::[] -> t
  | (t1, occ1)::(t2, occ2)::tail -> treelist_to_hufftree (insert_sorted (Node(t1, t2), occ1 + occ2) tail snd)
;;

let codelist hufftree =
  let rec aux hufftree path acc =
    match hufftree with
    | Leaf(c) -> (c, List.rev path)::acc
    | Node(left, right) -> let lacc = aux left (0::path) acc 
  in aux right (1::path) lacc in List.rev (aux hufftree [] [])
;;

let rec encode_charlist charlist codelist =
  match charlist with
  | [] -> []
  | c::t -> (encode_char c codelist) @ encode_charlist t codelist
;;

let encode charlist =
  let occlist = charlist_to_occlist charlist in
  let treelist = charlist_to_treelist in
  let hufftree = treelist_to_hufftree in
  let code = encode_charlist charlist code
;;

let rec nextchar_and_tail hufftree l =
  true
;;