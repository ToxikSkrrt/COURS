package fr.ubx.poo.td2.view;

import fr.ubx.poo.td2.Position;
import javafx.scene.image.ImageView;

public class SpriteDust extends SpriteDecor {
    public SpriteDust(Position position) {
        super(new ImageView(ImageResource.imageDust), position);
    }
}
