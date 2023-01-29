# Évaluation Croisée du Projet

**Projet Évalué** : `Team 07B`

## Consignes

Pour chaque question, on attend une réponse courte (oui/non/partiellement) qui
doit être suivie d'une argumentation précise et concise. L’argumentation est
essentielle et doit remplir 2 objectifs : justifier votre réponse courte et
proposer des pistes d’améliorations du code.

Par exemple :

* Question - Le code est-il correctement indenté ?
* Réponse - Partiellement. La fonction truc bidule() du fichier n’est pas
  correctement indentée. Le fichier truc.c n’est pas indenté de la même manière
  que les autres fichiers.

## Questionnaire à remplir

**Question 01** - L’archive du dépôt Git est-elle propre ? (Présence d'un
fichier `README.md` bien écrit, présence des fichiers `.clang-format`,
`.gitignore`, ... Absence de fichiers superflux, temporaires, ou d'exécutables,
...)

`Partiellement : README.md non modifié, fichier HTML en trop, .gitignore vide.`

**Question 02** - La compilation se fait-elle correctement ? (Les exécutables et
la bibliothèque sont générés sans erreurs ni warnings.)

`Oui : Aucune erreur de compilation.`

**Question 03** - Est-ce que le programme `game_text` s'exécute sans erreurs, ni
bugs ? Arrivez-vous à gagner le jeu par défaut ?

`Partiellement : game_text s'éxecute sans erreurs, cependant le jeu créé est un jeu vide, il n'y a donc aucun 'immutable'. La commande 'h' n'affiche pas une aide réellement utile. De plus, le jeu ne détecte pas les coups impossibles. Exemple :`
```
   012345
   ------
0 |wwwwww|
1 |      |
2 |      |
3 |      |
4 |      |
5 |      |
6 |      |
7 |      |
8 |      |
9 |      |
   ------
``` 

**Question 04** - Est-ce que les tests fournis s'éxécutent sans fautes ?
Pouvez-vous ainsi identifier des bugs non corrigés ? Justifiez quelle fonction
ou ligne de code est responsable.

`Partiellement : Un test ne fonctionne pas : test_ninteyineza_game_restart. Les lignes 201 et 202 sont en partie responsables, il y a un game_delete avant le game_copy :`
```c
game_delete(g2);
game g3 = game_copy(g2);
```

**Question 05** - Quelle est la couverture du code ? Y a-t-il selon vous
suffisamment de tests, y compris pour les extensions du jeu (v2) ?

`Oui : La couverture du code est de 85.06%. Le nombre de tests est cependant suffisant (séparation des tests pour les extensions unique et wrapping notamment).`

**Question 06** - Est-ce que les tests fournis s'exécutent sans fuites mémoire ?
Justifiez quelle fonction ou ligne de code est responsable.

`Partiellement : Plusieurs tests comportent des fuites mémoires : test_ecallet_has_error_unique, test_ecallet_undo, test_pdinghin_game_new, test_pdinghin_game_new_empty_ext, test_pdinghin_game_redo et test_ninteyineza_game_restart.`

**Question 07** - La bibliothèque fournie peut-elle remplacer votre propre
bibliothèque sans générer de problèmes ? Vérifiez avec `game_text`.

`Oui : Cela fonctionne parfaitement avec game_text. (mais seulement en désactivant la génération des tests, explication à la question suivante).`

**Question 08** - Est-ce que la bibliothèque fournie arrive à passer vos tests ?
Pouvez-vous ainsi detécter de nouveaux bugs ou fuites mémoire dans cette
bibliothèque ? Justifiez quelle fonction ou ligne de code est responsable.

`Partiellement : il y a des erreurs de compatibilité pour un fichier :`
```
/mnt/c/Users/thoma/Documents/COURS/Fac/L2/Projet Tech/TD8/Copie takuzu/game_test_tcohen.c: In function ‘test_game_new_ext’:
/mnt/c/Users/thoma/Documents/COURS/Fac/L2/Projet Tech/TD8/Copie takuzu/game_test_tcohen.c:244:12: error: ‘struct game_s’ has no member named ‘rows’; did you mean ‘nb_rows’?
  244 |     if (g->rows != row || g->columns != col) test = false;
      |            ^~~~
      |            nb_rows
/mnt/c/Users/thoma/Documents/COURS/Fac/L2/Projet Tech/TD8/Copie takuzu/game_test_tcohen.c:244:28: error: ‘struct game_s’ has no member named ‘columns’
  244 |     if (g->rows != row || g->columns != col) test = false;
      |                            ^~
make[2]: *** [CMakeFiles/game_test_tcohen.dir/build.make:63: CMakeFiles/game_test_tcohen.dir/game_test_tcohen.c.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:166: CMakeFiles/game_test_tcohen.dir/all] Error 2
make: *** [Makefile:95: all] Error 2
```
`Cependant pour les deux autres fichiers, tous les tests passent. Deux tests contiennent des fuites mémoires : test_thmoreau_game_undo et test_thmoreau_game_redo.`

