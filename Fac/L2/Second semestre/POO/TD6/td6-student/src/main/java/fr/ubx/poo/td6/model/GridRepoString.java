package fr.ubx.poo.td6.model;

public class GridRepoString implements GridRepo {
    final char EOL = 'x';

    @Override
    public Grid load(String string) {
        Grid grid = new Grid(0, 0);
        int j = 0;
        for (int i = 0; i < string.length(); i++) {
            switch (string.charAt(i)) {
                case 'R':
                    grid.set(i, j, Entity.ROCK);
                    break;
                case 'B':
                    grid.set(i, j, Entity.BIGROCK);
                    break;
                case 'G':
                    grid.set(i, j, Entity.GROUND);
                    break;
                case 'C':
                    grid.set(i, j, Entity.CRACK);
                    break;
                case 'E':
                    grid.set(i, j, Entity.ENERGY);
                    break;
                case 'D':
                    grid.set(i, j, Entity.DUST);
                    break;
                case 'x':
                    j++;
                    break;
            }
        }
        return grid;
    }

    @Override
    public String export(Grid grid) {
        StringBuilder s = new StringBuilder();
        for (int i = 0; i < grid.getHeight(); i++) {
            for (int j = 0; j < grid.getWidth(); j++) {
                switch (grid.get(i, j)) {
                    case ROCK:
                        s.append('R');
                        break;
                    case BIGROCK:
                        s.append('B');
                        break;
                    case GROUND:
                        s.append('G');
                        break;
                    case CRACK:
                        s.append('C');
                        break;
                    case ENERGY:
                        s.append('E');
                        break;
                    case DUST:
                        s.append('D');
                        break;
                }
            }
            s.append('x');
        }
        return s.toString();
    }
}
