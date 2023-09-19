# TD 1

## Exercice 1

1.
a) (a + ba)*
- 0 : E (epsilon)
- 1 : {a}
- 2 : {ba, aa}
- 3 : {aaa, baa, aba}
- 4 : {aaaa, aaba, baba, abaa, baaa}

b) a(aa + b(ab)*a)*a
- 0 : ∅
- 1 : ∅
- 2 : {aa}
- 3 : ∅
- 4 : {aaaa, abaa}

2.
L V w € L : |w| mod 2 = 0  
L* V u € L* : |u| mod 2 = 0 ?  
si Ǝ u L* : |u| mod 2 = 1,  
alors prenoms Umin € L* :  
|Umin| est umpair et minimal  
Umin = wv, w € L\{E}, v € L*  
Umin = Ew2w3w4...wk  
w -> premier non vide  
v -> reste après w  
|w| mod 2 = 0  
|v| = |Umin| - |w|  
L* : {u = w1...wk}  
V k € N : |w1...wk| est toujours pair  
L* = {E} = L⁰ + L¹ = L + L² + L³...  
V k, V u € L^k, |u| mod 2 = 0  


Base : k = 0 : L⁰ = {E}  
u € L⁰ => u = E => |u| = 0  

Hérédité : L^(k+1) - ?  
K^(k + 1) = LL^k  
u € L^(k + 1) => u = wuk : w € L, uk € L^k  
|u| = |w| + |uk|  source : tkt

3.
(a + ba)* vs "pas de bb"  

## Exercice 2

1.
a*b*    ->  tkt frr  
w € L(a*b*)  
k := |w|a  

Induction par k  
Base : k = 0, w ne contient que b, w € L(b*) <= L()L(b*) <= L(a*b*)  
Hérédité : |w|a = k + 1  
|w|a > 0 => la 1e lettre de w est a  
w = av, |v|a = |w|a - 1 = k  
        |w|a = |v|a + 1
v € L(a*b*)  
v = v1v2, v1 € L(a*), v2 € L(b*)  
w = (av1)v2     av1 € L(a*)     av1 = a^(k + 1)

2.
(b*ab*ab*)b* ou (b*ab*a)*b*  
si |w|a mod 2 = 0, alors `w € L((b*ab*a)*b*)`

3.
(aplupluplouwu)

4.
(a + b)*ba