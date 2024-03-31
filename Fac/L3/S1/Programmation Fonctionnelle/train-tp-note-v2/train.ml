(* IMPLEMENTATION DES TYPES *)

type arbre = Noeud of arbre * arbre | Feuille

type point_nul = Point of int * int

type point = int * int

type point_bis = {x : int; y : int}

type func_point = point -> bool

(* IMPLEMENTATION CONSTRUCTEURS *)

let make_arbre = Noeud (Noeud (Feuille, Feuille), Feuille)  (* cas un peu particulier donc ff *)

let make_point_nul x y = Point (x, y)

let make_point x y : point = x, y

let make_point_bis x y = {x = x; y = y}

let oui = fun _ -> true (* cas particulier *)

(* IMPLEMENTATION ACCESSEURS *)

let get_x_nul point_nul = let Point (x, _) = point_nul in x

let get_y_nul point_nul = let Point (_, y) = point_nul in y

let get_x (point : point) = let x, _ = point in x

let get_y (point : point) = let _, y = point in y

let get_x_bis point_bis = point_bis.x

let get_y_bis point_bis = point_bis.y

(* FONCTIONS *)

let exists (point : point) (func_point : func_point) = func_point point

let inf3 = fun point -> get_x point < 3

(* TESTS *)

let test () =
  let point_nul = make_point_nul 1 2 in
  let point = make_point 1 2 in
  let point_bis = make_point_bis 1 2 in
  begin
    assert (get_x_nul point_nul = get_x point && get_x_nul point_nul = get_x_bis point_bis);
    assert (get_y_nul point_nul = get_y point && get_y_nul point_nul = get_y_bis point_bis);
    assert (inf3 point);
  end

let _ = test ()

(* AUTRES *)

let compose f g = fun x -> f (g x)

let _ = compose (fun x -> 2 * x) (fun x -> x + 10) 3

(* let rec map f =
  fun l ->
    match l with
    | [] -> []
    | h :: t -> f h :: map f t *)

let map f =
  fun l ->
    let rec aux l acc =
      match l with
      | [] -> List.rev acc
      | h :: t -> aux t (f h :: acc)
    in aux l []

type uwu = int -> bool



type ratio = Ratio of int * int

type rset = ratio -> bool

let rset_empty : rset = fun r -> false

let rset_member r rset = rset r