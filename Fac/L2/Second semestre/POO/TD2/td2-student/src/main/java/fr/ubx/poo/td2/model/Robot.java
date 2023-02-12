package fr.ubx.poo.td2.mode1;

import fr.ubx.poo.td2.Position;

public class Robot extends Vehicule {

    public Robot(String name, Position position, double energy, double cost) {
        super(name, position, energy, cost);
    }

    @Override
    public int distance(Position target) {
        return (int) Math.abs(target.getX() - this.getPosition().getX()) + Math.abs(target.getY() - this.getPosition().getY());
    }

    @Override
    public Position[] getPathTo(Position target) {
        int deltaX = target.getX() - this.getPosition().getX();
        int deltaY = target.getY() - this.getPosition().getY();;
        Position pos[] = new Position[6];
        pos[0] = new Position(this.getPosition().getX() + deltaX / 3, this.getPosition().getY());
        pos[1] = new Position(this.getPosition().getX() + deltaX / 3, this.getPosition().getY() + deltaY / 3);
        pos[2] = new Position(this.getPosition().getX() + (deltaX / 3) * 2, this.getPosition().getY() + deltaY / 3);
        pos[3] = new Position(this.getPosition().getX() + (deltaX / 3) * 2, this.getPosition().getY() + (deltaY / 3) * 2);
        pos[4] = new Position(target.getX(), this.getPosition().getY() + (deltaY / 3) * 2);
        pos[5] = new Position(target.getX(), target.getY());
        return pos;
    }

    @Override
    public String toString() {
        return "Robot";
    }
}
