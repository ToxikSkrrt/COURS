# COURS

Utiliser VS Code  
(Ou interpréteur Utop)  

L’opération ‘+’ est typé

```ocaml
3.14 + 3.14;;

- : Error


3.14 +. 3.14;;

- : float = 6.28
```

```ocaml
( + );;

- : int → int → int
```

premier int = premier argument  
deuxième int = deuxième argument  
troisième int = type renvoyé  

```ocaml
fun x → x + 1 ;;

- : int → int = <fun>
```

'a correspond à n'importe quel type  
Permet de faire des fonctions polymorphes

```ocaml
if 1 < 2 then "OK" else "KO";;

- : string = "OK"
```

```ocaml
();;

- : unit = ()
```

```ocaml
let func x y z = x + y + z;;
```

Type List
```ocaml
type intlist = Null | Cellule of int * intlist


Null;;

- : intlist = Null


Cellule (1, Null);;

- : intlist = Cellule (1, Null)
```