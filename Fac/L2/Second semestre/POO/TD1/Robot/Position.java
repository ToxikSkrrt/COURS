class Position {
    Position(double x, double y) {
        this.x = x;
        this.y = y;
    }

    double x;
    double y;

    void afficher() {
        System.out.println("(" + this.x + " x " + this.y + ")");
    }
    
    // Deplace une position par rapport à son origine
    void deplacement(double dx, double dy) {
        this.x += dx;
        this.y += dy;
    }

    // meme deplacement en x et en y
    void deplacement(double delta) {
        this.x += delta;
        this.y += delta;
    }

    // Calcul la distance euclidienne entre deux positions
    double distance(Position cible) {
        double d = Math.sqrt(Math.pow(cible.x - this.x, 2) + Math.pow(cible.y - this.y, 2));
        return d;
    }
}