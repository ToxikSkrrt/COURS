#load "funcs.cmo"
open Funcs

let test () =
  begin
    assert (fact 5 = 120);
    assert (fact 0 = 1);
    assert (sum 5 = 15);
    assert (sum 0 = 0);
  end

let _ = test ()