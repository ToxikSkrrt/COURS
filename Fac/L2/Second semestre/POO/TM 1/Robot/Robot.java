class Robot {
    Robot(Position position, double energie, double cout) {
        this.position = position;
        this.energie = energie;
        this.cout = cout
    }
    private Position position;
    private double energie;
    private double cout;

    // Retourne le rayon d'action du robot, c'est à dire la distance maximale que peut parcourir le robot compte tenu de son énergie disponible.
    double rayonAction() {
        return this.energie / this.cout;
    }

    // Détermine si le robot possède siffisamment d'énergie pour atteindre la position cible. La méthode retournera `true` si le test est positif, et `false` dans le cas contraire.
    boolean peutSeDeplacer(Position cible) {
        if (this.position.distance(cible) < this.rayonAction()) {
            return true;
        }
        return false;
    }

    // Affiche les informations du robot sur la console
    void afficher() {
        System.out.println("Robot @ " + this.position.afficher());
        System.out.println("Energie : " + this.energie);
        System.out.println("Cout : " + this.cout);
    }
}