# TD 3



## Exercice 1 (voir Paint hihi)
```y86
        .pos 0
        irmovl stack, %esp
        mrmovl b, %eax
        mrmovl c, %edx
        orl %eax, %edx
        pushl %edx
        mrmovl d, %eax
        mrmovl e, %edx
        orl %eax, %edx
        popl %eax
        andl %eax, %edx
        rmmovl %ebx, a
        halt
```

## Exercice 2

### Question 1 (voir Paint hihi)
```y86
        .pos 0
        irmovl stack, %esp
        mrmovl b, %eax
        mrmovl c, %edx
        orl %eax, %edx
        pushl %edx
        mrmovl d, %eax
        mrmovl e, %edx
        orl %eax, %edx
        popl %eax
        andl %eax, %edx
        pushl %edx
        mrmovl f, %eax
        mrmovl g, %edx
        orl %eax, %edx
        pushl %edx
        mrmovl h, %eax
        mrmovl i, %edx
        orl %eax, %edx
        popl %eax
        andl %eax, %edx
        pol %eax
        addl %eax, %edx
        mrmovl %edx, a
        halt
```

### Question 2
???

## Exercice 3

### Question 1
```c
static tn[2] = {0, 0};

long ticket(long t) {
    return tn[t]++;
}
```

### Question 2
```y86
        .pos 0
        irmovl stack, %esp
        irmovl 1, %eax
        call ticket
        halt

ticket: addl %eax, %eax
        addl %eax, %eax
        mrmovl tn(%eax), %ecx
        iaddl 1, %ecx
        rmmovl %ecx, tn(%eax)
        rrmovl %ecx, %eax
        ret
```

---

# TD 4

## Exercice 1

### Question 1
```y86
        .pos 0
init:   irmovl stack,%esp
        mrmovl u, %eax
        pushl %eax      # param y(u)
        irmovl t, %eax
        pushl %eax      # param @x(t)
        call f
        iaddl 8, %esp
        halt

f:      mrmovl 4(%esp), %eax
        mrmovl 8(%esp), %ecx
        rmmovl %ecx, (%eax)
        ret

        .pos 0x200
t:      .long 0
u:      .long 2

stack:  

```

### Question 2
`Le registre serait simplement modifié. (peut être)`

## Exercice 2
```y86
        .pos 0
init:   irmovl stack,%esp
        irmovl p, %eax
        pushl %eax      # p dans param p
        mrmovl n, %eax  
        pushl %eax      # n dans param n
        call f
        iaddl 8, %esp
        halt

f:      mrmovl 4(%esp), %ecx    # n
        mrmovl 8(%esp), %edx    # p
bcl:    isubl 1, %ecx
        jl fin
        mrmovl (%edx), %eax
        iaddl 1, %eax
        rmmovl %eax, (%edx)
        iaddl 4, %edx
        jmp bcl
fin:    ret

        .pos 0x200
n:      .long 4
p:      .long 2
        .long 3
        .long 4
        .long 5
        
        .pos 0x250
stack:  

```

## Exercice 3
```y86
# %eax -> s(somme)
# %ecx -> n
# %edx -> pointeur sur elements
# %ebx -> pour changer element courant

# pas de main ici, juste la fonction somme

        .pos 0
somme:  pushl %ebx      # callee save
        xorl %eax, %eax # s = 0
        mrmovl 8(%esp), %ecx
        rrmovl %esp, %edx
        iaddl 12, %edx
bcl:    isubl 1, %ecx
        jl fin
        mrmovl (%edx), %ebx     # element courant
        addl %ebx, %eax         # s += vi
        iaddl 4, %edx
        jmp bcl
fin:    popl %ebx
        ret

        .pos 0x200
stack:  

```

## Exercice 5
`Tentative ratée`
```y86
        .pos 0
init:   irmovl stack,%esp
        irmovl j, %eax
        pushl %eax      
        mrmovl i, %eax  
        pushl %eax      
        call mult
        iaddl 8, %esp
        halt

mult:   xorl %ebx, %ebx
        mrmovl 4(%esp), %edx    
        mrmovl 8(%esp), %ecx    
bcl:    isubl 1, %ecx
        jl fin
        addl %edx, %ebx
        jmp bcl
fin:    ret

        .pos 0x200
i:      .long 3
j:      .long 5

        .pos 0x250
stack:  

```

