(* TD 2 *)

(* Exercice 2.1 *)
let test x y z =
  z = x + y
;;

(* Exercice 2.2 *)
let valeur_p4 x =
  3 * (x * x * x * x) + 7 * x - 1
;;

(* Exercice 2.3 *)
let polynome3 a b c =
  fun x -> a * (x * x) + b * x + c
;;

(* Exercice 2.4 *)
(*
  fact 5 -> 5 /= 0 -> 5 * fact 4
    -> 4 /= 0 -> 5 * 4 * fact 3
      -> 3 /= 0 -> 5 * 4 * 3 * fact 2
        -> 2 /= 0 -> 5 * 4 * 3 * 2 * fact 1
          -> 0 /= 0 -> 5 * 4 * 3 * 2 * 1 * fact 0
            -> 0 == 0 -> 5 * 4 * 3 * 2 * 1 = 120
*)

(* Exercice 2.5 *)
let rec pgcd n p =
  if p = 0
  then n
  else pgcd p (n mod p)
;;

(* Exercice 2.6 *)
let rec ack m n =
  if m = 0 then n + 1 else if m > 0 && n = 0 then ack (m - 1) n else ack (m - 1) (ack m (n - 1))
;;

(* Exercice 2.7 *)
let rec fib n =
  if n = 0 || n = 1 then 1 else fib (n - 1) + fib (n - 2)
;;

(* Exercice 2.8 *)