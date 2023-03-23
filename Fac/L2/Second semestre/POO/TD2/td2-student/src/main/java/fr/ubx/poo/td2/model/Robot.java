package fr.ubx.poo.td2.model;

import fr.ubx.poo.td2.Position;
import fr.ubx.poo.td2.World;

public class Robot extends Vehicule {

    public Robot(String name, Position position, double energy, double cost) {
        super(name, position, energy, cost);
    }

    @Override
    public int distance(Position target) {
        return Math.abs(target.x() - this.getPosition().x()) + Math.abs(target.y() - this.getPosition().y());
    }

    @Override
    public Position[] getPathTo(Position target) {
        int deltaX = target.x() - this.getPosition().x();
        int deltaY = target.y() - this.getPosition().y();
        Position pos[] = new Position[6];
        pos[0] = new Position(this.getPosition().x() + deltaX / 3, this.getPosition().y());
        /* A FAIRE (TD 4/5)
        if (World.map[pos[0].x()][pos[0].y()] == World.ROCK) {
            return pos;
        }
        */
        pos[1] = new Position(this.getPosition().x() + deltaX / 3, this.getPosition().y() + deltaY / 3);
        pos[2] = new Position(this.getPosition().x() + (deltaX / 3) * 2, this.getPosition().y() + deltaY / 3);
        pos[3] = new Position(this.getPosition().x() + (deltaX / 3) * 2, this.getPosition().y() + (deltaY / 3) * 2);
        pos[4] = new Position(target.x(), this.getPosition().y() + (deltaY / 3) * 2);
        pos[5] = new Position(target.x(), target.y());
        return pos;
    }

    @Override
    public String toString() {
        return "Robot";
    }
}
