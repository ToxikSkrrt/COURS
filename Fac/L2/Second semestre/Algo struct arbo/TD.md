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
    if n = 0 || n = 1
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

## 1.15

### a)
P1 : h(t) + 1 <= n(t)
P2 : h(t) <= 2^(h(t) + 1) - 1

P1 :

1. Cas de base : si t est l'arbre nul

h(t) + 1 = -1 + 1 = 0
n(t) = 0
0 <= 0 donc P1 est vraie

2. Cas récursif

t = (x, g, d)
-> sur g, P1 vraie [ h(g + 1) + 1 <= n(g) ]
   sur d, ...

h(t) + 1 = 1 + max(h(g), h(d)) + 1
On suppose h(g) <= h(d)
h(t) + 1 = 1 + h(g) + 1
Avec P1: h(t + 1) <= 1 + n(g) < 1 + n(d) + n(g) = n(t)
on sait que h(0) =/= 0, n(0) > 0
-> P1 est vraie sur t

P2 :

1. Cas de base

n(t = O) = 0
2^(h(O) + 1) - 1 = 2^(-1 + 1) - 1 = 0
-> P2 est vraie pour t = O

2. Cas récursif

t = (x, g, d), g et d =/= O
P2 est vraie pour g et d
n(t) = 1 + n(g) + n(d) <= 1 + 2^(h(g) + 1) - 1 + 2^(h(d) + 1) - 1
On suppose h(g) >= h(d)
= 1 + 2^(h(g) + 1) - 1 + 2^(h(g) + 1) - 1 = 2 * 2^(h(g) + 1) - 1
h(t) = 1 + h(g)
n(t) <= 2 * 2^(h(t) - 1) = 2^(h(t) + 1) - 1
Donc P2 est vraie pour t

---

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

## 2.6
```ocaml
let rec btree_mem x t =
    match t with
    | Empty -> false
    | Node (v, g, d) -> if v = x 
                        then true 
                        else (btree_mem x g) || (btree_mem x d)
```

## 2.6 bis
```ocaml
let rec list_mem x l =
    match l with
    | [] -> false
    | head::tail -> if x = head
                    then true
                    else list_mem x tail
```

## 2.8
```ocaml
let rec btree_is_full t =
    match t with
    | Empty -> true
    | Node (_, Empty, Empty) -> true
    | Node (_, Empty, _) -> false
    | Node (_, _ , Empty) -> false
    | Node (_, l, r) -> (btree_is_full l) && (btree_is_full r)
```

## 2.9
```ocaml
let rec btree_is_perfect t =
    match t with
    | Empty -> true
    | Node (_, l, r) -> (btree_height l) = (btree_height r) && (btree_is_perfect l) && (btree_is_perfect r)
```

---

# TD 3

## Exercice 4

### 2.
```ocaml
let rec recherche t x = 
    match x with
    | Empty -> false
    | Node (v, l, r) -> if v = x
                        then true
                        else if v < x
                             then recherche r x
                             else recherche l x

let rec bst_search t x =
    match t with
    | Empty -> 0
    | Node ((v, m), l, r) -> if v = x
                             then m
                             else if v < x
                                  then bst_search r x
                                  else bst_search l x
```

## Exercice 5

### 2.
```ocaml
let rec insert t x =
    match t with
    | Empty -> Node (x, Empty, Empty)
    | Node (v, l, r) -> if x = v
                        then t
                        else if x > v
                             then Node (v, l, insert r x)
                             else Node (v, insert l x, r)

let rec bst_insert t x =
    match t with
    | Empty -> Node ((x, l), Empty, Empty)
    | Node ((k, m), l, r) -> if k = x
                             then Node ((k, m + 1), l, r)
                             else if k < x
                                  then Node ((k, m), l, bst_insert r x)
                                  else Node ((k, m), bst_insert l x, r)
```

---

# TD 4

## Exercice 1

### 1.

### 2.
```ocaml
let rec bst_max t =
    match t with
    | Empty -> failwith "Empty tree"
    | Node (v, l, r) -> if r = Empty
                        then v
                        else bst_max r

let rec bst_min t =
    match t with
    | Empty -> failwith "Empty tree"
    | Node (v, l, r) -> if l = Empty
                        then v
                        else bst_min l
```

## Exercice 2

### 3.
```ocaml
let rec bst_pop_max t =
    match t with
    | Empty -> failwith "Empty tree"
    | Node((c, m), l, Empty) -> l, (c, m)
    | Node((c, m), l, r) -> let bstr, maxr = bst_pop_max r in Node((c, m), l, bstr), maxr;;
```

