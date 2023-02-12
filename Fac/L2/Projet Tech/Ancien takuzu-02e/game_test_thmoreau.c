#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"

void usage(int argc, char *argv[]) {
    fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
    exit(EXIT_FAILURE);
}

bool test_dummy() {
    return true;
}

bool test_game_is_over() {
    bool test = true;
    game g = game_default_solution();
    if (!game_is_over(g)) test = false;
    game_play_move(g, 0, 0, S_EMPTY);
    if (game_is_over(g)) test = false;
    game g2 = game_new_empty();
    for (int i = 0; i < 3; i++) {
        game_play_move(g2, i, 0, S_ZERO);
        game_play_move(g2, i, 1, S_ZERO);
        game_play_move(g2, i, 2, S_ZERO);
        game_play_move(g2, i, 3, S_ONE);
        game_play_move(g2, i, 4, S_ONE);
        game_play_move(g2, i, 5, S_ONE);
    }
    for (int i = 3; i < DEFAULT_SIZE; i++) {
        game_play_move(g2, i, 0, S_ONE);
        game_play_move(g2, i, 1, S_ONE);
        game_play_move(g2, i, 2, S_ONE);
        game_play_move(g2, i, 3, S_ZERO);
        game_play_move(g2, i, 4, S_ZERO);
        game_play_move(g2, i, 5, S_ZERO);
    }
    if (game_is_over(g2)) test = false;
    game g3 = game_new_empty_ext(4, 4, true, true);
    for (int i = 0; i < 2; i++) {
        game_play_move(g3, i, 0, S_ZERO);
        game_play_move(g3, i, 1, S_ONE);
        game_play_move(g3, i, 2, S_ZERO);
        game_play_move(g3, i, 3, S_ONE);
    }
    for (int i = 2; i < 4; i++) {
        game_play_move(g3, i, 0, S_ONE);
        game_play_move(g3, i, 1, S_ZERO);
        game_play_move(g3, i, 2, S_ONE);
        game_play_move(g3, i, 3, S_ZERO);
    }
    if (game_is_over(g3)) test = false;
    game_delete(g);
    game_delete(g2);
    game_delete(g3);
    return test;
}

bool test_game_restart() {
    bool test = true;
    game g1 = game_default_solution();
    game g2 = game_default();
    game_play_move(g1, 0, 0, S_ONE);
    game_play_move(g1, 0, 0, S_ZERO);
    game_restart(g1);
    game_undo(g1);
    if (game_equal(g1, g2) == false) test = false;
    game_restart(g2);
    if (game_equal(g1, g2) == false) test = false;
    game_delete(g1);
    game_delete(g2);
    return test;
}

bool test_game_play_move() {
    bool test = true;
    game g = game_default();
    game_play_move(g, 0, 0, S_ONE);
    if (game_get_square(g, 0, 0) != S_ONE) test = false;
    game_delete(g);
    return test;
}

bool test_game_new_empty() {
    game g = game_new_empty();
    for (int i = 0; i < DEFAULT_SIZE; i++) {
        for (int j = 0; j < DEFAULT_SIZE; j++) {
            if (game_get_square(g, i, j) != S_EMPTY) {
                game_delete(g);
                return false;
            }
        }
    }
    game_delete(g);
    return true;
}

bool test_game_new() {
    bool test = true;
    square tab[36] = {S_EMPTY};
    game g1 = game_new(tab);
    game g2 = game_new_empty();
    if (game_equal(g1, g2) == false) test = false;
    tab[0] = S_ONE;
    game_set_square(g2, 0, 0, S_ONE);
    game_delete(g1);
    game g3 = game_new(tab);
    if (game_equal(g3, g2) == false) test = false;
    game_delete(g3);
    game_delete(g2);
    return test;
}

bool test_game_default_solution() {
    game g = game_default_solution();
    if (game_is_over(g)) {
        game_delete(g);
        return true;
    }
    game_delete(g);
    return false;
}

bool test_game_print() {
    game g = game_default();
    game_print(g);
    game_delete(g);
    return true;
}

bool test_game_undo() {
    bool test = true;
    game g = game_new_empty();
    game_play_move(g, 0, 0, S_ZERO);
    game_play_move(g, 0, 1, S_ONE);
    game_undo(g);
    if (game_get_square(g, 0, 1) == S_ONE) test = false;
    game_undo(g);
    if (game_get_square(g, 0, 0) == S_ZERO) test = false;
    game_delete(g);
    return test;
}

bool test_game_redo() {
    bool test = true;
    game g = game_new_empty();
    game_play_move(g, 0, 0, S_ZERO);
    game_play_move(g, 0, 1, S_ONE);
    game_undo(g);
    game_undo(g);
    game_redo(g);
    if (game_get_square(g, 0, 0) != S_ZERO) test = false;
    game_undo(g);
    if (game_get_square(g, 0, 0) != S_EMPTY) test = false;
    game_redo(g);
    game_redo(g);
    if (game_get_square(g, 0, 1) != S_ONE) test = false;
    game_delete(g);
    return test;
}

int main(int argc, char *argv[]) {
    if (argc == 1) usage(argc, argv);

    fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
    bool ok = false;

    if (strcmp("dummy", argv[1]) == 0)
        ok = test_dummy();
    else if (strcmp("game_is_over", argv[1]) == 0)
        ok = test_game_is_over();
    else if (strcmp("game_restart", argv[1]) == 0)
        ok = test_game_restart();
    else if (strcmp("game_play_move", argv[1]) == 0)
        ok = test_game_play_move();
    else if (strcmp("game_new_empty", argv[1]) == 0)
        ok = test_game_new_empty();
    else if (strcmp("game_new", argv[1]) == 0)
        ok = test_game_new();
    else if (strcmp("game_default_solution", argv[1]) == 0)
        ok = test_game_default_solution();
    else if (strcmp("game_print", argv[1]) == 0)
        ok = test_game_print();
    else if (strcmp("game_undo", argv[1]) == 0)
        ok = test_game_undo();
    else if (strcmp("game_redo", argv[1]) == 0)
        ok = test_game_redo();
    else {
        fprintf(stderr, "Error: test \"%s\" not found!\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (ok) {
        fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
        return EXIT_SUCCESS;
    } else {
        fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
        return EXIT_FAILURE;
    }
}