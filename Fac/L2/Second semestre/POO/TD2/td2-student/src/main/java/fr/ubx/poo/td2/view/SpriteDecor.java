package fr.ubx.poo.td2.view;

import fr.ubx.poo.td2.Position;
import javafx.scene.image.ImageView;

public class SpriteDecor extends Sprite {
    private Position position;

    public SpriteDecor(ImageView img, Position position) {
        super(img);
        this.position = position;
    }
}
