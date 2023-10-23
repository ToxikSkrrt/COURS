let fact n =
  let rec aux n acc =
    if n < 1 then
      acc
    else
      aux (n - 1) (acc * n)
  in aux n 1

let sum n =
  let rec aux n acc =
    if n < 1 then
      acc
    else
      aux (n - 1) (acc + n)
  in aux n 0

let sum_interval n p =
  let rec aux n acc =
    if n > p then
      acc
    else
      aux (n + 1) (acc + n)
  in aux n 0

type point = {x : int; y : int}

let getX point = point.x

let getY point = point.y

let makePoint x y = {x = x; y = y}