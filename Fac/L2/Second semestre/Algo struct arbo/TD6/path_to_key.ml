type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

type direction = L | R;;

let rec path_to_key bst x =
  match bst with
  | Empty -> failwith "Not in bst"
  | Node(v, l, r) -> if v = x
                     then []
                     else if x > v
                          then R::path_to_key r x
                          else L::path_to_key l x
;;