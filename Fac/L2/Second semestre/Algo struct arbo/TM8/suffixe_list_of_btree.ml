type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec suffixe_list_of_btree t =
  match t with
  |Empty -> []
  |Node(k, l, r) ->
  (suffixe_list_of_btree l) @
  (suffixe_list_of_btree r) @ [k]
;;