## Exercice 6
```y86
        .pos 0
mult:   pushl %ebx
        xorl %eax, %eax
        mrmovl 8(%esp), %ecx    # i
        mrmovl 12(%esp), %edx   # j
        andl %ecx, %ecx         # i == 0 ?
        je fin
        rrmovl %ecx, %ebx
        iandl 1, %ebx           # test ik == 0 ?
        je suite
        addl %edx, %eax         # s += j
suite:  addl %edx, %edx         # j *= 2
        addl %ecx, %ecx         # décalage i
        jne bcl
fin:    popl %ebx
        ret

        .pos 0x200
stack:  

```

---

# TD 5

## Exercice 1 (' = NOT)
`f0(x, y) = O  ->  FALSE`  
`f1(x, y) = 'x.'y = '(x + y)`  
`f2(x, y) = 'x.y`  
`f3(x, y) = 'x.'y + 'x.y = 'x.('y + y) = 'x`  
`f4(x, y) = x.'y`  
`f5(x, y) = 'x.'y + x.'y = ('x + x).'y = 'y`  
`f6(x, y) = 'x.y + x.'y = x XOR y`  
`f7(x, y) = 'x.'y + x.'y + 'x.y = '(x.y) = x NAND y`  
`f8(x, y) = x.y = x AND y`  
`f9(x, y) = 'x.'y + x.y = x EQUIV y = '(x XOR y)`  
`f10(x, y) = 'x.y + x.y = y`  
`f11(x, y) = 'x.'y + 'x.y + x.y = 'f4 = '(x.'y) = 'x + y`  
`f12(x, y) = x.'y + x.y = x`  
`f13(x, y) = 'x.'y + x.'y + x.y = '('x.y) = x + 'y`  
`f14(x, y) = 'x.y + x.'y + x.y = x + y`  
`f15(x, y) = 1  ->  TRUE`

## Exercice 2
```
f1 = 'a.b.c
f2 = a.'b + 'a.b.'c
f3 = '(a + 'b + 'c) = 'a.b.c
f4 = '('a.'b).'(b.c).'(a.b.'c) = (a + b).('b + 'c).('a + 'b + c) = a.'b.c + a.'b.'c

a  b  c  f1  f2  f3  f4
0  0  0   0   0   0   0
0  0  1   0   0   0   0
0  1  0   0   1   0   1
0  1  1   1   0   1   0
1  0  0   0   1   0   1
1  0  1   0   1   0   1
1  1  0   0   0   0   0
1  1  1   0   0   0   0

=> f2 = f4
=> f1 = f3
```

## Exercice 3

### Question 1
`f1 = 'x.'y.'z + 'x.y.z + x.'y.'z + x.'y.'z + x.y.z`

### Question 2
`f2 = 'x.'y.z + 'x.y.'z + x.y.'z = 'x.(y XOR z)`

## Exercice 4

### Question 1
`'a XOR b = a XOR 'b = '(a XOR b)`

### Question 2

`Montrer associativité de XOR dans un ensemble E : V(a, b, c) € E, (a XOR b) XOR c = a XOR (b XOR c)`  
`(a XOR b) XOR c = (a XOR b).'c + '(a XOR b).c = (a XOR b).'c + (a XOR 'b).c = (a.'b + 'a.b).'c + (a.b + 'a.'b).c = a.'b.'c + 'a.b.'c + a.b.c + 'a.'b.c`  
`En developpant a XOR (b XOR c), on retrouve la meme chose`

# Exercice 5
`C7 et C4 incomplets`  
`C0 -> complet`  
`C1 -> x.y = '('x + 'y) = x.y -> complet`
`le reste = complet sauf C4`

---

# TD 6

## Exercice 1

### Question 1
NAND :  
'(x.x) = 'x  
'(x.1) = 'x  

NOR :  
'(x + x) = 'x
'(x + O) = 'x

### Question 2
f = (x XOR y) + (x.'z) = ''(x.'y + 'x.y + x.'z) = '('(x.'y).'('x.y).'(x.'z))    NAND
                                                = ''('('x + y) + '(x + 'y) + '('x + z)) NOR

x + y = ''(x + y) = '('x + 'y) = '('(x.x).'(y.y))

