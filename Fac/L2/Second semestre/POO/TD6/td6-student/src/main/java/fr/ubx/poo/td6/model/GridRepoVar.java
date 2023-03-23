package fr.ubx.poo.td6.model;

import java.lang.reflect.Field;

import static fr.ubx.poo.td6.model.Entity.*;

public class GridRepoVar implements GridRepo {

    private final Entity[][] sample1 = {
            {GROUND, GROUND, GROUND, GROUND, DUST, GROUND, GROUND, GROUND, GROUND},
            {GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, DUST, GROUND, GROUND},
            {GROUND, GROUND, ROCK, CRACK, GROUND, GROUND, BIGROCK, GROUND, GROUND},
            {GROUND, ROCK, GROUND, ROCK, GROUND, GROUND, GROUND, GROUND, GROUND},
            {GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND},
            {GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, CRACK, GROUND},
            {GROUND, DUST, GROUND, DUST, GROUND, GROUND, GROUND, GROUND, GROUND},
            {GROUND, GROUND, GROUND, CRACK, GROUND, DUST, BIGROCK, GROUND, GROUND},
            {GROUND, ROCK, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND},
    };

    private final Entity[][] sample2 = {
            {GROUND, ROCK, DUST, ROCK, GROUND},
            {GROUND, CRACK, BIGROCK, CRACK, DUST},
            {GROUND, CRACK, CRACK, GROUND, BIGROCK},
            {ROCK, DUST, DUST, GROUND, DUST}
    };

    @Override
    public Grid load(String string) {
        /*  Crée une nouvelle instance de la classe Grid et initialise les champs de l'objet avec les informations de sample1.
            Retourn le nouvel objet.
         */
        Entity[][] entities = getEntities(string);
        if (entities == null)
            return null;

        Grid grid = new Grid(sample1.length, sample1.length);
        for (int i = 0; i < sample1.length; i++) {
            for (int j = 0; j < sample1.length; j++) {
                grid.set(i , j, sample1[i][j]);
            }
        }
        return grid;
    }

    @Override
    public String export(Grid grid) {
        /*  Retourne sous forme de chaîne de caractères la déclaration Java correspondant aux tableau d'entités de l'objet grid.
            Le résultat produit doit être de la forme: private final Entity[][] sample1 = {....};
            Le code produit peut être utilisé pour remplacer la déclaration de sample1 plus haut.
        */
        StringBuilder s = new StringBuilder();
        s.append("private final Entity[][] sample = {");
        for (int i = 0; i < grid.getHeight(); i++) {
            s.append("{");
            for (int j = 0; j < grid.getWidth(); j++) {
                s.append(grid.get(i, j));
                s.append(", ");
            }
            s.append("}, ");
        }
        s.append("}");
        return s.toString();
    } // PAS VRAIMENT FINI MAIS TRKL

    private Entity[][] getEntities(String name) {
        try {
            Field field = this.getClass().getDeclaredField(name);
            return (Entity[][]) field.get(this);
        } catch (IllegalAccessException e) {
            return null;
        } catch (NoSuchFieldException e) {
            return null;
        }
    }
}
