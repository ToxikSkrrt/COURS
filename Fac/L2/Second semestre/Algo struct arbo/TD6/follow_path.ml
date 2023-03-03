type 'a btree = Empty | Node of 'a * 'a btree * 'a btree;;

type direction = L | R;;

let rec follow_path btree list =
  match btree, list with
  | Empty, _ -> "ERROR"
  | Node(v, l, r), [] -> v
  | Node(v, l, r), h::t -> if h = L 
                           then follow_path l t
                           else follow_path r t
;;