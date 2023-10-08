
(*for repl without dune *)
(*
#use "mycomplex.ml"
or
#load "mycomplex.cmo"
  if file already compiled
*)

open Mycomplex

(* A point in a 2-dimensional space is represented by a complex of type mycomplex *)
let make_point x y = make_complex x y

(* A zone is represented as a function that takes a point as a parameter and returns true
   if and only if the point is in the zone, and false otherwise.
*)

type zone = mycomplex -> bool
type point = mycomplex

(* A zone that contains every point. A point is always in this zone. *)
let everywhere = fun _ -> true

(* A zone that contains no points.  A point is never in this zone. *)
let nowhere = fun _ -> false

(* point_in_zone_p (make_point 3.5 2.1) everywhere *)

(*  To determine whether a point is in a zone, just call this function. *)
let point_in_zone_p (point: point) (zone: zone) = zone point

(* Create a circular zone with center in (0,0) with the indicated radius. *)
let make_disk0 radius = fun point -> c_abs point <= radius

(* Given a zone, move it by a vector indicated as a complex number
   passed as the argument. *)
let translate_zone zone vector = fun p -> point_in_zone_p (c_dif p vector) zone
                                   
(* Given two zones, create a zone that behaves as the intersection of the two. *)
let zone_intersection zone1 zone2 =
  fun p -> point_in_zone_p p zone1 && point_in_zone_p p zone2

(* Test all zone_manipulating code. *)
let test = 
  let c = make_disk0 1. in
  let c1 = translate_zone c (make_point 1. 0.) in
  assert (point_in_zone_p (make_point 0.0 0.5) c);
  assert (not (point_in_zone_p (make_point 1.0 0.5) c));
  assert (point_in_zone_p (make_point 0.5 0.) (zone_intersection c c1))

(* Make a rectangle in the first quadrant. *)
let make_rectangle width height =
  fun p -> realpart p >= 0. && realpart p  <= width && imagpart p >= 0. && imagpart p <= height
;;

(* Given two zones, create a zone that behaves as the union of the two. *)
let zone_union zone1 zone2 =
  fun p -> point_in_zone_p p zone1 || point_in_zone_p p zone2
;;

(* Given a zone, create a zone that contains every point not in zone. *)

let zone_complement zone =
  fun p -> not (point_in_zone_p p zone)
;;

(* Given two zones, create a zone that contains every point in zone1 except the ones that are in zone2. *)
let zone_difference zone1 zone2 =
  fun p -> point_in_zone_p p zone1 && not (point_in_zone_p p zone2)
;;

(* let make_disk radius center = *)

(* point_in_zone_p (make_point 2. 2.) (make_disk 1. (make_point 1.5 1.5)) *)

(* Scale a zone in two dimensions *)
(* let scale_zone0 zone coeff = *)
  
(* Test scale_zone *)
(* point_in_zone_p (make_point 5. 5.) (scale_zone0 (make_disk0 2.) (make_point 10. 10.)) *)

(* let scale_zone zone coeff origin = *)

(*  
let _ = point_in_zone_p (make_point 6.0 0.5) (scale_zone0 (make_disk 1. (make_point 4.0 4.0)) (make_point 6.0 4.0))
*)

(* let c_i = make_point 0. -1. *)

(* let rotate_zone0 zone angle = *)

(* point_in_zone_p (make_point 0.5 8.) (rotate_zone0 (make_rectangle 10. 2.) (3.1416 /. 2.)) *)

(* let rotate_zone zone angle center = *)
