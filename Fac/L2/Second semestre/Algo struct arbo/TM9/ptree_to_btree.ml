type 'a ptree = Pnode of 'a * 'a ptree list;;

type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let rec ptree_to_btree ptree =
  match ptree with
  | Pnode(_, [])-> Empty
  | Pnode(value, h::t) -> failwith "Pas d'idée"
;;