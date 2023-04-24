type 'a ptree = Pnode of 'a * 'a ptree list;;

let rec ptree_size ptree =
  match ptree with
  Pnode(_,[]) -> 1
  |Pnode(k, fst::rest_of_sons) ->
  (ptree_size fst) + (ptree_size (Pnode(k,rest_of_sons)));;