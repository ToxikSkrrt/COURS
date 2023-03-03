package fr.ubx.poo.td2.view;

import fr.ubx.poo.td2.Position;
import fr.ubx.poo.td2.model.Vehicule;
import javafx.animation.PathTransition;
import javafx.scene.image.ImageView;
import javafx.scene.shape.LineTo;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.util.Duration;

abstract public class Sprite {
    private ImageView img;

    public Sprite(ImageView img) {
        this.img = img;
    }
    public void updateLocation(Position position) {
        getImg().setX(position.x() * ImageResource.size);
        getImg().setY(position.y() * ImageResource.size);
    }

    public ImageView getImg() {
        return img;
    }
}
