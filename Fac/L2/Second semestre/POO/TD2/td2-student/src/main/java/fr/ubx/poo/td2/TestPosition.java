package fr.ubx.poo.td2;

public class TestPosition {
    public static void main(String[] args) {
        Position pos1 = new Position(1, 2);
        Position pos2 = new Position(1, 2);

        System.out.println("pos1 == pos2 ?\n" + pos1.equals(pos2));
    }
}
