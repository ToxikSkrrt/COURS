class Rectangle {
    Rectangle(double largeur, double hauteur) {
        this.largeur = largeur;
        this.hauteur = hauteur;
    }
    
    double surface() {
        return this.largeur * this.hauteur;
    }
}