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
