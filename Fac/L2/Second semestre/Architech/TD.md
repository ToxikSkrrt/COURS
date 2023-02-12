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