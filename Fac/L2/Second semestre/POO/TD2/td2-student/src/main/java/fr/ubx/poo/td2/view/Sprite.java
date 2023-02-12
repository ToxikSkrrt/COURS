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
    private Vehicule vehicule;
    private ImageView img;

    public Sprite(Vehicule vehicule, ImageView img) {
        this.vehicule = vehicule;
        this.img = img;
        updateLocation(vehicule.getPosition());
    }

    private void updateLocation(Position position) {
        img.setX(position.x() * ImageResource.size);
        img.setY(position.y() * ImageResource.size);
    }

    public ImageView getImg() {
        return img;
    }

    public void animateMove(Position target) {
        // Make the path movement
        Position[] positionPath = vehicule.getPathTo(target);

        if (positionPath != null) {
            Path path = new Path();

            path.getElements().add(new MoveTo(vehicule.getPosition().x() * ImageResource.size + ImageResource.size / 2,
                    vehicule.getPosition().y() * ImageResource.size + ImageResource.size / 2));
            for (Position pos : positionPath) {
                path.getElements().add(new LineTo(pos.x() * ImageResource.size + ImageResource.size / 2, pos.y() * ImageResource.size + ImageResource.size / 2));
            }

            PathTransition ptr = new PathTransition();
            ptr.setDuration(Duration.millis(300 * vehicule.distance(target)));
            ptr.setPath(path);
            ptr.setNode(getImg());
            ptr.play();

            ptr.setOnFinished(e -> {
                vehicule.move(target);
            });
        } else {
            // Direct move
            vehicule.move(target);
            updateLocation(target);
        }
    }
}