### Question 3
https://dept-info.labri.fr/ENSEIGNEMENT/archi/circuits/blank.html#wpVWw5HCjsKaQBR9w59kw7/DgcOwwqwbZkBAw5M0wrFqE8KTLjbCu8KmacOSw7RBYVRSZCwOXcOtZsO/wr04YGDDoMOAw5I3PcO3wpzDg8Kde8OvXHjCvcK/w6vDtcK0wpfDgBd7bUzCqMKuw7clwrBnw4FuL8K0wrFzA057w77CssOiPMOcw7DCszYWccOCMljDnMKgH8OXwr/CvcOewqsmLkfCpsKNwrXDmVR7w6tXwrDDpTMAwr/DjGd1w7BrcsOaL8K3w5vChkBUw4dXfMK3C1kdd8KXwqs6OHHDgSNdwoguwp/CkCcAwr9DEFLCj0EUw4vDqsKiSMOIwrYgw7ApOS3DgMKpU3jCmQDCusO5w5EEw6AHBG4CYcKfw5gudcKqB8KfwrhYw4fCl3nDpHHCn8OFwpBBBTdnTMOGW8KDUMO8wpjCnCFIIcOaZMKRw6JAMGMHw6QuYcOow7Q5CcODwokPw4/DoXIBJcKTw4hvw4EJGCZcwofDucOvZB1iJx8/YRF5EE/Cqw1xwrfCocOBw4/DiQbDuwBoMAcDw5I0OBJHwoppJAYuwoTDk8OcYcOkwpg0Dlgac8OZWSzCjjB0TWIdw73DgjF+eExCGMKawoQJw4TCpyHDt8KwGcOqD2g+wrrCqMOfwoJYwqTDjR8gw4EtJsKFw5fDmMOPbMOlw7rDrE/DoMKxE1zCuX0tw7DDk18pRU9/wqdreWTDtcK1wos2wqbClsOZw5fDgsO1wobChQ3CqznDn8KfwoXCnmR6Sk1pQCzCpzAAF8KrwqbCp8Kqwp7DmsK0w5BfOsOowo1cT8KyAxjCtlXDqMO/w6I9X8KIw41MbBBaTx7CvhFUw7lQwpUrwrl3wpBbwqpcSR3Dim9rwr/CsMKwcwvCqmcZw5BSw7vCusOoHVVvUMKnTS9ffcKFeMKUwonDjcK8w7Rqw7XCmsOfwp3CpcOZw5FVB8K1woDCnRzCiMOqwqDDlsKwwpNDPsKAw4PDq8ORwqslw6jDpmDDnBzDsibCkMO/w44hwp9Dw4vDlMK7w5bDocO6NVQyw4gnw5E2w4EtwpIfTsKlwr3DoMOxKGLCnsOgcXk1bGN+w4jCvR7CgsOow5oXw4HDswXDscOAE8KhwpcyKMKowrQ7w5XDqE41K1TDkkwdVsKowrTCmWpVwqhGM8OVw67CnsKAw5M9woFRwoVqwrdTScKJOmzCphLCvWJrwr7Dgy3Duzotw5zDqhjCtMKkK8K5ZV/Cq8KFW8KdGcOSMgnCklw2Ji3CrSDDlREbwr3DgyVdwrPCqA1kw4vDrEjCssOiw5wyEsKkOsK/w6TDlj15XcOvw6/DnsO+AQ==

### Question 4
???

### Question 5
???

## Exercice 2

### Question 1
x       y       Cin     
b2      b1      b0      p1      p0      Cout    s
0       0       0       0       0       0       0
0       0       1       0       1       0       1
0       1       0       0       1     
0       1       1       1       0       1       0
1       0       0       0       1
1       0       1       1       0       1       0
1       1       0       1       0
1       1       1       1       1       1       1

p0 = 'b2.'b1.b0 + 'b2.b1.'b0 + b2.'b1.'b0 + b2.b1.b0  
   = 'b2.(b1 XOR b0) + b2.('b1.'b0 + b1.b0)
   = 'b2.(b1 XOR b0) + b2.'(b1 XOR b0)

p1 = 'b2.b1.b0 + b2.'b1.b0 + b2.b1.'b0 + b2.b1.b0
   = 'b2.b1.b0 + b2.('b1.b0 + b1.'b0 + b1.b0)
   = 'b2.b1.b0 = b2.(b1.b0)

### Question 2
voir tab plus haut  

