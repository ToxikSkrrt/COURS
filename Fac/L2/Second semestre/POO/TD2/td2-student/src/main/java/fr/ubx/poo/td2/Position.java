package fr.ubx.poo.td2;

import java.util.Random;

public record Position(int x, int y) {
    /*
     -- NOT REQUIRED --
     public Position(int x, int y) {
         this.x = x;
         this.y = y;
     }
    */

    public Position(Position position) {
        this(position.x, position.y);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Position position)) return false;
        return x == position.x && y == position.y;
    }
    static Position random(int width, int height) {
        Random rand = new Random();
        int randWidth = rand.nextInt(width);
        int randHeight = rand.nextInt(height);
        return new Position(randWidth, randHeight);
    }
}
