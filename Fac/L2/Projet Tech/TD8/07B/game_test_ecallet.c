#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_struct.h"

/* ********** ASSERT ********** */
#define ASSERT(expr)                                                          \
  do {                                                                        \
    if ((expr) == 0) {                                                        \
      fprintf(stderr, "[%s:%d] Assertion '%s' failed!\n", __FILE__, __LINE__, \
              #expr);                                                         \
      abort();                                                                \
    }                                                                         \
  } while (0)

/* Create a test game 3x3 with wanted parameters */
game set_game_test(bool wrapping, bool unique) {
  game g = game_new_empty_ext(4, 4, wrapping, unique);
  game_set_square(g, 0, 0, S_IMMUTABLE_ZERO);
  game_set_square(g, 0, 3, S_IMMUTABLE_ONE);
  game_set_square(g, 3, 0, S_ZERO);
  game_set_square(g, 3, 3, S_ONE);
  return (g);
}
/* *** TEST DUMMY *** */
int test_dummy() { return 0; }

/* *** TEST GET NUMBER *** */
int test_get_number() {
  game g = game_default();
  square s = S_ZERO;
  game_play_move(g, 0, 0, s);
  s = S_ONE;
  game_play_move(g, 0, 3, s);
  if (game_get_number(g, 0, 0) != 0 || game_get_number(g, 0, 1) != 1 ||
      game_get_number(g, 0, 2) != 0 || game_get_number(g, 0, 3) != 1 ||
      game_get_number(g, 0, 4) != -1) {
    game_delete(g);
    return 1;
  } else {
    game_delete(g);
    return 0;
  }
}

/* *** TEST GET NEXT SQUARE *** */
int test_get_next_square() {
  game g = set_game_test(false, false);
  if (game_get_next_square(g, 0, 0, RIGHT, 0) != S_IMMUTABLE_ZERO ||
      game_get_next_square(g, 0, 2, LEFT, 0) != S_EMPTY ||
      game_get_next_square(g, 2, 3, UP, 2) != S_IMMUTABLE_ONE ||
      game_get_next_square(g, 3, 0, DOWN, 2) != -1 ||
      game_get_next_square(g, 0, 2, UP, 1) != -1 ||
      game_get_next_square(g, 3, 0, LEFT, 2) != -1 ||
      game_get_next_square(g, 3, 3, RIGHT, 1) != -1) {
    game_delete(g);
    return -1;
  }
  game_delete(g);
  return 0;
}

/* *** TEST GET NEXT SQUARE *** */
int test_get_next_square_wrapping() {
  game g = set_game_test(true, false);
  if (game_get_next_square(g, 0, 0, RIGHT, 0) != S_IMMUTABLE_ZERO ||
      game_get_next_square(g, 0, 2, LEFT, 0) != S_EMPTY ||
      game_get_next_square(g, 2, 3, UP, 2) != S_IMMUTABLE_ONE ||
      game_get_next_square(g, 3, 0, DOWN, 2) != S_EMPTY ||
      game_get_next_square(g, 3, 0, DOWN, 1) != S_IMMUTABLE_ZERO ||
      game_get_next_square(g, 0, 0, UP, 1) != S_ZERO ||
      game_get_next_square(g, 0, 2, UP, 1) != S_EMPTY ||
      game_get_next_square(g, 0, 3, UP, 1) != S_ONE ||
      game_get_next_square(g, 0, 0, LEFT, 1) != S_IMMUTABLE_ONE ||
      game_get_next_square(g, 1, 0, LEFT, 1) != S_EMPTY ||
      game_get_next_square(g, 1, 3, RIGHT, 1) != S_EMPTY ||
      game_get_next_square(g, 3, 3, RIGHT, 1) != S_ZERO) {
    game_delete(g);
    return 1;
  }
  game_delete(g);
  return 0;
}

/* *** TEST CHECK MOVE *** */
int test_check_move() {
  game g = game_default();

  if (game_check_move(g, 7, 8, S_ONE) != false ||
      game_check_move(g, 0, 0, S_ZERO) != true ||
      game_check_move(g, 0, 0, S_ONE) != true ||
      game_check_move(g, 0, 0, S_EMPTY) != true ||
      game_check_move(g, 0, 1, S_ONE) != false ||
      game_check_move(g, 0, 2, S_ZERO) != false ||
      game_check_move(g, 0, 0, S_IMMUTABLE_ONE) != false ||
      game_check_move(g, 0, 1, S_IMMUTABLE_ZERO) != false) {
    game_delete(g);
    return 1;
  } else {
    game_delete(g);
    return 0;
  }
}

/* *** TEST GET NEXT NUMBER *** */
int test_get_next_number() {
  game g = set_game_test(false, false);
  if (game_get_next_number(g, 0, 0, RIGHT, 0) != 0 ||
      game_get_next_number(g, 0, 2, LEFT, 0) != -1 ||
      game_get_next_number(g, 2, 3, UP, 2) != 1 ||
      game_get_next_number(g, 3, 0, DOWN, 2) != -1 ||
      game_get_next_number(g, 0, 2, UP, 1) != -1) {
    game_delete(g);
    return 1;
  }
  game_delete(g);
  return 0;
}

/* *** TEST GET NEXT NUMBER WRAPPING *** */
int test_get_next_number_wrapping() {
  game g = set_game_test(true, false);
  if (game_get_next_number(g, 0, 0, RIGHT, 0) != 0 ||
      game_get_next_number(g, 0, 2, LEFT, 0) != -1 ||
      game_get_next_number(g, 2, 3, UP, 2) != 1 ||
      game_get_next_number(g, 3, 0, DOWN, 2) != -1 ||
      game_get_next_number(g, 3, 0, DOWN, 1) != 0 ||
      game_get_next_number(g, 0, 2, UP, 1) != -1 ||
      game_get_next_number(g, 0, 3, UP, 1) != 1 ||
      game_get_next_number(g, 0, 0, LEFT, 1) != 1 ||
      game_get_next_number(g, 1, 0, LEFT, 1) != -1 ||
      game_get_next_number(g, 1, 3, RIGHT, 1) != -1 ||
      game_get_next_number(g, 3, 3, RIGHT, 1) != 0) {
    game_delete(g);
    return 1;
  }
  game_delete(g);
  return 0;
}

/* *** TEST IS EMPTY *** */
int test_is_empty() {
  game g = game_default();
  square s = S_ZERO;
  game_play_move(g, 0, 0, s);
  s = S_ONE;
  game_play_move(g, 0, 3, s);
  if (game_is_empty(g, 0, 0) != false || game_is_empty(g, 0, 1) != false ||
      game_is_empty(g, 0, 2) != false || game_is_empty(g, 0, 3) != false ||
      game_is_empty(g, 0, 4) != true) {
    game_delete(g);
    return 1;
  } else {
    game_delete(g);
    return 0;
  }
}

/* *** TEST IS IMMUTABLE *** */
int test_is_immutable() {
  game g = game_default();
  square s = S_ZERO;
  game_play_move(g, 0, 0, s);
  s = S_ONE;
  game_play_move(g, 0, 3, s);
  if (game_is_immutable(g, 0, 0) != false ||
      game_is_immutable(g, 0, 1) != true ||
      game_is_immutable(g, 0, 2) != true ||
      game_is_immutable(g, 0, 3) != false ||
      game_is_immutable(g, 0, 4) != false) {
    game_delete(g);
    return 1;
  } else {
    game_delete(g);
    return 0;
  }
}

/* *** TEST HAS ERROR *** */
int test_has_error() {
  game g = game_default();
  game_play_move(g, 1, 1, S_ZERO);
  game_play_move(g, 5, 2, S_ONE);
  game_play_move(g, 0, 3, S_ZERO);
  game_play_move(g, 0, 4, S_ZERO);
  if (game_has_error(g, 0, 0) != 0 || game_has_error(g, 0, 1) != 0 ||
      game_has_error(g, 1, 1) == 0 || game_has_error(g, 5, 2) == 0 ||
      game_has_error(g, 0, 3) == 0 || game_has_error(g, 0, 4) == 0) {
    game_delete(g);
    return 1;
  }
  game_delete(g);
  square test[32] = {S_ZERO, S_ZERO, S_ONE,  S_ONE, S_ZERO, S_ONE,  S_ONE,
                     S_ZERO, S_ZERO, S_ZERO, S_ONE, S_ONE,  S_ZERO, S_ONE,
                     S_ONE,  S_ZERO, S_ONE,  S_ONE, S_ZERO, S_ZERO, S_ONE,
                     S_ZERO, S_ZERO, S_ONE,  S_ONE, S_ONE,  S_ZERO, S_ZERO,
                     S_ONE,  S_ZERO, S_ZERO, S_ONE};
  game g2 = game_new_ext(4, 8, test, false, true);
  if (game_has_error(g2, 1, 0) == false) {
    game_delete(g2);
    return 1;
  }
  game_delete(g2);
  return 0;
}

/* *** TEST HAS ERROR WRAPPING*** */
int test_has_error_wrapping() {
  game g = set_game_test(true, false);
  game_play_move(g, 1, 0, S_ZERO);  // W   w B
  game_play_move(g, 1, 3, S_ZERO);  // w
  game_play_move(g, 0, 2, S_ZERO);  //       b
  game_play_move(g, 3, 2, S_ZERO);  // w b w b
  game_play_move(g, 2, 3, S_ONE);
  game_play_move(g, 3, 1, S_ONE);
  if (game_has_error(g, 0, 0) != -1 || game_has_error(g, 1, 0) != -1 ||
      game_has_error(g, 3, 0) != -1 || game_has_error(g, 2, 3) != -1 ||
      game_has_error(g, 3, 3) != -1 || game_has_error(g, 0, 2) != 0 ||
      game_has_error(g, 3, 1) != 0 || game_has_error(g, 3, 2) != 0) {
    game_delete(g);
    return 1;
  }                                 // W   w B
  game_play_move(g, 1, 1, S_ZERO);  // w w   w
  game_play_move(g, 1, 3, S_ZERO);  //       b
                                    // b b w b
  if (game_has_error(g, 1, 0) != -1 || game_has_error(g, 1, 1) != -1 ||
      game_has_error(g, 1, 3) != -1 || game_has_error(g, 3, 0) != -1 ||
      game_has_error(g, 3, 3) != -1) {
    game_delete(g);
    return 1;
  }

  game_delete(g);
  return 0;
}

/* *** TEST HAS ERROR UNIQUE*** */
int test_has_error_unique() {
  game g = game_new_empty_ext(6, 6, false, true);
  game_play_move(g, 0, 0, S_ZERO);
  game_play_move(g, 0, 1, S_ZERO);
  game_play_move(g, 0, 3, S_ZERO);
  game_play_move(g, 0, 4, S_ZERO);
  game_play_move(g, 0, 2, S_ONE);
  game_play_move(g, 1, 2, S_ONE);
  game_play_move(g, 3, 2, S_ONE);
  game_play_move(g, 4, 2, S_ONE);
  if (game_has_error(g, 0, 0) != -1 || game_has_error(g, 0, 1) != -1 ||
      game_has_error(g, 0, 2) != -1 || game_has_error(g, 3, 2) != -1) {
    game_delete(g);
    return 1;
  }
  game_delete(g);
  game g_diff_lines = game_new_empty_ext(4, 4, false, true);
  game_play_move(g_diff_lines, 0, 0, S_ZERO);
  game_play_move(g_diff_lines, 0, 2, S_ZERO);
  game_play_move(g_diff_lines, 1, 0, S_ZERO);
  game_play_move(g_diff_lines, 1, 1, S_ZERO);
  game_play_move(g_diff_lines, 2, 1, S_ZERO);
  game_play_move(g_diff_lines, 2, 3, S_ZERO);
  game_play_move(g_diff_lines, 3, 2, S_ZERO);
  game_play_move(g_diff_lines, 3, 3, S_ZERO);
  game_play_move(g_diff_lines, 0, 1, S_ONE);
  game_play_move(g_diff_lines, 0, 3, S_ONE);
  game_play_move(g_diff_lines, 1, 2, S_ONE);
  game_play_move(g_diff_lines, 1, 3, S_ONE);
  game_play_move(g_diff_lines, 2, 0, S_ONE);
  game_play_move(g_diff_lines, 2, 2, S_ONE);
  game_play_move(g_diff_lines, 3, 0, S_ONE);
  game_play_move(g_diff_lines, 3, 1, S_ONE);
  if (game_has_error(g, 0, 0) != 0) {
    game_delete(g_diff_lines);
    return -1;
  }
  game_delete(g_diff_lines);
  game g_same_lines = game_new_empty_ext(4, 4, true, true);
  game_play_move(g_same_lines, 0, 1, S_ZERO);
  game_play_move(g_same_lines, 0, 3, S_ZERO);
  game_play_move(g_same_lines, 1, 1, S_ZERO);
  game_play_move(g_same_lines, 1, 3, S_ZERO);
  game_play_move(g_same_lines, 2, 0, S_ZERO);
  game_play_move(g_same_lines, 2, 2, S_ZERO);
  game_play_move(g_same_lines, 3, 0, S_ZERO);
  game_play_move(g_same_lines, 3, 2, S_ZERO);
  game_play_move(g_same_lines, 0, 0, S_ONE);
  game_play_move(g_same_lines, 0, 2, S_ONE);
  game_play_move(g_same_lines, 1, 0, S_ONE);
  game_play_move(g_same_lines, 1, 2, S_ONE);
  game_play_move(g_same_lines, 2, 1, S_ONE);
  game_play_move(g_same_lines, 2, 3, S_ONE);
  game_play_move(g_same_lines, 3, 1, S_ONE);
  game_play_move(g_same_lines, 3, 3, S_ONE);
  if (game_has_error(g, 0, 0) != -1) {
    game_delete(g_same_lines);
    return -1;
  }

  game_delete(g_same_lines);
  return 0;
}

/* *** TEST UNDO *** */
int test_undo() {
  game g = set_game_test(false, false);
  game g2 = set_game_test(false, false);
  game g3 = set_game_test(false, false);
  game_play_move(g2, 0, 1, S_ONE);
  game_undo(g2);
  game_play_move(g2, 1, 1, S_ZERO);
  game_play_move(g2, 2, 1, S_ONE);
  game_undo(g2);
  game_undo(g2);
  game_redo(g2);
  game_undo(g2);
  game_undo(g);
  if (game_equal(g, g2) == false || game_equal(g, g3) == false) {
    game_delete(g);
    game_delete(g2);
    game_delete(g3);
    return 1;
  } else {
    game_delete(g);
    game_delete(g2);
    game_delete(g3);
    return 0;
  }
}

/* *** TEST GAME_NEW_EXT COMME MOODLE *** */
int test_game_new_ext_moodle() {
  square squares[8] = {S_EMPTY, S_IMMUTABLE_ONE,  S_IMMUTABLE_ZERO, S_ONE,
                       S_ZERO,  S_IMMUTABLE_ZERO, S_EMPTY,          S_ONE};
  int nb_rows = 4;
  int nb_cols = 2;
  game g = game_new_ext(4, 2, squares, true, true);
  if (game_is_unique(g) != true || game_is_wrapping(g) != true ||
      game_nb_rows(g) != nb_rows || game_nb_cols(g) != nb_cols) {
    game_delete(g);
    return 1;
  }
  for (int i = 0; i < nb_rows; i++) {
    for (int j = 0; j < nb_cols; j++) {
      if (game_get_square(g, i, j) != squares[i * nb_cols + j]) {
        game_delete(g);
        return 1;
      }
    }
  }
  game_delete(g);
  return 0;
}

/* *** TEST IS OVER UNIQUE *** */
int test_is_over_unique() {
  game g_diff_lines = game_new_empty_ext(4, 4, false, true);
  game_play_move(g_diff_lines, 0, 0, S_ZERO);
  game_play_move(g_diff_lines, 0, 2, S_ZERO);
  game_play_move(g_diff_lines, 1, 0, S_ZERO);
  game_play_move(g_diff_lines, 1, 1, S_ZERO);
  game_play_move(g_diff_lines, 2, 1, S_ZERO);
  game_play_move(g_diff_lines, 2, 3, S_ZERO);
  game_play_move(g_diff_lines, 3, 2, S_ZERO);
  game_play_move(g_diff_lines, 3, 3, S_ZERO);
  game_play_move(g_diff_lines, 0, 1, S_ONE);
  game_play_move(g_diff_lines, 0, 3, S_ONE);
  game_play_move(g_diff_lines, 1, 2, S_ONE);
  game_play_move(g_diff_lines, 1, 3, S_ONE);
  game_play_move(g_diff_lines, 2, 0, S_ONE);
  game_play_move(g_diff_lines, 2, 2, S_ONE);
  game_play_move(g_diff_lines, 3, 0, S_ONE);
  game_play_move(g_diff_lines, 3, 1, S_ONE);
  if (game_is_over(g_diff_lines) == false) {
    game_delete(g_diff_lines);
    return 1;
  }
  game g_same_lines = game_new_empty_ext(4, 4, true, true);
  game_play_move(g_same_lines, 0, 1, S_ZERO);
  game_play_move(g_same_lines, 0, 3, S_ZERO);
  game_play_move(g_same_lines, 1, 1, S_ZERO);
  game_play_move(g_same_lines, 1, 3, S_ZERO);
  game_play_move(g_same_lines, 2, 0, S_ZERO);
  game_play_move(g_same_lines, 2, 2, S_ZERO);
  game_play_move(g_same_lines, 3, 0, S_ZERO);
  game_play_move(g_same_lines, 3, 2, S_ZERO);
  game_play_move(g_same_lines, 0, 0, S_ONE);
  game_play_move(g_same_lines, 0, 2, S_ONE);
  game_play_move(g_same_lines, 1, 0, S_ONE);
  game_play_move(g_same_lines, 1, 2, S_ONE);
  game_play_move(g_same_lines, 2, 1, S_ONE);
  game_play_move(g_same_lines, 2, 3, S_ONE);
  game_play_move(g_same_lines, 3, 1, S_ONE);
  game_play_move(g_same_lines, 3, 3, S_ONE);
  if (game_is_over(g_same_lines)) {
    game_delete(g_diff_lines);
    game_delete(g_same_lines);
    return 1;
  }
  game_delete(g_diff_lines);
  game_delete(g_same_lines);
  return 0;
}

/* ********** USAGE ********** */

void usage(int argc, char *argv[]) {
  fprintf(stderr, "Usage: %s <testname> [<...>]\n", argv[0]);
  exit(EXIT_FAILURE);
}

/* ********** MAIN ROUTINE ********** */

int main(int argc, char *argv[]) {
  if (argc == 1) usage(argc, argv);

  // start test
  fprintf(stderr, "=> Start test \"%s\"\n", argv[1]);
  int ok = 1;
  if (strcmp("dummy", argv[1]) == 0) {
    ok = test_dummy();
  }
  if (strcmp("get_number", argv[1]) == 0) {
    ok = test_get_number();
  }
  if (strcmp("get_next_square", argv[1]) == 0) {
    ok = test_get_next_square();
  }
  if (strcmp("get_next_square_wrapping", argv[1]) == 0) {
    ok = test_get_next_square_wrapping();
  }
  if (strcmp("check_move", argv[1]) == 0) {
    ok = test_check_move();
  }
  if (strcmp("get_next_number", argv[1]) == 0) {
    ok = test_get_next_number();
  }
  if (strcmp("get_next_number_wrapping", argv[1]) == 0) {
    ok = test_get_next_number_wrapping();
  }
  if (strcmp("is_empty", argv[1]) == 0) {
    ok = test_is_empty();
  }
  if (strcmp("is_immutable", argv[1]) == 0) {
    ok = test_is_immutable();
  }
  if (strcmp("has_error", argv[1]) == 0) {
    ok = test_has_error();
  }
  if (strcmp("has_error_wrapping", argv[1]) == 0) {
    ok = test_has_error_wrapping();
  }
  if (strcmp("has_error_unique", argv[1]) == 0) {
    ok = test_has_error_unique();
  }
  if (strcmp("undo", argv[1]) == 0) {
    ok = test_undo();
  }
  if (strcmp("game_new_ext_moodle", argv[1]) == 0) {
    ok = test_game_new_ext_moodle();
  }
  if (strcmp("is_over_unique", argv[1]) == 0) {
    ok = test_is_over_unique();
  }

  if (ok == 0) {
    fprintf(stderr, "Test \"%s\" finished: SUCCESS\n", argv[1]);
    return EXIT_SUCCESS;
  }

  else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }
}