### 4.
```ocaml
let rec bst_remove t x =
    match t with
    | Empty -> t
    | Node((c, m), l, r) -> if x = c
                            then (* x = c *) if m > 1
                                             then Node((c, m - 1), l, r)
                                             else if l = Empty
                                                  then r
                                                  else let l_without_max, max = bst_pop_max l
                                                  in Node(max, l_without_max, r)
                            else (* x != c *) if x < c
                                              then Node((c, l), ???)
```

`Parcours infixe = ordre croissant` 

`préfixe = r + fg + fd`  
`infixe = fg + r + fd`  
`postfixe = fg + fd + r`

```ocaml
let rec prefixe t =
    match t with
    | Empty -> []
    | Node(v, l, r) -> [v] @ (prefixe l) @ (prefixe r)
```

```ocaml
let rec infixe t =
    match t with
    | Empty -> []
    | Node(v, l, r) -> (infixe l) @ [v] @ (infixe r)
```

```ocaml
let rec postfixe t =
    match t with
    | Empty -> []
    | Node(v, l, r) -> (postfixe l) @ (postfixe r) @ [v]
```

```ocaml
let rec nbNoeuds t =
    match t with
    | Empty -> 0
    | Node(v, l, r) -> 1 + nbNoeuds l + nbNoeuds r
```

---

# TD 5

`Equilibre d'un noeud : eq(t) = h(l) - h(r)`

## Exercice 1

### 1.

## Exercice 3

### 1.
```ocaml
let rec get_height t = 
  match t with
  | Empty -> -1
  | Node((v, h), l, r) -> h
;;
```

### 2.
```ocaml
let rec tag_node c l r =
  let hl = get_height l in 
  let hr = get_height r in
  if (hl < hr) 
  then Node((c, hr + 1), l, r)
  else Node((c, hl + 1), l, r)
;;
```

## Exercice 8
Voir photo sur tel

---

# TD 6

## Exercice 1
Arbres quasi parfaits de taile 2 :  
(voir image (soon))

t1 -> (r1, left1, right1)  
1. h(left1) = h(right1) + 1
2. left1 -> qp  
   right1 -> p

t3 ->
1. h(left3) = h(right3)
2. left3 -> p
   right3 -> qp

---

# TD 10

## Exercice 1

### Question 1
MOODLE  
M -> 1  
O -> 2  
D -> 1  
L -> 1  
E -> 1

```ocaml
let rec insert_sorted x l key_fun =
  match l with
  | [] -> [x]
  | h::t -> if key_fun x <= key_fun h
            then x::l
            else h::insert_sorted x t key_fun 
;;
```

### Question 2
```ocaml
let rec insertion_sort l key_fun =
  let rec aux l acc =
    match l with
      | [] -> acc
      | h::t -> aux t key_fun (insert_sorted h acc key_fun)
    in aux l []
;;

OR

let rec insertion_sort l key_fun =
  match l with
  | [] -> []
  | h::t -> insert_sorted h (insertion_sort t key_fun) key_fun
;;
```

## Exercice 2

pas fait ptdr

## Exercice 3

### Question 1
```ocaml
let rec add_char c occlist =
  match occlist with
  | [] -> [(c, 1)]
  | (cchar, cocc)::t -> if c < cchar
                        then (c, 1)::occlist
                        else 
                          if c = cchar
                          then (c, cocc + 1)::t
                          else (cchar, cocc)::add_char c t
;;
```

### Question 2
???

### Question 3
```ocaml
let rec charlist_to_treelist charlist =
  match charlist with
  | [] -> []
  | (c, occ)::t -> (Leaf(c), occ)::charlist_to_treelist t
;;
```

### Question 4
```ocaml
let rec treelist_to_hufftree treelist =
  match treelist with
  | [] -> failwith "error"
  | (t, _)::[] -> t
  | (t1, occ1)::(t2, occ2)::tail -> treelist_to_hufftree (insert_sorted (Node(t1, t2), occ1 + occ2) tail snd)
;;
```
## Exercice 4

### Question 1
```ocaml
let codelist hufftree =
  let rec aux hufftree path acc =
    match hufftree with
    | Leaf(c) -> (c, List.rev path)::acc
    | Node(left, right) -> let lacc = aux left (0::path) acc 
  in aux right (1::path) lacc in List.rev (aux hufftree [] [])
;;
```

### Question 2
```ocaml
