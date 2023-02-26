package fr.ubx.poo.td2;

import fr.ubx.poo.td2.model.Drone;
import fr.ubx.poo.td2.model.Robot;
import fr.ubx.poo.td2.model.Vehicule;
import fr.ubx.poo.td2.view.*;
import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {

    @Override
    public void start(Stage stage)  {
        int width = 20;
        int height = 20;
        World world = new World(width, height, 0.3, 0.3);
        // Creation du robot et du drone
        Vehicule[] vehicules = new Vehicule[3];
        vehicules[0] = new Robot("Curiosity", new Position(4,4), 200, 2);
        vehicules[1] = new Robot("Opportunity", new Position(8,4), 200, 2);
        vehicules[2] = new Drone("Ingenuity", new Position(6,6), 300, 2);

        SpriteVehicule[] spritesVehicule = new SpriteVehicule[3];
        spritesVehicule[0] = new SpriteRobot((Robot) vehicules[0]);
        spritesVehicule[1] = new SpriteRobot((Robot) vehicules[1]);
        spritesVehicule[2] = new SpriteDrone((Drone) vehicules[2]);

        // Affiche la fenetre
        View view = new View(width, height);
        stage.setTitle("POO");
        stage.setScene(view.getPane().getScene());
        stage.show();
        view.getPane().setOnMouseClicked(e -> {
            Position target = view.getPosition(e);
            for (int i = 0; i < 3; i++) {
                if (vehicules[i].canMove(target) && !vehicules[i].getPosition().equals((target))) {
                    spritesVehicule[i].animateMove(target);
                }
            }
        });
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (world.get(new Position(i, j)) != World.EMPTY) {
                    view.getPane().getChildren().addAll(world.map[i][j].getImg());
                }
            }
        }
        view.getPane().getChildren().addAll(spritesVehicule[0].getImg());
        view.getPane().getChildren().addAll(spritesVehicule[1].getImg());
        view.getPane().getChildren().addAll(spritesVehicule[2].getImg());

    }

    public static void main(String[] args) { launch(); }
}
