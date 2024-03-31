## Note 
Tout ce qui touche au descripteur n'est pas implémenté 
La possiblité de chercher des images similaires n'est pas implémenté

## Important
Pour lancer correctement le serveur il faut faire attention de bien avoir le nom d'une database du cremi ainsi que son mot de passe défini en variable d'environnement
au cas où ça ne soit pas le cas pour le faire il faut faire les commande suivante:
export DATABASE_NAME={id de la personne}
export DATABASE_PASSWORD={mot de passe de la database de la personne}

# Systeme d'exploitation testé 
- Debian
- Manjaro Linux

# Navigateur testé
- brave 1.63.174
- Firefox 124.0

Avant toute chose, j'ai fais l'évaluation du projet en SSH.

Le tout premier `mvn clean install` n'a pas fonctionné, mais ensuite en relançant la commande une seconde fois, le serveur s'est bien lancé. Ensuite pour l'exécution aucun problème, mais ça ne marchait pas avec le port défini dans le fichier `application.properties`. Mais en changeant de port, j'ai bien eu accès au site donc aucun problème à ce niveau.


Besoin 5 : le JSON des images (/images) est bien fonctionnel, même après ajout / suppression. Mais peut-être rajouter un bouton dans le menu pour accéder à cette page.


