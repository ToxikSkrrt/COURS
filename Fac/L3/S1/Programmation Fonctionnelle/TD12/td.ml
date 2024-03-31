(* 12.1 *)

(* 
  def triRapideRec(t, n, d, f):
      if(d<f):
        p=separationPivot(t,n,d,f)
        triRapideRec(t,n,d,p-1)
        triRapideRec(t,n,p+1,f)
     
  def triRapide(t, n):
    triRapideRec(t,n,0,n-1)
*)


(* 12.2 *)

let partition p l =
  let rec aux l l1 l2 =
    match l with
    | [] -> (l1, l2)
    | h :: t ->
      if h < p then
        aux t (h :: l1) l2
      else
        aux t l1 (h :: l2)
  in aux l [] []

let _ = partition 5 [1; 5; 3; 6; 8; 3; 9; 10; 2]

(* 12.3 *)

let rec quick_sort l =
  match l with
  | [] -> []
  | h :: t ->
    let l1, l2 = partition h t in
    quick_sort l1 @ (h :: (quick_sort l2))

let _ = quick_sort [1; 5; 3; 6; 8; 3; 9; 10; 2]

(* 12.4 *)

(* 
    def triFusion (t,n,d,f):
      if (d<f-1):
        m=(d+f)//2
        triFusion(t,n,d,m)
        triFusion(t,n,m,f)
        fusion(t,n,d,f)

  1er Appel :
  triFusion(t,n,0,n)
*)

(* 12.5 *)

let split l =
  let rec aux l l1 l2 count len =
    match l with
    | [] -> (List.rev l1, List.rev l2)
    | h :: t ->
      if count < len / 2 then
        aux t (h :: l1) l2 (count + 1) len
      else
        aux t l1 (h :: l2) (count + 1) len
  in aux l [] [] 0 (List.length l)

let _ = split [1; 5; 3; 6; 8; 3; 9; 10; 2]

(* 12.6 *)

let merge l1 l2 =
  let rec aux l1 l2 acc =
    match l1, l2 with
    | [], [] -> List.rev acc
    | [], (h :: t) -> aux [] t (h :: acc)
    | (h :: t), [] -> aux t [] (h :: acc)
    | (h1 :: t1), (h2 :: t2) ->
      if h1 < h2 then
        aux t1 l2 (h1 :: acc)
      else
        aux l1 t2 (h2 :: acc)
  in aux l1 l2 []

let _ = merge [1;3;5;9] [4;6;7]

(* 12.7 *)

let rec merge_sort l =
  match l with
  | [] -> []
  | [e] -> [e]
  | _ ->
    let l1, l2 = split l in
    merge (merge_sort l1) (merge_sort l2)

let _ = merge_sort [1; 5; 3; 6; 8; 3; 9; 10; 2]