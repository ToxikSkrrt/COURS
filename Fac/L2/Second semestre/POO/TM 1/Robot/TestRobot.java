class Main {
    public static void main(String[] args) {
            Position pos = new Position(1, 2);

            Robot rob = new Robot(pos, 100, 10);
            System.out.println("Rayon d'action : " + rob.rayonAction());
            System.out.println()
    }
}