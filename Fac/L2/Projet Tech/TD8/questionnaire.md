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

`Partiellement : Il y a une erreur pour undo et redo, mais cela vient de notre code.`

**Question 08** - Est-ce que la bibliothèque fournie arrive à passer vos tests ?
Pouvez-vous ainsi detécter de nouveaux bugs ou fuites mémoire dans cette
bibliothèque ? Justifiez quelle fonction ou ligne de code est responsable.

`Partiellement : Tous les tests passent sauf undo et redo. Le problème reste le même.`

**Question 09** - A l'inverse, est-ce que les différents exécutables fournis
(`game_text` et tests) fonctionnent avec votre propre bibliothèque ? Justifiez
tout problème découvert, y compris dans votre propre projet.

`A FAIRE (potentiellement modif les questions précédentes pour la biblio.`

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

`???`

**Question 13** - Donnez un appréciation générale. Voyez-vous d'autres pistes
d'amélioration ?

`Le code est réellement bon dans son ensemble. Mais il faudrait corriger les problèmes de fuite de mémoire, potentiellement en essayant de ne pas utiliser de malloc pour les éléments des piles (en cours d'implémentation de notre coté).`

---
