package fr.ubx.poo.td2.model;

import fr.ubx.poo.td2.Position;

public class Drone extends Vehicule {
    public Drone(String name, Position position, double energy, double cost) {
        super(name, position, energy, cost);
    }

    // TODO
    @Override
    public int distance(Position target) {
        return (int) Math.sqrt(Math.pow(target.x() - this.getPosition().x(), 2) + Math.pow(target.y() - this.getPosition().y(), 2));
    }

    // TODO
    @Override
    public Position[] getPathTo(Position target) {
        Position pos[] = new Position[1];
        pos[0] = new Position(target);
        return pos;
    }

    @Override
    public String toString() {
        return "Drone";
    }
}
