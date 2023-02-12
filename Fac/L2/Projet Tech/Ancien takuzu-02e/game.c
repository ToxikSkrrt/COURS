#include "game.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_ext.h"
#include "game_struct.h"

enum err_code {
    NO_ERROR = 0,
    E_CONSEC_IN_ROW,
    E_CONSEC_IN_COL,
    E_TOO_MANY_IN_ROW,
    E_TOO_MANY_IN_COL,
    E_INVALID_VALUE,
    E_NON_UNIQUE_COL,
    E_NON_UNIQUE_ROW,
};

game game_new(square* squares) {
    return game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, squares, false, false);
}

game game_new_empty(void) {
    return game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, false);
}

game game_copy(cgame g) {
    if (g == NULL || g->board == NULL) {
        fprintf(stderr, "invalid pointer for g\n");
        exit(EXIT_FAILURE);
    }
    square tmpSquares[(g->rows) * (g->columns)];
    for (int i = 0; i < (g->rows); i++) {
        for (int j = 0; j < (g->columns); j++) {
            tmpSquares[i * (g->columns) + j] = g->board[i][j];
        }
    }
    game gNew = game_new_ext(game_nb_rows(g), game_nb_cols(g), tmpSquares,
                             game_is_wrapping(g), game_is_unique(g));
    // Si nécessaire faire:
    // gNew->redo = g->redo;
    // gNew->undo = g->undo;
    return gNew;
}

