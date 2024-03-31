(* Exercice 1: à tester vous même *)

(* Exercice 2 *)

(*  8. fun x y -> float_of_int x +. y *)
(*  9. fun x -> fst x = snd x *)
(* 10. fun x p -> if p x then 0 else 1 *)

(* Exercice 3 *)
(*  11. PGCD(a, 0) = a et que PGCD(a, b) = PGCD(b, a mod b) *)
let rec pgcd a b =
  if b = 0 then if a = 0 then failwith "pgcd(0,0)" else a
    else pgcd b (a mod b)

(* Exercice 4 *)
(* 12. *)
let make_ratio n d =
  let p = pgcd n d in Ratio(n / p, d / p)

(* 13. *)
let numerateur r = let Ratio(n,_) = r in n
let denominateur r = let Ratio(_,d) = r in d

(* 14. *)
let float_of_ratio r =
  float_of_int (numerateur n) /. float_of_int (denominateur r)

(* 15. *)
let ratio_infeg r1 r2 = float_of_ratio r1 <= float_of_ratio r2

(* 16. *)
let ratio_sum r1 r2 =
  let a1 = numerateur r1 and b1 = denominateur r1 and
      a2 = numerateur r2 and b2 = denominateur r2 in
  make_ratio (a1 * b2 + b1 * a2) (b1 * b2)

(* Exercice 5 *)
(* 17. *)
let rset_full : rset = fun r -> true

(* 18. *)
let rec rset_make_interval r1 r2 : rset = (* [r1, r2] *)
  fun r -> ratio_infeg r1 r && ratio_infeg r r2

(* 19. *)
let rset_make_singleton r = rset_make_interval r r

(* 20. *) 
let rset_complement rset = fun r -> not (rset_member r rset)
(* let rset_full = rset_complement rset_empty *)

(* 21. *)
let rset_intersection rset1 rset2 : rset = fun r -> rset_member r rset1 && rset_member r rset2

(* 22. *)
let rset_remove_if p rset : rset =
  fun r -> not (p r) && rset_member r rset

(* 23. *)
(* rset_remove_if (fun ratio -> denominateur ratio = 1) rset_full *)

(* 24. *)
(* recursion pour trouver le plus grand entier positif strictement plus petit que n *)
let rset_find_smaller_int rset n =
  let rec aux i =
    if i = -1 then n
  else
    let ri = make_ratio i 1 in
    if rset_member ri rset then i
    else  aux (pred i)
  in aux (pred n)
