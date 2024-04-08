# COURS
```
texte --*Lexing*--> séquence de token --*Parsing*--> AST --*analyses*--> AST --*interprétation*--> Assembleur                                                                   
                                                                             --*decouper flow*--> Langage intermédiaire ou assembleur haut-niveau
```

**Texte :**
- .c
- .h
- etc

**Lexing :**
- automates finis
  - repérer tokens
  - éliminer commentaires / espaces
  - détecter erreurs lexicales
  
**Parsing :**
- automates shift-reduce algébriques
  - LR0 -> conflit : undef
  - SLR -> Follow
  - Annotations de priorités

**AST :**
- `Affect (x, Binop (+, 3, 4))`

**Analyses :**
- detecter erreurs
- simplifier exécution