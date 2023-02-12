package fr.ubx.poo.td2;

import fr.ubx.poo.td2.view.ImageResource;
import fr.ubx.poo.td2.view.Sprite;
import javafx.scene.image.ImageView;

public class SpriteRobot extends Sprite {
    private Robot robot;

    public SpriteRobot(Robot robot) {
        super(robot, new ImageView(ImageResource.imageRobot));
    }
}
