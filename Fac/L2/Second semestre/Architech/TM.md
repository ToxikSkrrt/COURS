# TM 1

## Exercice 1

### Question 1

```y86
        .pos 0
init:   irmovl 43, %eax
        irmovl 26, %ecx
        rrmovl %eax, %edx
        addl %ecx, %edx
        halt

```

### Question 2

```y86
        .pos 0
init:   irmovl 43, %eax
        irmovl 26, %ecx
        rrmovl %eax, %edx
        andl %ecx, %edx
        halt

```
=> Le résultat est 10  
43 = 101011  
26 = 011010  
101011 AND  
011010 =  
001010  
= 8 + 2 = 10

### Question 3

```y86
        .pos 0
init:   irmovl 43, %eax
        irmovl 26, %ecx
        rrmovl %eax, %ebx
        xorl %ecx, %ebx
        halt

```
=> Le résultat est 49
101011 XOR  
011010 =  
110001  
= 32 + 16 + 1 = 49

## Exercice 2

### Question 1

ZF Flag (Zero Flag) :

```y86
        .pos 0
init:   irmovl 43, %eax
        irmovl 43, %ecx
        rrmovl %eax, %ebx
        subl %ecx, %ebx
        halt

```

OF Flag (Overflow Flag) :

```y86
        .pos 0
init:   irmovl 0x8fffffff, %eax
        irmovl 0x8fffffff, %ecx
        rrmovl %eax, %ebx
        addl %ecx, %ebx
        halt

```

SF Flag (Sign Flag) :

```y86
        .pos 0
init:   irmovl 26, %eax
        irmovl 43, %ecx
        rrmovl %eax, %ebx
        subl %ecx, %ebx
        halt

```

### Question 2

SF = 1

```y86
        .pos 0
init:   irmovl 1, %eax
        irmovl 43, %ecx
        rrmovl %eax, %ebx
        subl %ecx, %ebx
        halt

```



```y86
        .pos 0
init:   irmovl 1, %eax
        irmovl 0x8fffffff, %ecx
        rrmovl %eax, %ebx
        subl %ecx, %ebx
        halt

```

# TD 2

## Exercice 1
```y86
        irmovl 0, %eax  # sum
        irmovl 1, %ecx  # i <- 1
bcl:    rrmovl %ecx, %edx  # copie de i dans %edx
        isubl 10, %edx
        jg suite  # jg -> ZF = SF = 0 | jl -> SF = 1 | je -> ZF 1 | jne -> ZF = 0
        addl %ecx, %eax
        iadd 1, %ecx
        jmp bcl
suite:
```

## Exercice 2

### Question 1
???

### Question 2
???

### Question 3
```y86
        mrmovl n, %edx
        irmovl 1, %eax  # bit balayage
        xorl %ecx, %ecx  # compteur de bits
bcl:    rrovl %edx, %ebx
        andl %eax, %ebx
        je pasun
        iaddl 1, %ecx
pasun:  addl %eax, %eax  # décalage bit vers la gauche (2x)
        jne bcl
        rmovl %ecx, c
```

## Exercice 3
```y86
        irmovl x, %esi  # p = &x
        mrmovl (%esi), %ebx  # a = *p
        rmmovl %ebx, a  # a = 
        mrmovl b, %ebx  # *p = b
        mrmovl %ebx, (%esi)  # *p = 
        irmovl b, %esi  # p = &b
        mrmovl (%esi), %ebx  # (*p)++
        iaddl 1, %ebx  # ++
        rmmovl %ebx, (%esi)  # 
```

## Exercice 4
```y86
        irmovl t, %esi
        mrmovl n, %ecx  # décompteur
bcl:    isubl 1, %ecx
        jl fin
        mrmovl (%esi), %ebx
        addl 1, %ebx
        rmmovl %ebx, (%esi)
        iaddl 4, %esi  # p++
        jmp bcl
fin:    halt
```

# TM 2

## Exercice 1

### Question 1
```y86
        .pos 0
init:   irmovl t, %esi
        mrmovl n, %ecx
        isubl 2, %ecx
bcl:    isubl 1, %ecx
        jl fin
        mrmovl (%esi), %eax
        iaddl 4, %esi
        mrmovl (%esi), %ebx
        addl %eax, %ebx
        iaddl 4, %esi
        rmmovl %ebx, (%esi)
        isubl 4, %esi
        jmp bcl
fin:    halt

        .pos 0x100
n :     .long 16
t:      .long 1
        .long 1


```