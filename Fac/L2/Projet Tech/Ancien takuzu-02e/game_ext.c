#include "game_ext.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_struct.h"

game game_new_ext(uint nb_rows, uint nb_cols, square *squares, bool wrapping,
                  bool unique) {
    if (squares == NULL) {
        fprintf(stderr, "invalid square pointer!\n");
        exit(EXIT_FAILURE);
    }
    game g = (game)malloc(sizeof(struct game_s));
    if (g == NULL) {
        fprintf(stderr, "allocation failure!\n");
        exit(EXIT_FAILURE);
    }
    g->rows = nb_rows;
    g->columns = nb_cols;
    g->board = (square **)malloc(sizeof(square *) * g->rows);
    for (int i = 0; i < (g->rows); i++) {
        g->board[i] = (square *)malloc(sizeof(square) * g->columns);
        if (g->board[i] == NULL) {
            fprintf(stderr, "allocation failure!\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < (g->columns); j++) {
            g->board[i][j] = squares[i * (g->columns) + j];
        }
    }
    g->wrapping = wrapping;
    g->unique = unique;
    g->undo = queue_new();
    g->redo = queue_new();
    return g;
}

game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping,
                        bool unique) {
    if (nb_rows < 2 || nb_cols < 2) {
        fprintf(stderr, "invalid dimensions\n");
        exit(EXIT_FAILURE);
    }
    square squares[nb_rows * nb_cols];
    for (uint i = 0; i < (nb_rows * nb_cols); i++) {
        squares[i] = S_EMPTY;
    }
    return game_new_ext(nb_rows, nb_cols, squares, wrapping, unique);
}

uint game_nb_rows(cgame g) {
    if (g == NULL) {
        fprintf(stderr, "invalid game pointer\n");
        exit(EXIT_FAILURE);
    }
    return g->rows;
}

uint game_nb_cols(cgame g) {
    if (g == NULL) {
        fprintf(stderr, "invalid game pointer\n");
        exit(EXIT_FAILURE);
    }
    return g->columns;
}

bool game_is_wrapping(cgame g) {
    // test g
    if (g == NULL) {
        fprintf(stderr, "invalid game pointer\n");
        exit(EXIT_FAILURE);
    }
    return g->wrapping;
}

bool game_is_unique(cgame g) {
    // test g
    if (g == NULL) {
        fprintf(stderr, "invalid game pointer\n");
        exit(EXIT_FAILURE);
    }
    return g->unique;
}

void game_undo(game g) {
    if (g == NULL) {
        fprintf(stderr, "invalid game pointer\n");
        exit(EXIT_FAILURE);
    }
    if (!queue_is_empty(g->undo)) {
        queueSquare *undoQ = queue_pop_head(g->undo);
        queueSquare redoQ = {undoQ->i, undoQ->j,
                             game_get_square(g, undoQ->i, undoQ->j)};
        queue_push_head(g->redo, &redoQ);
        game_set_square(g, undoQ->i, undoQ->j, undoQ->value);
        free(undoQ);

        /*
        queueSquare undoSquare;
        queueSquare *undoSquareP = &undoSquare;
        undoSquareP = queue_pop_head(g->undo);
        game_set_square(g, undoSquare.i, undoSquare.j, undoSquare.value);
        queue_push_head(g->redo, undoSquareP);
        */

        // A MODIFIER (MEM ERR)
    }
}

void game_redo(game g) {
    if (g == NULL) {
        fprintf(stderr, "invalid game pointer\n");
        exit(EXIT_FAILURE);
    }
    if (!queue_is_empty(g->redo)) {
        queueSquare *redoQ = queue_pop_head(g->redo);
        queueSquare *undoQ = malloc(sizeof(queueSquare));
        undoQ->i = redoQ->i;
        undoQ->j = redoQ->j;
        undoQ->value = game_get_square(g, redoQ->i, redoQ->j);
        queue_push_head(g->undo, undoQ);
        game_set_square(g, redoQ->i, redoQ->j, redoQ->value);
        free(redoQ);

        // A MODIFIER (MEM ERR)
    }
}
