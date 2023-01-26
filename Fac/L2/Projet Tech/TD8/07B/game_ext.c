#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_struct.h"

#define TAILLE_MAX 10

game game_new_ext(uint nb_rows, uint nb_cols, square* squares, bool wrapping,
                  bool unique) {
  game g = game_new_empty_ext(nb_rows, nb_cols, wrapping, unique);
  assert(g);
  memcpy(g->tab, squares, nb_rows * nb_cols * sizeof(square));
  return g;
}

game game_new_empty_ext(uint nb_rows, uint nb_cols, bool wrapping,
                        bool unique) {
  if (nb_rows % 2 != 0 || nb_cols % 2 != 0 || nb_cols > TAILLE_MAX  || nb_rows > TAILLE_MAX ) {
    return NULL;
  }
  game g = my_malloc(sizeof(*g));
  g->nb_rows = nb_rows;
  g->nb_cols = nb_cols;
  g->wrapping = wrapping;
  g->unique = unique;
  g->tab = my_calloc(nb_cols * nb_rows, sizeof(square));
  g->q_undo = queue_new();
  g->q_redo = queue_new();
  return g;
}

bool game_is_wrapping(cgame g) {
  check_parameters(g, 0, 0);
  return g->wrapping;
}

bool game_is_unique(cgame g) {
  check_parameters(g, 0, 0);
  return g->unique;
}

uint game_nb_cols(cgame g) {
  check_parameters(g, 0, 0);
  return g->nb_cols;
}

uint game_nb_rows(cgame g) {
  check_parameters(g, 0, 0);
  return g->nb_rows;
}

void game_undo(game g) {
  if (!queue_is_empty(g->q_undo)) {
    struct move* m = queue_pop_head(g->q_undo);
    game_play_move(g, m->row, m->col, m->square_prev);
    queue_push_head(g->q_redo, queue_pop_head(g->q_undo));
  }
}

void game_redo(game g) {
  if (!queue_is_empty(g->q_redo)) {
    struct move* m = queue_pop_head(g->q_redo);
    game_play_move(g, m->row, m->col, m->square_prev);
  }
}