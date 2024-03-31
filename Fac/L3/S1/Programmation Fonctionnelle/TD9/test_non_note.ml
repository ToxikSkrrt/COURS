(* 1.2 *)
let m_empty = fun x -> 0

let m_multiplicity e mset = mset e

let m_full count = fun x -> count

let m_adjoin e mset count =
  fun x ->
    let m = m_multiplicity e mset in
    if x = e then m + count else count

let m_remove e mset count =
  fun x ->
    let m = m_multiplicity e mset in
    if x = e then max (m - count) 0 else m

let m_union mset1 mset2 =
  fun x ->
    let m1 = m_multiplicity x mset1 in
    let m2 = m_multiplicity x mset2 in
    m1 + m2

let m_intersection mset1 mset2 =
  fun x ->
    let m1 = m_multiplicity x mset1 in
    let m2 = m_multiplicity x mset2 in
    min m1  m2