# PDL - l1b


## Pour lancer le projet
Dans le terminal, à la racine du projet
```
mvn clean install
mvn --projects backend spring-boot:run
```
Dans un navigateur (de préférence Chrome, certaines fonctionnalités ne marchent pas correctement sur Firefox), entrer l'url [suivante](localhost:8765) (localhost:8765).

## Configuration accès à la base de données:
Définir les variables d'environnement DATABASE_NAME et DATABASE_PASSWORD avec vos username et password (dans un terminal ou dans le fichier .bashrc)
```
export DATABASE_NAME=username
export DATABASE_PASSWORD=password
```

## Besoins

### Besoin 1 : Initialiser un ensemble d’images présentes sur le serveur
Ok en partie. Les images présentes dans le dossier sont bien initialisées mais elles ne sont pas indexées dans la database

### Besoin 2 : Gérer les images présentes sur le serveur
ok

### Besoin 3 : Indexer une image
En partie: le serveur indexe bien les images qui sont ajoutées.
En revanche, l'indexation dans la base de données n'a pas lieu pour les images déjà présentes.

### Besoin 4 : Rechercher des images similaires à une image donnée
Non implémenté

### Besoin 5 : Transférer la liste des images existantes
ok

### Besoin 6 : Ajouter une image
ok

### Besoin 7 : Récupérer une image
ok

### Besoin 8 : Supprimer une image
ok sur Chrome (pas sur Firefox)

### Besoin 9 : Transférer la liste des images les plus similaires à une image donnée
non implémenté

### Besoin 10 : Parcourir les images disponibles sur le serveur
ok

### Besoin 11 : Sélectionner une image et afficher les images similaires
non implémenté

### Besoin 12 : Enregistrer une image sur disque
ok. Fonctionne correctement sur Chrome.

### Besoin 13 : Ajouter une image aux images disponibles sur le serveur
ok. Et les données liées à la nouvelle image sont bien ajoutées dans la base de données.

### Besoin 14 : Supprimer une image
ok. Fonctionne correctement dans Chrome (pas dans Firefox)

### Besoin 15 : Intégration continue


### Besoin 16 : Compatibilité du serveur
Compatibilité sur Debian Bookworm, Ubuntu 22.04

### Besoin 17 : Compatibilité du client
Compatible sur Chrome
Ne fonctionne pas correctement sur Firefox

### Besoin 18 : Documentation d’installation et de test
ok