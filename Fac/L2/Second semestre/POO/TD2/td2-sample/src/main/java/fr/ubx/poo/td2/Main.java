package fr.ubx.poo.td2;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

public class Main extends Application {
    @Override
    public void start(Stage stage) {
        Pane root = new Pane();

        // Affiche le robot
        Position position = new Position(80, 80);
        ImageView img = new ImageView(new Image("./robot.png"));
        img.setX(position.getX());
        img.setY(position.getY());

        // Affiche la fenetre
        root.getChildren().addAll(img);
        Scene scene = new Scene(root, 200, 200);
        scene.setFill(Color.rgb(241,199,128));
        stage.setTitle("POO - TD1");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) { launch(); }
}