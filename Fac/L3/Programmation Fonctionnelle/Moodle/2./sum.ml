let rec sum n p = 
  let rec aux acc = 
    if n > p || p < n || n = 0 && p = 0 then
      0
    else
      let x = n in
      if x > p then
        acc
      else
        x + sum (n + 1) p
  in aux 0
;;