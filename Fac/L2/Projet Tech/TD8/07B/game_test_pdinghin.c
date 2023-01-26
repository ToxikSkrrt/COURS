#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game_struct.h"

/*tester les entrées seulement sur game_check_move*/
void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/*Test function game_new*/
int test_game_new() {
  int size = DEFAULT_SIZE * DEFAULT_SIZE;
  square *squares = (square *)malloc(size * sizeof(square));
  for (int i = 0; i < size; i++) {
    squares[i] = S_ONE;
  }
  game g = game_new(squares);
  free(squares);
  if (g == NULL) {
    return 1;
  }
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    for (int j = 0; j < DEFAULT_SIZE; j++) {
      if (game_get_square(g, i, j) != S_ONE) {
        game_delete(g);
        return 1;
      }
    }
  }
  return 0;
}

int test_game_redo() {
  game g = game_new_empty_ext(4, 4, false, true);
  game g2 = game_copy(g);
  game_play_move(g, 0, 0, S_ZERO);
  game_play_move(g2, 0, 0, S_ZERO);
  game_undo(g);
  game_redo(g);
  if (game_equal(g, g2) == false) {
    game_delete(g);
    game_delete(g2);
    return 1;
  }
  game_delete(g);
  game_delete(g2);
  return 0;
}

/*Test function game_new_ext*/
int test_game_new_ext() {
  square squares[24] = {
      S_ONE, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_ZERO, S_EMPTY,
      S_ONE, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_ZERO, S_EMPTY,
      S_ONE, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_ZERO, S_EMPTY,
  };
  int nb_rows = 4;
  int nb_cols = 6;
  game g = game_new_ext(nb_rows, nb_cols, squares, true, true);

  if (game_is_wrapping(g) != true || game_is_unique(g) != true ||
      game_nb_rows(g) != nb_rows || game_nb_cols(g) != nb_cols) {
    game_delete(g);
    return 1;
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 6; j++) {
      if (game_get_square(g, i, j) != squares[i * 6 + j]) {
        game_delete(g);
        return 1;
      }
    }
  }
  game_delete(g);
  return 0;
}

/*Test function game_new_empty_ext*/
int test_game_new_empty_ext() {
  game g = game_new_empty_ext(6, 4, true, true);
  if (game_nb_rows(g) != 6 || game_nb_cols(g) != 4 ||
      game_is_wrapping(g) != true || game_is_unique(g) != true) {
    game_delete(g);
    return 1;
  }

  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 4; j++) {
      if (game_get_square(g, i, j) != S_EMPTY) {
        game_delete(g);
        return 1;
      }
    }
  }
  return 0;
}

/*Test function game_new Empty*/
int test_game_new_empty() {
  game g = game_new_empty();
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    for (int j = 0; j < DEFAULT_SIZE; j++) {
      if (game_get_square(g, i, j) != S_EMPTY) {
        game_delete(g);
        return 1;
      }
    }
  }
  game_delete(g);
  return 0;
}

/*Test function game_is_wrapping*/
int test_game_is_wrapping() {
  game g = game_new_empty();
  game g2 = game_new_empty_ext(6, 6, true, true);
  if (game_is_wrapping(g) != false || game_is_wrapping(g2) != true) {
    game_delete(g);
    game_delete(g2);
    return 1;
  }
  game_delete(g);
  game_delete(g2);
  return 0;
}

/*Test function game_is_unique*/
int test_game_is_unique() {
  game g = game_new_empty();
  game g2 = game_new_empty_ext(6, 6, true, true);
  if (game_is_unique(g) != false || game_is_unique(g2) != true) {
    game_delete(g);
    game_delete(g2);
    return 1;
  }
  game_delete(g);
  game_delete(g2);
  return 0;
}

int test_game_nb_cols() {
  game g = game_new_empty();
  game g2 = game_new_empty_ext(8, 10, true, true);
  if (game_nb_cols(g) != 6 || game_nb_cols(g2) != 10) {
    game_delete(g);
    game_delete(g2);
    return 1;
  }
  game_delete(g);
  game_delete(g2);
  return 0;
}

int test_game_nb_rows() {
  game g = game_new_empty();
  game g2 = game_new_empty_ext(8, 10, true, true);
  if (game_nb_rows(g) != 6 || game_nb_rows(g2) != 8) {
    game_delete(g);
    game_delete(g2);
    return 1;
  }
  game_delete(g);
  game_delete(g2);
  return 0;
}

