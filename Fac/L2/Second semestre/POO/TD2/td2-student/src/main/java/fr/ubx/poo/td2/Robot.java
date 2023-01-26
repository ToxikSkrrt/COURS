package fr.ubx.poo.td2;

public class Robot {
    private final double cost;
    private Position position;
    private double energy;


    public Robot(Position position, double energy, double cost) {
        this.position = new Position(position.getX(), position.getY());
        this.energy = energy;
        this.cost = cost;
    }

    public Position getPosition() {
        return new Position(this.position.getX(), this.position.getY());
    }

    // TODO
     private int range() { return (int) (this.energy / this.cost); }

    // TODO
    public int distance(Position target) {
        return (int) Math.sqrt(Math.pow(target.getX() - this.getPosition().getX(), 2) + Math.pow(target.getY() - this.getPosition().getY(), 2));
    }

    // TODO
    public boolean canMove(Position target) {
        if (this.distance(target) < this.range()) {
            return true;
        }
        return false;
    }

    // TODO
    public void move(Position target) {
        if (this.canMove(target)) {
            this.position.translate(target.getX() - this.position.getX(), target.getY() - this.position.getY());
            // this.energy = this.cost * distance(target);
        }
    }

    // TODO
    public Position[] getPathTo(Position target) {
        Position pos[] = new Position[6];
        pos[0] = new Position(target.getX() / 3, this.getPosition().getY());
        pos[1] = new Position(target.getX() / 3, target.getY() / 3);
        pos[2] = new Position(target.getX() / 3 * 2, target.getY() / 3);
        pos[3] = new Position(target.getX() / 3 * 2, target.getY() / 3 * 2);
        pos[4] = new Position(target.getX(), target.getY() / 3 * 2);
        pos[5] = new Position(target.getX(), target.getY());
        return pos;
    }

}
