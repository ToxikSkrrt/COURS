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