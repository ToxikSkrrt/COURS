package fr.ubx.poo.td2.view;

import fr.ubx.poo.td2.model.Drone;
import javafx.scene.image.ImageView;

public class SpriteDrone extends SpriteVehicule {
    // private Drone drone;

    public SpriteDrone(Drone drone) {
        super(drone, new ImageView(ImageResource.imageDrone));
    }
}
