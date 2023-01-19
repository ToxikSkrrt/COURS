# TD 1

## 1.1

```ocaml
let x = 5.0 in x *. x +.

- : float = 55.


let x = 5 in let y = 6 in y + 2 * x

- : int = 16
```

## 1.2

```ocaml
let x = 10 in if x > 0 then "positif" else "negatif"

- : string = "positif"


let x = 5 in let y = 2 in if x < y then "inf" else "sup"

- : string = "inf"


let helloworld langue =
    match langue with
        "francais" -> "Bonjour"
        "anglais" -> "Hello"
        "espagnol" -> "Hola"
        "allemand" -> "Hallo"
        autre -> "Je ne parle pas " ^ autre

# helloworld "francais";;
- : string = "Bonjour"
```

## 1.3

```ocaml
let f = fun x y -> x - y in f (f 1 2) 3

- : int = 2


let cube x = x * x * x in (cube 2) + (cube 3)

- : int = 35
```

## 1.4

```ocaml
let rec fact n =
    if n = 0
    then 1
    else n * fact (n - 1)

# fact 5;;
- : int = 120
```

## 1.5

```ocaml
let rec somme n =
    if n = 0
    then 0
    else n + somme (n - 1)

# somme 2;;
- : int = 3
```

## 1.6

```ocaml
let rec pgcd n p =
    if p = 0
    then n
    else pgcd p (n mod p)

# pgcd 20 10;;
- : int = 10
```

## 1.7

```ocaml
let rec fib n =
    if n = 0
    then 1
    else if n = 1
         then 1
         else fib (n - 1) + fib (n - 2)

# fib 4;;
- : int = 5
```

## 1.8

```ocaml
type vect = Vint of int * int * int | Vfloat of float * float * float

# Vint (1, 2, 3);;
- : vect = Vint (1, 2, 3)
# Vfloat (1., 2., 3.);;
- : vect = Vfloat (1., 2., 3.)
# (1, 2, 3);;
-: int * int * int = (1, 2, 3)
```

## 1.9

### 1.

```ocaml
type trois_valeurs = Vrai | Faux | Peut_Etre

let x = Faux
let vrai = Vrai

- : val x : trois_valeurs = Faux
- : val vrai : trois_valeurs = Vrai
```

### 2.
A FAIRE

### 3.
A FAIRE

## 1.10
A FAIRE

```ocaml
type natPeano = Zero | Succ of natPeano
```

## 1.11

### 1.

a)  
t = 7  
h = 2  
Parfait  

b)  
t = 13  
h = 4  
Complet  

c)  
t = 7  
h = 3  
???  

d)  
t = 8  
h = 3  
Quasi parfait  

### 2.

Voir Paint hihi (trèèèèèèès vite fait)

### 3.

Voir Paint hihi (en fait non)

## 1.12

### 1.

```ocaml
(* Taille *)
n(t) = 0 si t = Empty
       1 + n(left(t)) + n(right(t)) sinon

(* Hauteur *)
h(t) = -1 si t = Empty
       1 + max(h(left(t)), h(right(t))) sinon

(* Nombre de noeuds internes *)
i(t) = 0 si t = Empty
       0 si left(t) = right(t) = Empty
       1 + i(left(t)) + i(right(t)) sinon

(* Nombres de feuilles *)
l(t) = 0 si t = Empty
       1 si left(t) = right(t) = Empty
       l(left(t)) + l(right(t)) sinon
```

### 2.

```ocaml
type 'a btree = Empty | Node of 'a * 'a btree * 'a btree

let rec size a =
    match a with
        Empty -> 0
        Node (e, fg, fd) -> 1 + size fg + size fd

let n1 = Node (10, Empty, Empty)
let n3 = Node (1, Node (2, Node (3, Empty, Empty), Empty), Empty)
```

## 1.14
```ocaml
l(t) = 1 + i(t)
```

### 1)
```ocaml
tb = O
l(tb) = 1
i(tb) = 0

1 =?= 1 + 0
1 == 1 (* P est vraie *)
```

### 2)
```ocaml
t = (a, fg, fd)
l(t) = l(fg) + l(fd)
l(fg) = 1 + i(fg) (* PAR SUPPOSITION *)
l(fd) = 1 + i(fd) (* PAR SUPPOSITION *)
l(t) = 1 + i(fg) + 1 + i(fd)

l(t) = 1 + i(t)
```

```ocaml
n(t) = 2 * l(t) - 1 et n(t) = 2 * i(t) + 1
```

### 1)
```ocaml
tb = O
l(tb) = 1
n(tb) = 1

1 =?= 2 * 1 - 1
1 == 1 (* P est vraie *)
```

### 2)
```ocaml
t = (v, fg, fd)
n(t) = n(fd) + n(fg) + 1

(* On suppose que P' est vraie pour fg et fd *)

n(fg) = 2 * l(fg) - 1
n(fd) = 2 * l(fd) - 1
n(t) = (2 * l(fg) - 1) + (2 * l(fd)) - 1 + 1
n(t) = 2 * (l(fg) + l(fd)) - 1
l(t) = l(fg) + l(fd)
n(t) = 2 * l(t) - 1
(* P est vraie *)
```

# TD 2

## 2.1

```ocaml
(2n n) == "n parmi 2n"
```

### 1.

```ocaml
1/(1 + 1) * (2 1) = 1

1/(2 + 1) * (4 2) = 2

1/(3 + 1) * (6 3) = ?
```

### 2.

???

### 3.

???

## 2.2

### 2.

hauteur min d'un arbre de taille 7 = 3 ?

### 3.

hauteur max d'un arbre de taille 7 = 4 ?

### 4.

???

