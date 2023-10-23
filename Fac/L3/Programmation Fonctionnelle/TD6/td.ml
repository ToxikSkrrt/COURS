type complex = { real : float; imag : float; }

let make_complex (real : float) (imag : float) : complex = {real = real; imag = imag}

(* accesseurs *)
let realpart (c : complex) : float = c.real
let imagpart (c : complex) : float = c.imag

let c_origin : complex = make_complex 0.0 0.0
let c_i : complex = make_complex 0. 1.

let p_12 : complex = make_complex 1. 2.
let p_34 : complex = make_complex 3. 4.

let c_abs (c : complex) : float = let x, y = realpart c, imagpart c in
	sqrt (x *. x +. y *. y)

let c_sum (c1 : complex) (c2 : complex) : complex = make_complex (realpart c1 +. realpart c2) (imagpart c1 +. imagpart c2)

let c_dif (c1 : complex) (c2 : complex) : complex = make_complex (realpart c1 -. realpart c2) (imagpart c1 -. imagpart c2)

let c_opp (c : complex) : complex = c_dif c_origin c

let c_mul (c1 : complex) (c2 : complex) : complex = let x1, y1 = realpart c1, imagpart c1
	and x2, y2 = realpart c2, imagpart c2 in
	make_complex (x1 *. x2 -. y1 *. y2) (x1 *. y2 +. x2 *. y1)

let c_sca (lambda : float) (c : complex) : complex = make_complex (lambda *. realpart c) (lambda *. imagpart c)

let c_exp (c : complex) : complex = let x, y = realpart c, imagpart c in
  c_sca (exp x) (make_complex (cos y) (sin y))

let translate (c : complex) (vector : complex) : complex =
  c_sum c vector

let rotate0 (c : complex) (angle : float) : complex =
  c_mul (c_exp (c_sca angle c_i)) c

let rotate (c : complex) (angle : float) (center : complex) : complex =
  translate (rotate0 (translate c (c_opp center)) angle) center

type date = {day : int; month : int; year : int}

let make_date (day : int) (month : int) (year : int) : date = {day = day; month = month; year = year}

let get_day (d : date) : int = d.day

let get_month (d : date) : int = d.month

let get_year (d : date) : int = d.year

let today : date = make_date 12 10 2023

let date_infeg (date1 : date) (date2 : date) : bool =
  let d1, m1, y1 = get_day date1, get_month date1, get_year date1 in 
  let d2, m2, y2 = get_day date2, get_month date2, get_year date2 in
  if y1 < y2 then
    true
  else if y1 = y2 then
    if m1 < m2 then
      true
    else if m1 = m2 then
      if d1 <= d2 then
        true
      else
        false
    else
      false
  else
    false

type 'a mylist = Nil | C of 'a * 'a mylist

let rec mylist_length (l : 'a mylist) : int =
  match l with
  | Nil -> 0
  | C (h, t) -> 1 + mylist_length t
    
let rec interval_list (n : int) (p : int) : int mylist =
  if n > p then
    Nil
  else
    C(n, interval_list (n + 1) p)

let rec map (f : 'a -> 'b) (l : 'a mylist) : 'b mylist =
  match l with
  | Nil -> Nil
  | C (h, t) -> C (f h, map f t)

let rec filter (pred : 'a -> bool) (l : 'a mylist) : 'a mylist =
  match l with
  | Nil -> Nil
  | C (h, t) ->
    if pred h then
      C (h, filter pred t)
    else
      filter pred t

type peano = Zero | Succ of peano

let rec peano_add (p1 : peano) (p2 : peano) : peano =
  match p2 with
  | Zero -> p1
  | Succ (pred) -> Succ (peano_add p1 pred)

let rec peano_mult (p1 : peano) (p2 : peano) : peano =
  match p2 with
  | Zero -> Zero
  | Succ (pred) -> peano_add (peano_mult p1 pred) p1

let rec peano_of_int (n : int) : peano =
  if n = 0 then
    Zero
  else
    Succ (peano_of_int (n - 1))

let rec int_of_peano (p : peano) : int =
  match p with
  | Zero -> 0
  | Succ (pred) -> 1 + int_of_peano pred

let fact_ter (n : int) : int =
  let rec aux (n : int) (acc : int) =
    if n = 0 then
      acc
    else
      aux (n - 1) (acc * n)
  in aux n 1

let sum_ter (n : int) (p : int) : int =
  let rec aux (n : int) (p : int) (acc : int) =
    if n > p then
      acc
    else
      aux (n + 1) p acc + n
  in aux n p 0

(* ------------------------------------------------------------ *)

let test_mycomplex () =
  begin
(* realpart *)
  assert (let c = make_complex 3. 4. in realpart c = 3.0);

(* imagpart *)
  assert (let c = make_complex 3. 4. in imagpart c = 4.0);

(* c_abs *)
assert (let i = make_complex 0. 1. in c_abs i = 1.);

  assert (let c = make_complex 3. 4. in c_abs c = 5.);
(* c_sum *)
assert (let o = make_complex 0. 0. and i = make_complex 0. 1. in c_sum o i = i);
(* c_sca *)
assert (let c = make_complex 3. 4. in c_sum c c = c_sca 2. c);
assert (let c = make_complex 3. 4. in c_sca 2. c = make_complex 6. 8.);
(* c_dif *)
assert (let c = make_complex 3. 4. and o = make_complex 0. 0. in c_dif c c = o);

(* c_mul *)
assert (let c = make_complex 3. 4. in c_mul c c = make_complex (-7.) 24.);
(* c_opp *)
assert (let c = make_complex 3. 4. in c_opp c = make_complex (-3.) (-4.));

(* c_exp *)
assert (let c = make_complex 3. 4. in c_exp c = make_complex (-13.1287830814621582) (-15.2007844630679543));

(* translate *)
assert (let c = make_complex 3. 4. and v = make_complex 2. 3. in translate c v = make_complex 5. 7.);

(* rotate0 *)
assert (let c = make_complex 3. 4. and angle = 3.14159265358979312 /. 4. in rotate0 c angle = make_complex (-0.707106781186547) 4.94974746830583268);

(* rotate *)
assert (let c = make_complex 3. 4. and angle = 3.14159265358979312 /. 4. and center = make_complex 1. 2. in rotate c angle center = make_complex 1.00000000000000022 4.82842712474619);
end

(* pour tester vos fonctions *)
let _ = test_mycomplex () 
