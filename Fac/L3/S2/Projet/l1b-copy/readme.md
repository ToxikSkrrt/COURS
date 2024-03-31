# Projet de Développement Logiciel

## Utilisation et deploiement du projet
1. Téléchargez et décompressez le projet.
2. À partir de la racine, exécutez : `mvn clean install`
3. Ensuite, lancez le serveur : `mvn --projects backend spring-boot:run`
Vous pourrez y accéder via votre navigateur préféré à l'adresse :
<http://localhost:8765/>


4. Si vous préférez lancer le backend et le frontend indépendamment sans utiliser __mvn__ à la racine, vous pouvez les retrouver aux adresses suivantes :
- __Backend__ : <http://localhost:8765/>, (grâce à _Tomcat_)
- __Frontend__ : <http://localhost:4000/>, (grâce à _Vite_)
Pour cela, depuis la racine du dossier backend, exécutez la commande : `mvn spring-boot:run`
Ensuite, ouvrez, à l'aide de VSCode et de son extension Vite, la racine du dossier frontend.

## 

### TP1 Backend
Nous avons créé une application Spring Boot et déployé cette application pour gérer des photos. De plus, nous avons écrit des tests unitaires __JUnit__ pour vérifier le déploiement tout au long de son utilisation.
##### Remarques
Cette section a présenté des difficultés, notamment dans l'écriture des tests unitaires en raison de la documentation volumineuse et de l'ampleur de JUnit. Les tests 7 et 8 restent à implémenter.
__Note importante__ : Une modification a été apportée lors de l'initialisation du serveur. Désormais, le serveur charge toutes les images f1.png, f2.png, ..., f8.png. Ce n'est plus l'image test.png qui est chargée.


### TP2 Frontend
Dans cette partie, nous avons codé le client web avec plusieurs fonctionnalités :
1. Un _menu déroulant_ listant les photos du serveur, permettant de les afficher individuellement.
2. Une _page galerie_ affichant toutes les photos dans un format carré et une disposition de 3 par ligne.
3. Une _zone d'upload_ (POST) permettant d'ajouter des images sur le serveur sans passer par l'invite de commande (exemple curl), tout en restant sur l'interface web.
##### Remarques
L'édition du frontend a pu poser quelques contretemps. La liberté d'usage a parfois été déroutante, mais une fois compris, l'utilisation de Vue et de Vite permet une exécution beaucoup plus rapide. La seule difficulté apparue concerne l'utilisation d'axios pour poster les images, cette partie reste à implémenter.

