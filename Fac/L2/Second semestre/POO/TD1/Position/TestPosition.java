class Main {
        public static void main(String[] args) {
                Position pos = new Position(1, 2);

                System.out.println(pos.x + pos.y);
                pos.afficher();
                pos.deplacement(3, 3);
                pos.afficher();
                pos.deplacement(6);
                pos.afficher();
                Position pos2 = new Position(20, 20);
                
                System.out.println(pos.distance(pos2));
	}
}