(* Nom: Moreau *)
(* Prénom: Thomas-Alexandre *)
(* Groupe: A2 *)

(* 1- union *)

let union l1 l2 =
  let rec aux l1 l2 acc =
    match l1, l2 with
    | [], [] -> acc
    | [], h :: t -> if List.mem h acc then aux [] t acc else aux [] t (h :: acc)
    | h :: t, [] -> if List.mem h acc then aux t [] acc else aux t [] (h :: acc)
    | h1 :: t1, h2 :: t2 ->
      if h1 = h2 && not (List.mem h1 acc) then
        aux t1 t2 (h1 :: acc)
      else
        if not (List.mem h1 acc) then
          aux t1 l2 (h1 :: acc)
        else
          if not (List.mem h2 acc) then
            aux l1 t2 (h2 :: acc)
          else
            aux t1 t2 acc
  in aux l1 l2 []

(* 2- intersection *)

let intersection l1 l2 =
  let rec aux l1 l2 acc =
    match l1, l2 with
    | [], [] -> acc
    | [], h :: t -> if List.mem h l1 && not (List.mem h acc) then aux t [] (h :: acc) else aux t [] acc
    | h :: t, [] -> if List.mem h l2 && not (List.mem h acc) then aux t [] (h :: acc) else aux t [] acc
    | h1 :: t1, h2 :: t2 ->
      if (List.mem h1 l2) && not (List.mem h1 acc) then
        aux t1 l2 (h1 :: acc)
      else
        if (List.mem h2 l1) && not (List.mem h2 acc) then
          aux l1 t2 (h2 :: acc)
        else
          aux t1 t2 acc
  in aux l1 l2 []

(* 3- make_ratio *)

type ratio = Int of int | Ratio of int * int

let rec pgcd a b =
  if b = 0 then if a = 0 then failwith "pgcd(0,0)" else a
    else pgcd b (a mod b)

let make_ratio n d =
  let p = pgcd n d in
  let n1 = n / p in
  let d1 = d / p in
  if d1 = 1 then Int n1 else Ratio (n1, d1)

(* 4- numerateur / denominateur *)

let numerateur r =
  match r with
  | Int v -> v
  | Ratio (n, _) -> n

let denominateur r =
  match r with
  | Int v -> 1
  | Ratio (_, d) -> d

(* 5- ratio_sup *)

let ratio_sup r1 r2 =
  if denominateur r1 = denominateur r2 then
    numerateur r1 >= numerateur r2
  else
    let n1 = numerateur r1 * denominateur r2 in
    let n2 = numerateur r2 * denominateur r1 in
    n1 >= n2

(* 6- ratio_prod *)

let ratio_prod r1 r2 =
  let n = numerateur r1 * numerateur r2 in
  let d = denominateur r1 * denominateur r2 in
  make_ratio n d

(* 7- opérations implémentables avec le type list *)

type rset_fun = ratio -> bool

type rset_list = ratio list

(* rset_empty O: *)
(* rset_member O: *)
(* rset_complement 0: *)
(* rset_make_interval O: *)
(* rset_make_singleton O: *)
(* rset_adjoin O: *)
(* rset_union O: *)
(* rset_intersection O: *)
(* rset_remove_if O: *)

(* 8- opérations implémentables avec le type list; 9 au maximum *)

(* let rset_empty = fun (r : rset_list) ->
  let rec aux r acc =
    match r with
    | [] -> acc
    | h :: t -> aux t false
  in aux r false *)

let rset_empty : rset_list = []

let rset_member r (l : rset_list) = List.mem r l

let rset_complement r =
  fun l ->
    let rec aux l acc =
      match l with
      | [] -> acc
      | h :: t ->
        if h = r then
          aux t acc
        else
          aux t (h :: acc)
    in aux l []

let make_interval r1 r2 =
  fun l ->
    let rec aux l acc =
      match l with
      | [] -> acc
      | h :: t ->
        if ratio_sup h r1 && ratio_sup r2 h then
          aux t (h :: acc)
        else
          aux t acc
    in aux l []

let rset_make_singleton r : rset_list = [r]

(* let rset_adjoin rat l =
  fun r ->
    let rec aux l acc =
      match l with
      |  *)


let rset_intersection l1 l2 : rset_list = intersection l1 l2

let rset_union l1 l2 : rset_list = union l1 l2

let rset_remove_if p l : rset_list =
  let rec aux l acc =
    match l with
    | [] -> acc
    | h :: t ->
      if not (p h) then
        aux t (h :: acc)
      else
        aux t acc
  in aux l []

(* 9- rset_of_couples *)

let rset_of_couples l =
  let rec aux l acc =
    match l with
    | [] -> acc
    | (n, d) :: t ->
      let r = make_ratio n d in
      if not (List.mem r acc) then
        aux t ((make_ratio n d) :: acc)
      else
        aux t acc
  in aux l []

(* 10- rset_product *)

let rset_product l =
  let rec aux l acc =
    match l with
    | [] -> acc
    | r :: t -> aux t (ratio_prod r acc)
  in aux l (Int 1)
