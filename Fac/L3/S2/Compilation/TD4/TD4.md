# TD 4

## Exercice 1

1. 
L1 n'est pas un langage régulier, or Ocamllex ne traite que des langages réguliers.

2. 
Représente le système de parenthèse ouvrante / fermante : a^n b^n , avec a = ( et b =)

3. 
N = { main, S }

T = { A, B, EOF }

init : main

main -> | s EOF
        | EOF

s -> | A s B
     | A B