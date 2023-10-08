let rec op_prod n p f op neutral =
  let rec aux acc =
    if n > p || p < n || n = 0 && p = 0 then
      neutral
    else
      let x = n in
      if x > p then
        acc
      else
       op (f x) (op_prod (n + 1) p f op neutral)
  in aux neutral
;;