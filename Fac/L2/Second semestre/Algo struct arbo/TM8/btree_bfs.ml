type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

let btree_bfs t = 
  let rec aux queue lst =
    match queue with
    |[] -> lst
    |Empty :: tail -> aux tail lst
    |Node(k, l, r) :: tail ->
    aux (tail @ (l :: [r])) (k::lst)
    in List.rev (aux [t] []);;
;;