bool game_equal(cgame g1, cgame g2) {
    if (g1 == NULL || g2 == NULL) {
        fprintf(stderr, "invalid cgame pointer(s) !\n");
        exit(EXIT_FAILURE);
    }
    if (g1->board == NULL || g2->board == NULL) {
        fprintf(stderr, "invalid board pointer\n");
        exit(EXIT_FAILURE);
    }
    if (g1->rows != g2->rows || g1->columns != g2->columns) {
        return false;
    }
    if (game_is_unique(g1) != game_is_unique(g2) ||
        game_is_wrapping(g1) != game_is_wrapping(g2)) {
        return false;
    }
    for (int i = 0; i < g1->rows; i++) {
        if (g1->board[i] == NULL || g2->board[i] == NULL) {
            fprintf(stderr, "invalid board[i] pointer\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < g1->columns; j++) {
            if (g1->board[i][j] != g2->board[i][j]) return false;
        }
    }
    return true;
}

void game_delete(game g) {
    if (g == NULL) {
        fprintf(stderr, "Alloc error\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < g->rows; i++) free(g->board[i]);
    queue_free(g->undo);
    queue_free(g->redo);
    free(g->board);
    free(g);
}

void game_set_square(game g, uint i, uint j, square s) {
    // test g
    if (g == NULL) {
        fprintf(stderr, "invalid game pointer");
        exit(EXIT_FAILURE);
    }
    // test valeur i et j
    if (i > g->rows || j > g->columns) {
        fprintf(stderr, "invalid parameter value");
        exit(EXIT_FAILURE);
    }
    // set_square
    g->board[i][j] = s;
}

square game_get_square(cgame g, uint i, uint j) {
    // test g
    if (g == NULL) {
        fprintf(stderr, "invalid game pointer");
        exit(EXIT_FAILURE);
    }
    // test valeur i et j
    if (i >= g->rows || j >= g->columns) {
        fprintf(stderr, "invalid parameter value");
        exit(EXIT_FAILURE);
    }
    return g->board[i][j];
}

int game_get_number(cgame g, uint i, uint j) {
    square cell = game_get_square(g, i, j);
    if (cell == S_IMMUTABLE_ONE || cell == S_ONE) return 1;
    if (cell == S_IMMUTABLE_ZERO || cell == S_ZERO) return 0;
    return -1;
}

int game_get_next_square(cgame g, uint i, uint j, direction dir, uint dist) {
    // test g
    if (g == NULL) {
        fprintf(stderr, "invalid game pointer");
        exit(EXIT_FAILURE);
    }
    // test valeur i et j
    if (i >= g->rows || j >= g->columns) {
        fprintf(stderr, "invalid parameter value");
        exit(EXIT_FAILURE);
    }
    // test dir
    if (dist > 2) {
        fprintf(stderr, "invalid distance");
        exit(EXIT_FAILURE);
    }
    if (!game_is_wrapping(g)) {
        // pour chaque direction
        if (dir == DOWN) {
            if (i + dist >= g->rows) {
                fprintf(stderr, "next square out of board");
                return -1;
            }
            return (g->board[i + dist][j]);
        }
        if (dir == UP) {
            if (i - dist < 0) {
                fprintf(stderr, "next square out of board");
                return -1;
            }
            return (g->board[i - dist][j]);
        }
        if (dir == LEFT) {
            if (j - dist < 0) {
                fprintf(stderr, "next square out of board");
                return -1;
            }
            return (g->board[i][j - dist]);
        }
        if (dir == RIGHT) {
            if (j + dist >= g->columns) {
                fprintf(stderr, "next square out of board");
                return -1;
            }
            return (g->board[i][j + dist]);
        }
    } else {
        if (dir == DOWN) {
            return (g->board[(i + dist) % game_nb_rows(g)][j]);
        }
        if (dir == UP) {
            return (
                g->board[(i - dist + game_nb_rows(g)) % game_nb_rows(g)][j]);
        }
        if (dir == LEFT) {
            return (
                g->board[i][(j - dist + game_nb_cols(g)) % game_nb_cols(g)]);
        }
        if (dir == RIGHT) {
            return (g->board[i][(j + dist) % game_nb_cols(g)]);
        }
    }
    return -1;
}

int game_get_next_number(cgame g, uint i, uint j, direction dir, uint dist) {
    square cell = game_get_next_square(g, i, j, dir, dist);
    if (cell == S_IMMUTABLE_ONE || cell == S_ONE) return 1;
    if (cell == S_IMMUTABLE_ZERO || cell == S_ZERO) return 0;
    return -1;
}

bool game_is_empty(cgame g, uint i, uint j) {
    if (g == NULL) {
        fprintf(stderr, "Alloc error\n");
        exit(EXIT_FAILURE);
    }
    if (i > g->rows || j > g->columns) {
        fprintf(stderr, "Row / collumn parameter(s) error\n");
        exit(EXIT_FAILURE);
    }
    if (game_get_square(g, i, j) == S_EMPTY) return true;
    return false;
}

bool game_is_immutable(cgame g, uint i, uint j) {
    if (g == NULL) {
        fprintf(stderr, "Alloc error\n");
        exit(EXIT_FAILURE);
    }
    if (i > g->rows || j > g->columns) {
        fprintf(stderr, "Row / collumn parameter(s) error\n");
        exit(EXIT_FAILURE);
    }
    if (game_get_square(g, i, j) == S_IMMUTABLE_ONE ||
        game_get_square(g, i, j) == S_IMMUTABLE_ZERO)
        return true;
    return false;
}

int game_has_error(cgame g, uint i, uint j) {
    if (g == NULL) {
        fprintf(stderr, "invalid cgame pointer!\n");
        exit(EXIT_FAILURE);
    }
    int errorCode;
    int tmpSquare;
    int count;
    switch (game_get_square(g, i, j)) {
        case S_ZERO:
        case S_ONE:
        case S_IMMUTABLE_ZERO:
        case S_IMMUTABLE_ONE:
            // Compte du nombre de cases ayant la même valeur que (i,j) dans
            // la ligne correspondante
            tmpSquare = game_get_number(g, i, j);
            count = 0;
            for (int k = 0; k < (g->columns); k++) {
                if (game_get_number(g, i, k) == tmpSquare) {
                    count++;
                }
            }
            if (count > g->columns / 2) {
                errorCode = (int)E_TOO_MANY_IN_ROW;
                break;
            }
            // Compte du nb de cases ayant la même valeur que (i,j) dans la
            // colonne correspondante
            count = 0;
            for (int k = 0; k < g->rows; k++) {
                if (game_get_number(g, k, j) == tmpSquare) {
                    count++;
                }
            }
            if (count > g->rows / 2) {
                errorCode = (int)E_TOO_MANY_IN_COL;
                break;
            }
            // compte des cases consécutives à (i,j) dans sa ligne
            count = 1;
            if (game_is_wrapping(g)) {
                if (game_get_next_number(g, i, j, LEFT, 1) == tmpSquare) {
                    count++;
                    if (game_get_next_number(g, i, j, LEFT, 2) == tmpSquare) {
                        count++;
                    }
                }
                if (game_get_next_number(g, i, j, RIGHT, 1) == tmpSquare) {
                    count++;
                    if (game_get_next_number(g, i, j, RIGHT, 2) == tmpSquare) {
                        count++;
                    }
                }
            } else {
                if (j > 0 &&
                    game_get_next_number(g, i, j, LEFT, 1) == tmpSquare) {
                    count++;
                    if (j > 1 &&
                        game_get_next_number(g, i, j, LEFT, 2) == tmpSquare) {
                        count++;
                    }
                }
                if (j + 1 < g->columns &&
                    game_get_next_number(g, i, j, RIGHT, 1) == tmpSquare) {
                    count++;
                    if (j + 2 < g->columns &&
                        game_get_next_number(g, i, j, RIGHT, 2) == tmpSquare) {
                        count++;
                    }
                }
            }
            if (count > 2) {
                errorCode = (int)E_CONSEC_IN_ROW;
                break;
            }
            // compte des cases consécutives à (i,j) dans sa colonne
            count = 1;
            if (game_is_wrapping(g)) {
                if (game_get_next_number(g, i, j, UP, 1) == tmpSquare) {
                    count++;
                    if (game_get_next_number(g, i, j, UP, 2) == tmpSquare) {
                        count++;
                    }
                }
                if (game_get_next_number(g, i, j, DOWN, 1) == tmpSquare) {
                    count++;
                    if (game_get_next_number(g, i, j, DOWN, 2) == tmpSquare) {
                        count++;
                    }
                }
            } else {
                if (i > 0 &&
                    game_get_next_number(g, i, j, UP, 1) == tmpSquare) {
                    count++;
                    if (i > 1 &&
                        game_get_next_number(g, i, j, UP, 2) == tmpSquare) {
                        count++;
                    }
                }
                if (i + 1 < g->rows &&
                    game_get_next_number(g, i, j, DOWN, 1) == tmpSquare) {
                    count++;
                    if ((i + 2 < g->rows) &&
                        game_get_next_number(g, i, j, DOWN, 2) == tmpSquare) {
                        count++;
                    }
                }
            }
            if (count > 2) {
                errorCode = (int)E_CONSEC_IN_COL;
                break;
            }
            // test pour unique:
            if (game_is_unique(g)) {
                // row
                for (int r = 0; r < g->rows; r++) {
                    if (r == i) {
                        r++;
                    } else {
                        for (int c = 0; c < g->columns; c++) {
                            if (game_get_square(g, r, c) == S_EMPTY ||
                                game_get_number(g, r, c) !=
                                    game_get_number(g, i, c)) {
                                c = g->columns;
                            } else if (c == (game_nb_cols(g) - 1)) {
                                return (int)E_NON_UNIQUE_ROW;
                            }
                        }
                    }
                }
                // column
                for (int c = 0; c < g->columns; c++) {
                    if (c == j) {
                        c++;
                    } else {
                        for (int r = 0; r < g->rows; r++) {
                            if (game_get_square(g, r, c) == S_EMPTY ||
                                game_get_number(g, r, c) !=
                                    game_get_number(g, r, j)) {
                                r = g->rows;
                            } else if (r == (game_nb_rows(g) - 1)) {
                                return (int)E_NON_UNIQUE_COL;
                            }
                        }
                    }
                }
            }
            errorCode = (int)NO_ERROR;
            break;
        case S_EMPTY:
            errorCode = (int)NO_ERROR;
            break;
        default:
            errorCode = (int)E_INVALID_VALUE;
    }
    return errorCode;
}

bool game_check_move(cgame g, uint i, uint j, square s) {
    if (g == NULL || g->board == NULL) {
        fprintf(stderr, "invalid pointer for g!\n");
        exit(EXIT_FAILURE);
    }
    if ((i >= g->rows) || j >= g->columns) {
        return false;
    }
    switch (s) {
        case S_EMPTY:
        case S_ZERO:
        case S_ONE:
            break;
        default:
            return false;
    }
    if (g->board[i][j] == S_IMMUTABLE_ZERO ||
        g->board[i][j] == S_IMMUTABLE_ONE) {
        return false;
    }
    return true;
}

void game_play_move(game g, uint i, uint j, square s) {
    if (g == NULL) {
        fprintf(stderr, "Alloc error\n");
        exit(EXIT_FAILURE);
    }
    if (i > g->rows || j > g->columns) {
        fprintf(stderr, "Row / collumn parameter(s) error\n");
        exit(EXIT_FAILURE);
    }
    if (s != S_EMPTY && s != S_ONE && s != S_ZERO) {
        fprintf(stderr, "Square parameter error\n");
        exit(EXIT_FAILURE);
    }

    if (!game_is_immutable(g, i, j)) {
        queueSquare lastMove = {i, j, game_get_square(g, i, j)};
        queue_push_head(g->undo, &lastMove);
        game_set_square(g, i, j, s);

        if (!queue_is_empty(g->redo)) queue_clear(g->redo);
    }
}

bool game_is_over(cgame g) {
    if (g == NULL) {
        fprintf(stderr, "Alloc error\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->columns; j++) {
            if (game_is_empty(g, i, j) || game_has_error(g, i, j) != 0)
                return false;
        }
    }
    return true;
}

void game_restart(game g) {
    if (g == NULL) {
        fprintf(stderr, "Alloc error\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->columns; j++) {
            if (!game_is_immutable(g, i, j)) game_set_square(g, i, j, S_EMPTY);
        }
    }
    queue_clear(g->undo);
    queue_clear(g->redo);
}