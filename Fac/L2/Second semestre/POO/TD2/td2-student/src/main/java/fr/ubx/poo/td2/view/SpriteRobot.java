package fr.ubx.poo.td2.view;

import fr.ubx.poo.td2.model.Robot;
import javafx.scene.image.ImageView;

public class SpriteRobot extends SpriteVehicule {
    // private Robot robot;

    public SpriteRobot(Robot robot) {
        super(robot, new ImageView(ImageResource.imageRobot));
    }
}
