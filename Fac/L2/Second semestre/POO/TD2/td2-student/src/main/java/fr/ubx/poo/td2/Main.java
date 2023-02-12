package fr.ubx.poo.td2;

import fr.ubx.poo.td2.model.Drone;
import fr.ubx.poo.td2.model.Robot;
import fr.ubx.poo.td2.model.Vehicule;
import fr.ubx.poo.td2.view.Sprite;
import fr.ubx.poo.td2.view.SpriteDrone;
import fr.ubx.poo.td2.view.SpriteRobot;
import fr.ubx.poo.td2.view.View;
import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage stage)  {

        // Creation du robot et du drone
        Vehicule[] vehicules = new Vehicule[3];
        vehicules[0] = new Robot("Curiosity", new Position(4,4), 200, 2);
        vehicules[1] = new Robot("Opportunity", new Position(8,4), 200, 2);
        vehicules[2] = new Drone("Ingenuity", new Position(6,6), 300, 2);

        Sprite[] sprites = new Sprite[3];
        sprites[0] = new SpriteRobot((Robot) vehicules[0]);
        sprites[1] = new SpriteRobot((Robot) vehicules[1]);
        sprites[2] = new SpriteDrone((Drone) vehicules[2]);

        // Affiche la fenetre
        View view = new View(20, 20);
        stage.setTitle("POO");
        stage.setScene(view.getPane().getScene());
        stage.show();
        view.getPane().setOnMouseClicked(e -> {
            Position target = view.getPosition(e);
            for (int i = 0; i < 3; i++) {
                if (vehicules[i].canMove(target) && !vehicules[i].getPosition().equals((target))) {
                    sprites[i].animateMove(target);
                }
            }
        });

        view.getPane().getChildren().addAll(sprites[0].getImg());
        view.getPane().getChildren().addAll(sprites[1].getImg());
        view.getPane().getChildren().addAll(sprites[2].getImg());

    }

    public static void main(String[] args) { launch(); }
}
