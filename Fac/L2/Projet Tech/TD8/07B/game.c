#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_struct.h"

void *my_malloc(size_t x) {
  void *y = malloc(x);
  if (y == NULL) {
    fprintf(stderr, "not enough memory!\n");
    exit(EXIT_FAILURE);
  }
  return (y);
}

void *my_calloc(size_t nmemb, size_t size) {
  void *ptr = calloc(nmemb, size);
  if (ptr == NULL) {
    fprintf(stderr, "not enough memory!\n");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

void check_parameters(cgame g, uint i, uint j) {
  if ((g == NULL) || (i >= g->nb_rows) || (j >= g->nb_cols)) {
    printf(
        "erreur dans les parametres, exit du programme\nVérifiez que g est non "
        "null, ou alors que les coordonées sont valides\n");
    exit(-1);
  }
}

game game_new(square *squares) {
  return game_new_ext(DEFAULT_SIZE, DEFAULT_SIZE, squares, false, false);
}

game game_new_empty(void) {
  return game_new_empty_ext(DEFAULT_SIZE, DEFAULT_SIZE, false, false);
  ;
}

game game_copy(cgame g) {
  check_parameters(g, 0, 0);
  game g1 = game_new_ext(game_nb_rows(g), game_nb_cols(g), g->tab,
                         game_is_wrapping(g), game_is_unique(g));
  return g1;
}

bool game_equal(cgame g1, cgame g2) {
  check_parameters(g1, 0, 0);
  check_parameters(g2, 0, 0);
  if (game_nb_rows(g1) != game_nb_rows(g2) ||
      game_nb_cols(g1) != game_nb_cols(g2))
    return false;
  for (int i = 0; i < game_nb_rows(g1); i++) {
    for (int j = 0; j < game_nb_cols(g1); j++) {
      if (game_get_square(g1, i, j) != game_get_square(g2, i, j)) {
        return false;
      }
    }
  }
  if (game_is_wrapping(g1) != game_is_wrapping(g2) ||
      game_is_unique(g1) != game_is_unique(g2))
    return false;
  return true;
}

void game_delete(game g) {
  if (g != NULL) {
    queue_free_full(g->q_redo, free);
    queue_free_full(g->q_undo, free);
    free(g->tab);
    free(g);
  }
}

void game_set_square(game g, uint i, uint j, square s) {
  check_parameters(g, 0, 0);
  assert(i < game_nb_rows(g));
  assert(j < game_nb_cols(g));
  g->tab[i * game_nb_cols(g) + j] = s;
}

square game_get_square(cgame g, uint i, uint j) {
  check_parameters(g, 0, 0);
  assert(i < game_nb_rows(g));
  assert(j < game_nb_cols(g));
  return g->tab[i * game_nb_cols(g) + j];
}

int game_get_number(cgame g, uint i, uint j) {
  check_parameters(g, i, j);
  square res = game_get_square(g, i, j);
  switch (res) {
    case S_IMMUTABLE_ZERO:
    case S_ZERO:
      return 0;

    case S_IMMUTABLE_ONE:
    case S_ONE:
      return 1;

    default:
      return -1;
  }
}

int game_get_next_square(cgame g, uint i, uint j, direction dir, uint dist) {
  check_parameters(g, i, j);
  if (dist > 2) {
    fprintf(stderr, "Unvalid parameter\n");
    exit(EXIT_FAILURE);
  }
  int nb_rows = game_nb_rows(g);
  int nb_cols = game_nb_cols(g);
  switch (dir) {
    case UP:
      if (!game_is_wrapping(g) && (int)(i - dist) < 0) {
        return -1;
      }
      return game_get_square(g, (nb_rows + i - dist) % nb_rows, j);

    case DOWN:
      if (!game_is_wrapping(g) && (i + dist) >= nb_rows) {
        return -1;
      }
      return game_get_square(g, (i + dist) % nb_rows, j);

    case LEFT:
      if (!game_is_wrapping(g) && (int)(j - dist) < 0) {
        return -1;
      }
      return game_get_square(g, i, (nb_cols + j - dist) % nb_cols);

    default:
      if (!game_is_wrapping(g) && (j + dist) >= nb_cols) {
        return -1;
      }
      return game_get_square(g, i, (j + dist) % nb_cols);
  }
}

int game_get_next_number(cgame g, uint i, uint j, direction dir, uint dist) {
  check_parameters(g, i, j);
  square res = game_get_next_square(g, i, j, dir, dist);
  switch (res) {
    case S_IMMUTABLE_ZERO:
    case S_ZERO:
      return 0;

    case S_IMMUTABLE_ONE:
    case S_ONE:
      return 1;

    default:
      return -1;
  }
}

bool game_is_empty(cgame g, uint i, uint j) {
  check_parameters(g, i, j);
  if (game_get_square(g, i, j) == S_EMPTY) {
    return true;
  }
  return false;
}

bool game_is_immutable(cgame g, uint i, uint j) {
  check_parameters(g, i, j);
  if (game_get_square(g, i, j) == S_IMMUTABLE_ONE ||
      game_get_square(g, i, j) == S_IMMUTABLE_ZERO) {
    return true;
  }
  return false;
}

int game_has_error(cgame g, uint i, uint j) {
  check_parameters(g, i, j);

  direction dir[4] = {UP, DOWN, LEFT, RIGHT};
  int tmp = game_get_number(g, i, j);
  int nb_rows = game_nb_rows(g);
  int nb_cols = game_nb_cols(g);
  if (tmp == -1) {
    return 0;
  }

  // vérfication qu'il n'y ait pas plus de 2 w/W ou b/B côte à côte
  for (int k = 0; k < 4; k++) {
    if (tmp == game_get_next_number(g, i, j, dir[k], 1) &&
        (tmp == game_get_next_number(g, i, j, dir[k], 2))) {
      return -1;
    } else if (k == 0 || k == 2) {
      if ((tmp == game_get_next_number(g, i, j, dir[k], 1)) &&
          (tmp == game_get_next_number(g, i, j, dir[k + 1], 1))) {
        return -1;
      }
    }
  }

  // Partie verification S_ZERO ou S_ONE < nb_cols/2 ou nb_rows/2
  int cpt = 0;
  for (int x = 0; x < nb_rows; x++) {
    if (game_get_number(g, x, j) == tmp) {
      cpt++;
    }
  }
  if (cpt > (nb_rows / 2)) {
    return -1;
  }
  cpt = 0;
  for (int y = 0; y < nb_cols; y++) {
    if (game_get_number(g, i, y) == tmp) {
      cpt++;
    }
  }
  if (cpt > (nb_cols / 2)) {
    return -1;
  }

  // Partie vérification unique
  if (game_is_unique(g) == true) {
    ////////////////////////////////////////////// comparaison des lignes
    int cpt_same_squares = 0;  // compteur des cases qui sont égales
    for (int x = 0; x < nb_rows; x++) {
      if (x != i) {
        for (int y = 0; y < nb_cols; y++) {
          if (game_get_number(g, i, y) == game_get_number(g, x, y)) {
            cpt_same_squares++;
          } else {
            cpt_same_squares = 0;
            break;
          }
        }
      }
      if (cpt_same_squares == nb_cols) {
        return -1;
      }
    }
    ////////////////////////////////////////////// comparaison des colonnes
    for (int x = 0; x < nb_cols; x++) {
      if (x != j) {
        for (int y = 0; y < nb_rows; y++) {
          if (game_get_number(g, y, j) == game_get_number(g, y, x)) {
            cpt_same_squares++;
          } else {
            cpt_same_squares = 0;
            break;
          }
        }
      }
      if (cpt_same_squares == nb_rows) {
        return -1;
      }
    }
  }
  return 0;
}

bool game_check_move(cgame g, uint i, uint j, square s) {
  check_parameters(g, 0, 0);
  if (i < 0 || i >= game_nb_rows(g) || j < 0 || j >= game_nb_cols(g)) {
    return false;
  }
  if (game_is_immutable(g, i, j) == true || s == S_IMMUTABLE_ONE ||
      s == S_IMMUTABLE_ZERO) {
    return false;
  }
  return true;
}

void game_play_move(game g, uint i, uint j, square s) {
  check_parameters(g, i, j);
  if (game_check_move(g, i, j, s)) {
    struct move *m = my_malloc(sizeof(*m));
    m->row = i;
    m->col = j;
    m->square_prev = game_get_square(g, i, j);
    game_set_square(g, i, j, s);
    queue_push_head(g->q_undo, m);
  }
}

bool game_is_over(cgame g) {
  check_parameters(g, 0, 0);
  for (int i = 0; i < game_nb_rows(g); i++) {
    for (int j = 0; j < game_nb_cols(g); j++) {
      if (game_has_error(g, i, j) != 0 || game_get_number(g, i, j) == -1) {
        return false;
      }
    }
  }
  return true;
}

void game_restart(game g) {
  check_parameters(g, 0, 0);
  for (int i = 0; i < game_nb_rows(g); i++) {
    for (int j = 0; j < game_nb_cols(g); j++) {
      if (!game_is_immutable(g, i, j) && game_get_number(g, i, j) != -1) {
        game_set_square(g, i, j, S_EMPTY);
      }
    }
  }
  queue_clear_full(g->q_redo, free);
  queue_clear_full(g->q_undo, free);
}
