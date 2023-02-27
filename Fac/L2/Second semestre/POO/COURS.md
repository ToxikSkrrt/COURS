# COURS

www.reveillere.fr  

Installer IntelliJ  

- test Moodle 10%
- TP noté 30%
- QCM revisité 30%
- Projet duo 30%

En Java, pas de suppression d'objets -> garbage collector  

## Classe en Java
- fichier texte
- nom fichier = nom de la classe
- nom de classe commence par une maj
- (type des données -> propriétés)
- (type de traitements -> méthodes)

### Propriétés
- nom
- type (basic/natif, reference) (type minscule = type de donnée | type maj = type classe)
    - boolean
    - char
    - int
    - double
- traitements
    - type_retour nom(params) {corps}

## Exemple : 

### Rectangle.java

```java
class Rectangle {
    double largeur;
    double hauteur;

    double surface() {
        return largeur * hauteur;
    }
}
```

### Main.java

```java
... main (...) {
   Rectangle r1 = new Rectangle();
   r1.largeur = 2;
   r1.hauteur = 3;

   System.out.println("surface = " + r1.surface()); 
}
```

Toutes les variables sont 0-initialisées  

## Constructeur

```java
Rectangle(double largeur, double hauteur) {
    this.largeur = largeur;
    this.hauteur = hauteur;
}
```

Nombre d'instance = nombre de fois où "new" est présent

### For sur un tableau de rectangles :
```java
for (Rectangle r : rectangles) {
    ...
}
```

# 1. Encapsulation

Protéger ses données pour garantir l'intégrité

## Propriétés privées

```java
private double largeur;
private double hauteur;
```

## Accesseurs

### Setters

```java
void setLargeur(double largeur) {
    this.largeur = largeur;
}
```

### Getters

```java
double getLargeur() {
    return largeur;
}
```

# 2. Responsabilité

- données nécessaires (références vers d'autres objets => délégation)
- =/= faire les choses seul

# 3. Cohésion

- données / traitements = tout cohérent

# 4. Couplage

- dépendance entre objets

# Héritage

```java
class Figure {
    int x;
    int y;
    void draw();
    ...
}

class Rectangle extends Figure {
    double width;
    double height;

    void draw(); // REDEFINITION
    ...
}

class Circle extends Figure{
    double radius;
    ...
}
```

# Polymorphisme

- late binding (= ligature dynamique)

```java
Figure[] figs = new Figure[2];
figs[0] = new Rectangle(2, 3);
figs[1] = new Circle(4);

for (Figure fig: figures) {
    fig.draw();
}
```

# Classes abstraites   
```java
abstract class Figure {
    abstract void draw();
}
```

Si une classe hérite d'une méthode abstraite, la classe devient abstraite même sans 'abstract'. Pour éviter cela il faut redéfinir la méthode.

Imposer un cadre -> Forcer la definition de classes filles avec une classe mere abstraite, etc... (FACTORISATION)

# Interface

Une interface ne comporte que des méthodes.  
On définit que des prototypes de méthode.  
Les interfaces peuvent être héritées et également hériter d'autres interfaces.  
Surcharge = changement de signature (paramètres...) sans modifier le type de retour.

```java
interface Foo {
    void foo();
    void foo(int i);
    boolean toto();
}

class Triangle extends Figure implements Foo {
    ...
}

class Fleur extends Decor implements Foo, Bar {
    ...
}
```

Depuis Java 8, interfaces avec méthodes par défaut -> si la méthode n'est pas définie dans la classe, alors le code de la méthode par défaut sera exécuté.

```java
interface Foo {
    void foo();
    default boolean toto() {
        return true;
    }
}
```

```java
interface Bar {
    void bar();
    default boolean toto() {
        return false;
    }
}
```

Vu que Foo et Bar contiennent une définition par défaut de toto(), il faut obligatoirement redéfinir toto() dans la classe.

```java
class Decor {
    ...

    boolean toto() {
        if (...) {
            return Foo.super.toto();
        } else {
            return Bar.super.toto();
        }
    }
}
```

# Exceptions

