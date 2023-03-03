package fr.ubx.poo.td2;

public class World {
    public static final int EMPTY = 0;
    public static final int ROCK  = 1;
    public static final int DUST  = 2;

    public final int map[][];

    public World(int width, int height, double percentageRock, double percentageDust) {
        this.map = new int[width][height];
        if (percentageRock + percentageDust < 1) {
            int nbRocks = (int) (width * height * percentageRock);
            int nbDust = (int) (width * height * percentageDust);
            while (nbRocks > 0) {
                Position position = Position.random(width, height);
                if (this.get(position) == EMPTY) {
                    this.set(position, ROCK);
                    nbRocks--;
                }
            }
            while (nbDust > 0) {
                Position position = Position.random(width, height);
                if (this.get(position) == EMPTY) {
                    this.set(position, DUST);
                    nbDust--;
                }
            }
        }
    }

    public int get(Position position) {
        return map[position.x()][position.y()];
    }
    public void set(Position position, int kind) {
        this.map[position.x()][position.y()] = kind;
    }
}
