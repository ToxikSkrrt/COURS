# TM 1

## Exercice 1.1

1. 12 + 30 -> int = 42
2. 12.0 + 30 -> ERROR
3. 12.0 + 30.0 -> float = 42.0
4. int_of_float 12.5 + 30 -> int = 42
5. float_of_int 12 +. 30.0 -> float = 42.

## Exercice 1.2

1. 3 = 4 || 4 = 4 -> bool = true
2. 3 = 4 && 4 = 4 -> bool = false
3. not (3 = 4) && 4 = 4 -> bool = true
4. not (3 = 4 || 4 = 4) -> bool = false

## Exercice 1.3

1. 12 + 30 = 10 + 32 -> bool = true
2. 12.0 + 30.0 = 10 + 32 -> ERROR
3. 12.0 +. 30.0 = float_of_int (10 + 32) -> bool = true
4. 12.0 +. 30. = 42. && 3 + 4 = 4 + 4 -> bool = false
5. 12.0 +. 30. = 42. && 3 + 4 != 4 + 4 -> bool = true
6. 12.0 +. 30. = 42. || 3 + 4 = 4 + 4 -> bool = true
7. 12.0 +. 30. = 42. && not (3 + 4 = 4 + 4) -> bool = true
8. int_of_string "12" + int_of_string "30" -> int = 42
9. int_of_string "12" + int_of_string "30" = 42 -> bool = true

## Exercice 1.4

1. let x = 12.0 in x +. 30.0 -> float = 42.
2. let x = 12.0 in if x +. 30.0 = 42.0 then 42 else 0 -> int = 42
3. let x = 12.0 in if x +. 30.0 = 42.0 then "42" else 0 -> ERROR

## Exercice 1.5

1. let f = 2.0 in let square_f = sqrt f in let log_f = log f in (square_f +. log_f) *. (square_f -. 2. *. log_f);;
2. let f = 2.0 in let square_f = sqrt f in let log_square_f = log square_f in (square_f +. log_square_f) *. (square_f -. 2. *. log_square_f);;

## Exercice 1.7

(fun x -> x * 2) 2;;

## Exercice 1.8

1. let y = let x = 12.0 in x +. 30.0 -> val y : float = 42
2. let y = let x = 12.0 in if x +. 30.0 then 42 else 0 -> ERROR
3. let x = 3 in let y = 4 in x + y -> int = 7
4. let z = let x = 3 in let y = 4 in x + y -> val z : int = 7
5. let x = 3 in let y = 4 -> ERROR

## Exercice 1.9

let exo9 i = if i > 0 then "positive" else if i < 0 then "negative" else "nul";;

## Exercice 1.10

1. fun x -> x -> 'a -> 'a = <fun>
2. (fun x -> x) 5 -> int = 5
3. fun x -> x + 1 -> int -> int = <fun>
4. let f = fun x y -> x - y in f (f 1 1) 1 -> int = -1
5. let compose = fun f g -> fun x -> f (g x) -> val compose : ('a -> 'b) -> ('c -> 'a) -> 'c -> 'b = <fun>
6. let mystere =
let square = fun x -> x * x in
let compose = fun f g -> fun x -> f (g x) in
compose square square -> val mystere : int -> int = <fun>

## Exercice 1.11

let discriminant a b c = b * b - 4 * a * c;;
let nbSols a b c = if a = 0 && b = 0 && c = 0
                   then -1
                   else let d = discriminant a b c in if d < 0
                                                  then 0
                                                  else if d > 1
                                                       then 2
                                                       else 1
;;