**Question 09** - A l'inverse, est-ce que les différents exécutables fournis
(`game_text` et tests) fonctionnent avec votre propre bibliothèque ? Justifiez
tout problème découvert, y compris dans votre propre projet.

`Non : game_text ne se génère pas à cause d'erreurs de compatibilité :`
```
Scanning dependencies of target game_text
[ 92%] Building C object CMakeFiles/game_text.dir/game_text.c.o
/mnt/c/Users/thoma/Documents/COURS/Fac/L2/Projet Tech/TD8/Copie 07B/game_text.c: In function ‘main’:
/mnt/c/Users/thoma/Documents/COURS/Fac/L2/Projet Tech/TD8/Copie 07B/game_text.c:39:31: error: ‘struct game_s’ has no member named ‘q_undo’; did you mean ‘undo’?
   39 |         if (queue_is_empty(g->q_undo)) /*verif juste pour afficher le texte*/ {
      |                               ^~~~~~
      |                               undo
/mnt/c/Users/thoma/Documents/COURS/Fac/L2/Projet Tech/TD8/Copie 07B/game_text.c:47:31: error: ‘struct game_s’ has no member named ‘q_redo’; did you mean ‘redo’?
   47 |         if (queue_is_empty(g->q_redo)) /*verif juste pour afficher le texte*/ {
      |                               ^~~~~~
      |                               redo
/mnt/c/Users/thoma/Documents/COURS/Fac/L2/Projet Tech/TD8/Copie 07B/game_text.c:85:31: error: ‘struct game_s’ has no member named ‘q_redo’; did you mean ‘redo’?
   85 |           queue_clear_full(g->q_redo, free);
      |                               ^~~~~~
      |                               redo
make[2]: *** [CMakeFiles/game_text.dir/build.make:63: CMakeFiles/game_text.dir/game_text.c.o] Error 1
make[1]: *** [CMakeFiles/Makefile2:976: CMakeFiles/game_text.dir/all] Error 2
make: *** [Makefile:95: all] Error 2
```
`Les tests se génèrent mais comportent beaucoup d'erreurs :`
```
49% tests passed, 20 tests failed out of 39

Total Test time (real) =   3.80 sec

The following tests FAILED:
          3 - test_ecallet_get_next_square (SEGFAULT)
          4 - test_ecallet_get_next_square_wrapping (SEGFAULT)
          6 - test_ecallet_get_next_number (SEGFAULT)
          7 - test_ecallet_get_next_number_wrapping (SEGFAULT)
         10 - test_ecallet_has_error (SEGFAULT)
         11 - test_ecallet_has_error_wrapping (SEGFAULT)
         12 - test_ecallet_has_error_unique (SEGFAULT)
         13 - test_ecallet_undo (SEGFAULT)
         14 - test_ecallet_game_new_ext_moodle (SEGFAULT)
         15 - test_ecallet_is_over_unique (SEGFAULT)
         18 - test_pdinghin_game_delete (SEGFAULT)
         20 - test_pdinghin_game_copy (SEGFAULT)
         24 - test_pdinghin_game_new_ext (SEGFAULT)
         25 - test_pdinghin_game_new_empty_ext (SEGFAULT)
         26 - test_pdinghin_game_is_wrapping (SEGFAULT)
         27 - test_pdinghin_game_is_unique (SEGFAULT)
         28 - test_pdinghin_game_nb_rows (SEGFAULT)
         29 - test_pdinghin_game_nb_cols (SEGFAULT)
         30 - test_pdinghin_game_redo (SEGFAULT)
         37 - test_ninteyineza_game_restart (Failed)
Errors while running CTest
make: *** [Makefile:73: test] Error 8
```

**Question 10** - Est-ce que le code est propre et facilement lisible ?
(Indentation cohérente, nommage cohérent des variables et des fonctions, pas de
constantes magiques, fonctions de longueur raisonnable, pas de code mort ou de
duplication inutile, ...)

`Partiellement : le fichier game_ext.c a été modifié après avoir utilisé la commande 'clang-format-11 -i *.c *.h'. Sinon le code est parfaitement clair.`

**Question 11** - Le code est-il suffisament commenté ?

`Oui. Les parties pouvant être complexes à comprendre au départ sont bien commentées.`

**Question 12** - Est-ce que le code est complet et fonctionnel ? Dire si la V1
est correctement implémentée et lister les extensions de la V2 qui sont
correctement implémentées.

`Oui : Les fonctions de la V1 sont correctement implémentées, de même pour les fonctions de la V2 comme undo et redo ou les extensions unique et wrapping. `

**Question 13** - Donnez un appréciation générale. Voyez-vous d'autres pistes
d'amélioration ?

`Le code est réellement bon dans son ensemble. Mais il faudrait corriger les problèmes de fuite de mémoire, potentiellement en essayant de ne pas utiliser de malloc pour les éléments des piles (en cours d'implémentation de notre coté).`

---