/*Test function game_copy*/
int test_game_copy() {
  game g1 = game_default();
  game g2 = game_copy(g1);
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    for (int j = 0; j < DEFAULT_SIZE; j++) {
      if (game_get_square(g1, i, j) != game_get_square(g2, i, j)) {
        game_delete(g1);
        game_delete(g2);
        return 1;
      }
    }
  }
  game_delete(g1);
  game_delete(g2);
  game g3 = game_new_empty_ext(4, 6, true, true);
  game g4 = game_copy(g3);
  if (game_is_wrapping(g4) != true || game_is_unique(g4) != true ||
      game_nb_rows(g4) != 4 || game_nb_cols(g4) != 6) {
    return 1;
  }
  for (int i = 0; i < game_nb_rows(g3); i++) {
    for (int j = 0; j < game_nb_cols(g3); j++) {
      if (game_get_square(g3, i, j) != game_get_square(g4, i, j)) {
        return 1;
      }
    }
  }
  game_delete(g3);
  game_delete(g4);
  return 0;
}

/*Test function game_equal*/
int test_game_equal() {
  game g1 = game_new_empty();
  square *squares =
      (square *)malloc((DEFAULT_SIZE * DEFAULT_SIZE) * sizeof(square));
  square *squares2 =
      (square *)malloc((DEFAULT_SIZE * DEFAULT_SIZE) * sizeof(square));
  for (int i = 0; i < (DEFAULT_SIZE * DEFAULT_SIZE); i++) {
    squares[i] = S_IMMUTABLE_ONE;
    squares2[i] = S_ONE;
  }
  game g3 = game_new(squares2);
  game g2 = game_new(squares);
  free(squares);
  free(squares2);
  if (game_equal(g1, g2) == true || game_equal(g2, g3) == true ||
      game_equal(g1, g3) == true || game_equal(g1, g1) != true) {
    game_delete(g1);
    game_delete(g2);
    game_delete(g3);
    return 1;
  }
  game_delete(g1);
  game_delete(g2);
  game_delete(g3);
  return 0;
}

/*Test function game_delete*/
int test_game_delete() {
  game g = game_default();
  assert(g);
  game_delete(g);
  assert(g != NULL);
  return 0;
}

/*Test function game_set_square*/
int test_game_set_square() {
  game g = game_new_empty();
  for (int i = 0; i < DEFAULT_SIZE; i++) {
    game_set_square(g, i, 0, S_IMMUTABLE_ONE);
    game_set_square(g, i, 1, S_ONE);
    if (game_get_square(g, i, 0) != S_IMMUTABLE_ONE ||
        game_get_square(g, i, 1) != S_ONE) {
      game_delete(g);
      return 1;
    }
  }

  game_delete(g);
  return 0;
}

/*Test function game_get_square*/
int test_game_get_square() {
  game g = game_new_empty();
  game_set_square(g, 0, 1, S_ONE);
  game_set_square(g, 0, 2, S_IMMUTABLE_ONE);
  game_set_square(g, 1, 0, S_ZERO);
  game_set_square(g, 1, 1, S_IMMUTABLE_ZERO);
  if (game_get_square(g, 0, 0) != S_EMPTY ||
      game_get_square(g, 0, 1) != S_ONE ||
      game_get_square(g, 0, 2) != S_IMMUTABLE_ONE ||
      game_get_square(g, 1, 0) != S_ZERO ||
      game_get_square(g, 1, 1) != S_IMMUTABLE_ZERO) {
    game_delete(g);
    return 1;
  }
  game_delete(g);
  return 0;
}

/*Test Dummy*/
int test_dummy() { return EXIT_SUCCESS; }

/*Main function*/
int main(int argc, char *argv[]) {
  if (argc == 1) {
    usage(argc, argv);
  }

  if (strcmp("dummy", argv[1]) == 0) {
    return test_dummy();
  } else if (strcmp("new_game_empty", argv[1]) == 0) {
    return test_game_new_empty();
  } else if (strcmp("game_delete", argv[1]) == 0) {
    return test_game_delete();
  } else if (strcmp("game_equal", argv[1]) == 0) {
    return test_game_equal();
  } else if (strcmp("game_copy", argv[1]) == 0) {
    return test_game_copy();
  } else if (strcmp("game_set_square", argv[1]) == 0) {
    return test_game_set_square();
  } else if (strcmp("game_get_square", argv[1]) == 0) {
    return test_game_get_square();
  } else if (strcmp("game_new", argv[1]) == 0) {
    return test_game_new();
  } else if (strcmp("game_is_wrapping", argv[1]) == 0) {
    return test_game_is_wrapping();
  } else if (strcmp("game_is_unique", argv[1]) == 0) {
    return test_game_is_unique();
  } else if (strcmp("game_new_empty_ext", argv[1]) == 0) {
    return test_game_new_empty_ext();
  } else if (strcmp("game_new_ext", argv[1]) == 0) {
    return test_game_new_ext();
  } else if (strcmp("game_nb_rows", argv[1]) == 0) {
    return test_game_nb_rows();
  } else if (strcmp("game_nb_cols", argv[1]) == 0) {
    return test_game_nb_cols();
  } else if (strcmp("game_redo", argv[1]) == 0) {
    return test_game_redo();
  } else {
    exit(EXIT_FAILURE);
  }
}