```y86
        .pos 0
init:   irmovl stack,%esp
        mrmovl v, %eax
        pushl %eax      # v dans la pile
        mrmovl n, %eax  
        pushl %eax      # n dans la pile
        irmovl t, %eax
        pushl %eax      # t dans la pile
        call rech       # appel de la fonction
        iaddl 12, %esp  # remet le pointeur au début de la pile
        halt

rech:   pushl %ebx
        mrmovl 8(%esp), %edx    # t
        mrmovl 12(%esp), %ecx   # n
        mrmovl 16(%esp), %ebx   # v
bcl:    isubl 1, %ecx           # on décremente n de 1 (compteur)
        jl fin                  # si égal à -1, alors on va à la fin de la fonction (= si le tableau a été entièrement                     # parcouru
        mrmovl (%edx), %eax     # on copie la valeur pointée sur %edx vers %eax
        subl %ebx, %eax         # on soustrait la valeur recherchée à la valeur dans %eax (si égal à 0 alors la valeur                     # recherchée est présente)
        je vrai                 # jump vers vrai si la valeur si la valeur recherchée est présente (test si ça vaut 0)
        xorl %eax, %eax         # met %eax à 0 si la valeur n'était pas celle recherchée (= false)
        iaddl 4, %edx           # déplace le pointeur d'une case accéder à la valeur suivante du tableau
        jmp bcl                 # on revient au début de la boucle
vrai:   irmovl 1, %eax          # on met %eax à 1 car la valeur recherchée a été trouvée (= true)
fin:    popl %ebx
        ret                     # return final

        .pos 0x200
t:      .long 3
        .long 8
        .long 2
        .long 29
        .long 31
        .long 10
n:      .long 6
v:      .long 31
    
        .pos 0x250
stack:

```
