#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_ext.h"
#include "game_struct.h"

void game_print(cgame g) {
    printf("   ");
    for (int j = 0; j < g->columns; j++) {
        printf("%d", j);
    }
    printf("\n   ");
    for (int j = 0; j < g->columns; j++) printf("-");
    printf("\n");
    for (int i = 0; i < g->rows; i++) {
        printf("%d |", i);
        for (int j = 0; j < g->columns; j++) {
            square state = game_get_square(g, i, j);
            if (state == S_IMMUTABLE_ONE) {
                printf("B");
            }
            if (state == S_IMMUTABLE_ZERO) {
                printf("W");
            }
            if (state == S_ONE) {
                printf("b");
            }
            if (state == S_ZERO) {
                printf("w");
            } else if (state == S_EMPTY)
                printf(" ");
        }
        printf("|\n");
    }
};

game game_default(void) {
    game def = game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, false);
    if (def == NULL) {
        fprintf(stderr, "erreur allocation");
        exit(EXIT_FAILURE);
    }
    // par ligne
    game_set_square(def, 0, 1, S_IMMUTABLE_ONE);
    game_set_square(def, 0, 2, S_IMMUTABLE_ZERO);
    game_set_square(def, 2, 1, S_IMMUTABLE_ZERO);
    game_set_square(def, 2, 4, S_IMMUTABLE_ZERO);
    game_set_square(def, 3, 1, S_IMMUTABLE_ZERO);
    game_set_square(def, 3, 2, S_IMMUTABLE_ONE);
    game_set_square(def, 4, 2, S_IMMUTABLE_ONE);
    game_set_square(def, 4, 5, S_IMMUTABLE_ZERO);
    game_set_square(def, 5, 5, S_IMMUTABLE_ZERO);
    return def;
};

game game_default_solution(void) {
    game g = game_default();
    if (g == NULL) {
        fprintf(stderr, "Alloc error\n");
        exit(EXIT_FAILURE);
    }
    // à partir du fichier moves.txt :
    game_set_square(g, 0, 0, S_ZERO);
    game_set_square(g, 0, 3, S_ONE);
    game_set_square(g, 0, 4, S_ZERO);
    game_set_square(g, 0, 5, S_ONE);

    game_set_square(g, 1, 0, S_ZERO);
    game_set_square(g, 1, 1, S_ONE);
    game_set_square(g, 1, 2, S_ONE);
    game_set_square(g, 1, 3, S_ZERO);
    game_set_square(g, 1, 4, S_ONE);
    game_set_square(g, 1, 5, S_ZERO);

    game_set_square(g, 2, 0, S_ONE);
    game_set_square(g, 2, 2, S_ZERO);
    game_set_square(g, 2, 3, S_ONE);
    game_set_square(g, 2, 5, S_ONE);

    game_set_square(g, 3, 0, S_ONE);
    game_set_square(g, 3, 3, S_ZERO);
    game_set_square(g, 3, 4, S_ZERO);
    game_set_square(g, 3, 5, S_ONE);

    game_set_square(g, 4, 0, S_ZERO);
    game_set_square(g, 4, 1, S_ONE);
    game_set_square(g, 4, 3, S_ZERO);
    game_set_square(g, 4, 4, S_ONE);

    game_set_square(g, 5, 0, S_ONE);
    game_set_square(g, 5, 1, S_ZERO);
    game_set_square(g, 5, 2, S_ZERO);
    game_set_square(g, 5, 3, S_ONE);
    game_set_square(g, 5, 4, S_ONE);

    return g;
};
