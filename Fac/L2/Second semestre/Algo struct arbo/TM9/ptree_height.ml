type 'a ptree = Pnode of 'a * 'a ptree list;;

let rec ptree_height ptree =
  match ptree with
  Pnode(_,[])-> 0
  |Pnode(k,fst::rest) ->
  max (1+(ptree_height fst))
  (ptree_height (Pnode(k,rest)));;