#define __USE_GNU
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"

/* ********** ASSERT ********** */
#define assert(expr)                                                          \
  do {                                                                        \
    if ((expr) == 0) {                                                        \
      fprintf(stderr, "[%s:%d] Assertion '%s' failed!\n", __FILE__, __LINE__, \
              #expr);                                                         \
      abort();                                                                \
    }                                                                         \
  } while (0)

square mesSquares[] = {S_EMPTY, S_ONE,   S_EMPTY, S_ONE,   S_ZERO,  S_EMPTY,
                       S_ONE,   S_EMPTY, S_ONE,   S_ZERO,  S_ONE,   S_EMPTY,
                       S_EMPTY, S_EMPTY, S_ONE,   S_EMPTY, S_EMPTY, S_ZERO,
                       S_ONE,   S_ZERO,  S_ZERO,  S_ONE,   S_EMPTY, S_EMPTY};

square mesSquares1[] = {
    S_EMPTY, S_EMPTY, S_EMPTY, S_ONE,   S_ZERO,          S_EMPTY,
    S_ONE,   S_EMPTY, S_ONE,   S_ZERO,  S_EMPTY,         S_EMPTY,
    S_EMPTY, S_ONE,   S_EMPTY, S_ONE,   S_IMMUTABLE_ONE, S_IMMUTABLE_ZERO,
    S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_ONE,           S_ONE,
    S_EMPTY, S_EMPTY, S_EMPTY, S_ONE,   S_ZERO,          S_ZERO,
    S_ONE,   S_ZERO,  S_ONE,   S_ONE,   S_IMMUTABLE_ONE, S_EMPTY,
};

int test_dummy() { return 0; }

int test_game_print(void) {
  game g = game_default();
  game_print(g);
  game_delete(g);
  return EXIT_SUCCESS;
}

int test_game_default() {
  game test = game_default();

  square testsquares[6][6] = {
      {S_EMPTY, S_IMMUTABLE_ONE, S_IMMUTABLE_ZERO, S_EMPTY, S_EMPTY, S_EMPTY},
      {S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY},
      {S_EMPTY, S_IMMUTABLE_ZERO, S_EMPTY, S_EMPTY, S_IMMUTABLE_ZERO, S_EMPTY},
      {S_EMPTY, S_IMMUTABLE_ZERO, S_IMMUTABLE_ONE, S_EMPTY, S_EMPTY, S_EMPTY},
      {S_EMPTY, S_EMPTY, S_IMMUTABLE_ONE, S_EMPTY, S_EMPTY, S_IMMUTABLE_ZERO},
      {S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_IMMUTABLE_ZERO}};

  for (int i = 0; i < DEFAULT_SIZE; ++i) {
    for (int j = 0; j < DEFAULT_SIZE; ++j) {
      if (game_get_square(test, i, j) != testsquares[i][j]) {
        game_delete(test);
        return 1;
      }
    }
  }
  game_delete(test);
  return 0;
}

int test_game_default_solution(void) {
  game test = game_default_solution();
  game_print(test);
  square testsquares1[6][6] = {
      {S_ZERO, S_IMMUTABLE_ONE, S_IMMUTABLE_ZERO, S_ONE, S_ZERO, S_ONE},
      {S_ZERO, S_ONE, S_ONE, S_ZERO, S_ONE, S_ZERO},
      {S_ONE, S_IMMUTABLE_ZERO, S_ZERO, S_ONE, S_IMMUTABLE_ZERO, S_ONE},
      {S_ONE, S_IMMUTABLE_ZERO, S_IMMUTABLE_ONE, S_ZERO, S_ZERO, S_ONE},
      {S_ZERO, S_ONE, S_IMMUTABLE_ONE, S_ZERO, S_ONE, S_IMMUTABLE_ZERO},
      {S_ONE, S_ZERO, S_ZERO, S_ONE, S_ONE, S_IMMUTABLE_ZERO}};

  for (int i = 0; i < DEFAULT_SIZE; ++i) {
    for (int j = 0; j < DEFAULT_SIZE; ++j) {
      if (game_get_square(test, i, j) != testsquares1[i][j]) {
        game_delete(test);
        return 1;
      }
    }
  }
  game_delete(test);
  return 0;
}

int test_game_is_over() {
  // avec default game
  game g0 = game_default();
  bool test0 = game_is_over(g0) == false;
  game_delete(g0);

  // avec game default solution
  game g1 = game_default_solution();
  bool test1 = (game_is_over(g1) == true);
  game g2 = game_default_solution();
  bool test2 = game_equal(g1, g2);

  game_delete(g1);
  game_delete(g2);

  // avec game new empty
  game g3 = game_new_empty();
  game_play_move(g3, 0, 0, S_ZERO);
  game_play_move(g3, 0, 1, S_ZERO);
  game_play_move(g3, 0, 2, S_ZERO);
  bool test3 = (game_is_over(g3) == false);
  game_play_move(g3, 0, 0, S_ONE);
  game_play_move(g3, 1, 0, S_ONE);
  game_play_move(g3, 2, 0, S_ONE);
  bool test4 = (game_is_over(g3) == false);
  game_delete(g3);

  if (test0 && test1 && test2 && test3 && test4) return 0;
  // if(game_is_wrapping(g3) && game_is_unique(g3)) return 0;

  return 1;
}

int test_game_play_move() {
  game test = game_new_empty();
  for (int i = 0; i < DEFAULT_SIZE; ++i) {
    game_play_move(test, 0, i, S_ONE);
    if (game_get_square(test, 0, i) != S_ONE) {
      game_delete(test);
      return 1;
    }
    game_play_move(test, 1, i, S_ZERO);
    if (game_get_square(test, 1, i) != S_ZERO) {
      game_delete(test);
      return 1;
    }
    game_play_move(test, 2, i, S_EMPTY);
    if (game_get_square(test, 2, i) != S_EMPTY) {
      game_delete(test);
      return 1;
    }
    game_play_move(test, i, 1, S_ONE);
    if (game_get_square(test, i, 1) != S_ONE) {
      game_delete(test);
      return 1;
    }
    game_play_move(test, i, 2, S_ZERO);
    if (game_get_square(test, i, 2) != S_ZERO) {
      game_delete(test);
      return 1;
    }
    game_play_move(test, i, 3, S_EMPTY);
    if (game_get_square(test, i, 3) != S_EMPTY) {
      game_delete(test);
      return 1;
    }
  }
  game_delete(test);
  return 0;
}

int test_game_restart() {
  square defaultSquares[6][6] = {
      {S_EMPTY, S_ONE, S_ZERO, S_EMPTY, S_EMPTY, S_EMPTY},
      {S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY},
      {S_EMPTY, S_ZERO, S_EMPTY, S_EMPTY, S_ZERO, S_EMPTY},
      {S_EMPTY, S_ZERO, S_ONE, S_EMPTY, S_EMPTY, S_EMPTY},
      {S_EMPTY, S_EMPTY, S_ONE, S_EMPTY, S_EMPTY, S_ZERO},
      {S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_EMPTY, S_ZERO}};

  game g = game_default_solution();
  game_restart(g);
  for (uint i = 0; i < DEFAULT_SIZE; i++) {
    for (uint j = 0; j < DEFAULT_SIZE; j++) {
      if (game_get_square(g, i, j) != defaultSquares[i][j]) {
        return 1;
      }
    }
  }
  game_delete(g);

  game g1 = game_new(mesSquares1);
  game_restart(g1);
  for (uint i = 0; i < DEFAULT_SIZE; i++) {
    for (uint j = 0; j < DEFAULT_SIZE; j++) {
      if (game_get_square(g1, i, j) != defaultSquares[i][j]) {
        return 1;
      }
    }
  }
  game_delete(g1);
  game g2 = game_new_empty_ext(4, 4, false, true);
  game_restart(g2);
  for (uint i = 0; i < DEFAULT_SIZE; i++) {
    for (uint j = 0; j < DEFAULT_SIZE; j++) {
      if (game_get_square(g2, i, j) != defaultSquares[i][j]) {
        return 1;
      }
    }
  }
  game_delete(g2);
  game g3 = game_copy(g2);
  game_play_move(g2, 0, 0, S_ZERO);
  game_undo(g2);
  game_restart(g2);
  game_redo(g2);
  if (game_equal(g2, g3) == false) {
    game_delete(g2);
    game_delete(g3);
    return 1;
  }
  game_delete(g2);
  game_delete(g3);

  return 0;
}

int test_game_equal_ext(void) {
  game g1 = game_new_ext(4, 6, mesSquares, false, false);
  game g2 = game_new_ext(4, 6, mesSquares, false, false);
  game g3 = game_new_ext(4, 6, mesSquares, true, true);
  game g4 = game_new_ext(6, 4, mesSquares, true, true);

  bool test1 = (game_equal(g1, g2) == true);
  bool test2 = (game_equal(g1, g3) == false);
  bool test3 = (game_equal(g3, g4) == false);
  /*
    game_set_square(g2, 2, 5, S_ZERO);
    bool test3 = (game_equal(g1, g2) == false);
  */
  game_delete(g1);
  game_delete(g2);
  game_delete(g3);
  game_delete(g4);

  if ((test1 && test2) && test3) return 0;
  return 1;
}

int test_game_is_over_unique() {
  square test[32] = {S_ZERO, S_ZERO, S_ONE,  S_ONE, S_ZERO, S_ONE,  S_ONE,
                     S_ZERO, S_ZERO, S_ZERO, S_ONE, S_ONE,  S_ZERO, S_ONE,
                     S_ONE,  S_ZERO, S_ONE,  S_ONE, S_ZERO, S_ZERO, S_ONE,
                     S_ZERO, S_ZERO, S_ONE,  S_ONE, S_ONE,  S_ZERO, S_ZERO,
                     S_ONE,  S_ZERO, S_ZERO, S_ONE};
  game g = game_new_ext(4, 8, test, false, true);
  if (game_is_over(g) == true) {
    game_delete(g);
    return 1;
  }
  game_delete(g);
  return 0;
}

int test_game_is_over_wrapping() {
  game g0 = game_new_ext(6, 4, mesSquares, true, true);
  bool test0 = (game_is_wrapping(g0) == true);
  game_play_move(g0, 1, 1, S_ONE);
  game_play_move(g0, 2, 0, S_ONE);
  game_play_move(g0, 3, 2, S_ONE);
  bool test1 = (game_is_wrapping(g0) == true);
  bool test2 = (game_is_wrapping(g0) == true);
  game_delete(g0);
  if (test0 != true || test1 != true || test2 != true) return 1;

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

  else if (strcmp("game_print", argv[1]) == 0) {
    ok = test_game_print();
  }

  else if (strcmp("game_default", argv[1]) == 0) {
    ok = test_game_default();
  } else if (strcmp("game_default_solution", argv[1]) == 0) {
    ok = test_game_default_solution();
  }

  else if (strcmp("game_is_over", argv[1]) == 0) {
    ok = test_game_is_over();
  } else if (strcmp("game_is_over_unique", argv[1]) == 0) {
    ok = test_game_is_over_unique();
  } else if (strcmp("game_is_over_wrapping", argv[1]) == 0) {
    ok = test_game_is_over_wrapping();
  }

  else if (strcmp("game_restart", argv[1]) == 0) {
    ok = test_game_restart();
  } else if (strcmp("game_play_move", argv[1]) == 0) {
    ok = test_game_play_move();
  }

  else if (strcmp("game_equal_ext", argv[1]) == 0) {
    ok = test_game_equal_ext();
  }

  else {
    fprintf(stderr, "Test \"%s\" finished: FAILURE\n", argv[1]);
    return EXIT_FAILURE;
  }

  return ok;

  return EXIT_SUCCESS;
}