### Question 3
https://dept-info.labri.fr/ENSEIGNEMENT/archi/circuits/blank.html#wpXClVtvw5pAEMKFw58jw6U/wqB9DcKJw6zDtcKFwovCqkoUwqjChMOUwpgoQVXCpcKqD2AvYHXDsVLCs8ObwoDCosO8w7fCrMKNEWt8w6zDkjfDu8OMwpnDj8Ojw5nDscO4w63DtsKmw5Uiwq9xJMOXwqRvU8OLasOnw4LCmsOFwqvCtSTDvcOuScOYwq3DhcOrTAjCvhB7w5LCl8KpYkdZwp7CpMKfw5ltwqvDtUbDpGHDi0jCn8KMwobDpMK9fcKhTV/CgMO4bTzCqsKKT2rCt8KeLsKXNcKBwqTCqsOPw4Rqw4VZVQ/CpsKzwqo4CMOAIwPCqE7CnxETwog/wqAIwq3DmzhJw7PDrsKiCGdLEMO4wqJ2E8Oww5Zawp4qYHc/wrtAw7zChMOERSw7O8K2w5LCpGrDsFnDiHl6GCfCocKIWAodVAp3w4TDsnhjECY/wqo9FClUw6sQWgcJI8K2QcO0XMKGwqTCr8KKw7NBBMOfIxASwqYMwpLCqEHCt8OBMMOhPsKMw7/CqDnDh8KkCD9hwpLChFDDl8OdwoZ6UHPDgC9qwoE5QMK6H8KDAcKpG8KcXEcZw4NEw54HUMOWwrXDg8OIVsOVDsKYwo4FbC8nWxjDisKKwpgnwr9xTGweFcKHwqEBV1AfchFiGDofcMO4w6hDw70ewqdSH8O+PUo4w4XDssOELMO2w6vCuHIjw7Y3DsOZDsKuw5w2wokjfcKlLcKWwr7DlmvCucOnwrfDicKBw7TCqcOvwrYJwp8vGMKvWcONw4XDvjzDp8Obw4d8w6rDkBzDoFrDp8O8woV/RT4tw6fDqz/CiwHDsMKuADhlQMO2ZzoDw4AmwqsAw5wCQMOdHMOgw7hdA8OgXAHDsMOKAMK3w5QDwrBzKgDCvwzDsGxqAMOAfsKoADplwoBfw6rCgcOVwrTDhMOOwozDrsKRw6HDuFbDtSDChk/DlzF6J0bDt8OYCcKHw74/w4MuJsOSc8KLdlJjJMOvwq5kFFPDqXnDhVTCmR3CvSt9JcKhSBIWSsKRwpofw4oyFcKbwqIrD3HCkhUkRUF+EErCmh0tW23Dg0rCm8Ktw5TCsDrDtcOWw55FAW7Cs8OVLMOAa8K2wpoFw7jDtVbDm8K6wqjCoMOzD8KvWUI3w7PDmsO1XsKzwoZewoPDl0Zcwqs4w4jDm8Kbw7cP

---

# TD 10

## Exercice 1

###  Question 1
30f30b

30f10c  
3 -> 

6031
6 -> opl  
0 -> addl  
3 -> rA = ebx  
1 -> rB = ecx

2010  
20 -> rrmovl  
1 -> rA = ecx  
0 -> rB = eax

## Exercice 2

### Question 1
OUI (pakompri)

### Question 2
MDR

## Exercice 3

### Question 1
iaddl 14, %eax  
6..rB

### Question 3
need_regids -> rajouter IOPL  
need_valC -> rajouter IOPL  
instr_valid -> > rajouter IOPL  
srcB : rB -> rajouter IOPL  
dstE : rB -> rajouter IOPL
aluA : valC -> rajouter IOPL
aluB : valB -> rajouter IOPL
alufun -> rajouter IOPL  
set_cc -> rajouter IOPL

---

# TD 11

## Exercice 1

### Question 1
Durée minimal du cycle d'horloge CLK = 120 ps (pico-secondes)  
f = 1/P = 1/120x10⁻¹² = 8.33x10⁹ (B = 8.33 Gops (Giga operations))
Delai de propagation D = 3 * 120 = 360 ps  
Profondeur du pileline : 3

### Question 2
CLK = 170 ps  
B = 1/510x10⁻¹² = 5.88 Gops  
D = 3 * 170 = 510 ps

## Exercice 2

### Question 1
A : 80  
B : 60  
(L)   
C : 30  
D : 50  
E : 70  
F : 10  

On met le latch juste après B pour avoir 160 ps en haut et 180 ps en bas  

CLK = 180 ps  
D = 2x180 = 360 ps
B = 1/180x10⁻¹² = 5.88 Gops

### Question 2
A : 80  
(L)  
B : 60   
C : 30  
(L)
D : 50  
E : 70  
F : 10  

CLK = 150 ps  
D = 3x150 = 450 ps  
B = 1/150x10⁻¹² = 6.66 Gops

### Question 3

A : 80  
(L)  
B : 60  
(L)   
C : 30  
D : 50  
(L)   
E : 70  
F : 10  

CLK = 100 ps  
D = 400 ps  
B = 10 Gops

### Question 4

A : 80  
(L)  
B : 30  
(L)   
C : 60  
(L)  
D : 50  
(L)   
E : 70  
F : 10  

CLK = 100 ps  
D = 500 ps  
B = 10 Gops

## Exercice 3

### Question 1
![image](TD%2011.png)

### Question 2
CLK = 120 ps  
D = 480 ps  
B + 8.33 Gops