type mycomplex = C of float * float

(* constructeur *)                    
let make_complex realp imagp = C(realp, imagp)

(* accesseurs *)
let realpart c = match c with C(x, _) -> x
let imagpart c = match c with C(_, y) -> y

let c_origin = make_complex 0.0 0.0
let c_i = make_complex 0. 1.

let p_12 = make_complex 1. 2.
let p_34 = make_complex 3. 4.

let c_abs c = let x, y = realpart c, imagpart c in
	sqrt (x *. x +. y *. y)

let c_sum c1 c2 = make_complex (realpart c1 +. realpart c2) (imagpart c1 +. imagpart c2)

let c_dif c1 c2 = make_complex (realpart c1 -. realpart c2) (imagpart c1 -. imagpart c2)

let c_opp c = c_dif c_origin c

let c_mul c1 c2 = let x1, y1 = realpart c1, imagpart c1
	and x2, y2 = realpart c2, imagpart c2 in
	make_complex (x1 *. x2 -. y1 *. y2) (x1 *. y2 +. x2 *. y1)

let c_sca lambda c = make_complex (lambda *. realpart c) (lambda *. imagpart c)

let c_exp c = let x, y = realpart c, imagpart c in
  c_sca (exp x) (make_complex (cos y) (sin y))

let translate c vector =
  c_sum c vector

let rotate0 c angle =
  c_mul (c_exp (c_sca angle c_i)) c

let rotate c angle center =
  translate (rotate0 (translate c (c_opp center)) angle) center
