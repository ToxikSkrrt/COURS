(* Exercice 8.1 *)

type subject = Selfie | Monument | Miroir_d_Eau | Mode | People | Mon_assiette_au_resto

type photo = Photo of int * (subject list)

type album = photo list

let mon_album =
  [Photo(2016, [Selfie; Miroir_d_Eau]);
  Photo(2014, [Selfie; People]);
  Photo(2014, [Selfie; Monument; Mode]);
  Photo(2012, [Mon_assiette_au_resto; People])]

(* 1. *)
let photo_year (photo : photo) : int = let Photo(year, _) = photo in year

let photo_subjects (photo : photo) : subject list = let Photo(_, subjects) = photo in subjects

(* 2. *)
let has_subject (subject : subject) (photo : photo) : bool =
  List.mem subject (photo_subjects photo)

(* 3. *)
let select_by_subject (subject : subject) (album : album) : album =
  List.filter (has_subject subject) album

(*
let select_by_subject (subject : subject) (album : album) : album =
  let rec aux album acc =
    match album with
    | [] -> acc
    | h::t ->
      if has_subject subject h then
        aux t (h::acc)
      else
        aux t acc
  in aux album []
*)

(* 4. *)
let select_by_date (f : int -> bool) (album : album) : album =
  List.filter (fun photo -> f (photo_year photo)) album

(*
let select_by_date (f : int -> bool) (album : album) : album =
  let rec aux album acc =
    match album with
    | [] -> acc
    | h::t ->
      if f (photo_year h) then
        aux t (h::acc)
      else
        aux t acc
  in aux album []
*)

(* Exercice 8.2 *)

type criteria =
Subject of subject
| Date of (int -> bool)
| Or of criteria * criteria
| And of criteria * criteria
| Not of criteria

(* 1. *)
let critere = And (And (Subject Selfie, Not (Subject People)), Date (fun x -> x >= 2014))

(* 2. *)
let rec satisfies (criteria : criteria) (photo : photo) : bool =
  match criteria with
  | Not c -> not (satisfies c photo)
  | And (c1, c2) -> (satisfies c1 photo) && (satisfies c2 photo)
  | Or (c1, c2) -> (satisfies c1 photo) || (satisfies c2 photo)
  | Date (f) -> f (photo_year photo)
  | Subject (s) -> has_subject s photo

(* 3. *)
let select (criteria : criteria) (album : album) : album =
  List.filter (satisfies criteria) album  
