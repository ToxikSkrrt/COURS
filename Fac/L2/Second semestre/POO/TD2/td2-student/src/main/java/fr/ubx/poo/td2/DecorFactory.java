package fr.ubx.poo.td2;

import fr.ubx.poo.td2.view.SpriteDecor;
import fr.ubx.poo.td2.view.SpriteDust;
import fr.ubx.poo.td2.view.SpriteRock;

public class DecorFactory {
    public static SpriteDecor create(Position position, int kind) {
        switch (kind) {
            case World.DUST:
                return new SpriteDust(position);
            case World.ROCK:
                return new SpriteRock(position);
            default:
                return null;
        }
    }
}
