package fr.ubx.poo.td2.model;

import fr.ubx.poo.td2.Position;

abstract public class Vehicule {
    private final double cost;
    private Position position;
    private double energy;
    private final String name;

    public Vehicule(String name, Position position, double energy, double cost) {
        this.name = name;
        this.position = new Position(position);
        this.energy = energy;
        this.cost = cost;
    }

    public Position getPosition() {
        return new Position(this.position);
    }

    private int range() { return (int) (this.energy / this.cost); }

    abstract public int distance(Position target);

    public boolean canMove(Position target) {
        return this.distance(target) <= this.range();
    }

    public void move(Position target) {
        if (this.canMove(target)) {
            this.energy -= this.cost * distance(target);
            this.position = target;
            System.out.println("Move completed: " + this + " " + this.name + " : energy=" + this.energy);
        }
    }

    abstract public Position[] getPathTo(Position target);
}
