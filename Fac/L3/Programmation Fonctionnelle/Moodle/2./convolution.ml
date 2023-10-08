let rec sum_product f g i j =
  let rec aux acc =
    let k = i in
    if k > j then
      acc
    else
      (f k) * (g (j - k)) + sum_product f g (i + 1) j
  in aux 0
;;

let rec convolution f g =
  fun n -> sum_product f g 0 n
;;