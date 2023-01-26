#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_struct.h"

// if choice == true : print le meme charactère c, sinon print i (donc 1,2,3,...
// etc)
void print_in_range(int range, char *c, bool choice) {
  for (int i = 0; i < range; i++) {
    if (choice) {
      printf("%s", c);
    } else {
      printf("%d", i);
    }
  }
  printf("\n");
}

void game_print(cgame g) {
  int nb_cols = game_nb_cols(g);
  int nb_rows = game_nb_rows(g);
  char *tab[5] = {" ", "w", "b", "W", "B"};
  printf("   ");
  print_in_range(nb_cols, "$", false);
  printf("   ");
  print_in_range(nb_cols, "-", true);
  for (int cpt_line = 0; cpt_line < nb_rows; cpt_line++) {
    printf("%d |", cpt_line);
    for (int cpt_col = 0; cpt_col < nb_cols; cpt_col++) {
      square s = game_get_square(g, cpt_line, cpt_col);
      printf("%s", tab[s]);
    }
    printf("|\n");
  }
  printf("   ");
  print_in_range(g->nb_cols, "-", true);
}

game game_default(void) {
  game g = game_new_empty_ext(6, 6, false, false);
  int B[3] = {1, 20, 26};
  int W[6] = {2, 13, 16, 19, 29, 35};
  square black = S_IMMUTABLE_ONE;
  square white = S_IMMUTABLE_ZERO;
  for (int i = 0; i < 3; i++) {
    game_set_square(g, B[i] / 6, B[i] % 6, black);
  }
  for (int i = 0; i < 6; i++) {
    game_set_square(g, W[i] / 6, W[i] % 6, white);
  }
  return g;
}

game game_default_solution(void) {
  game g = game_default();
  square b = S_ONE;
  square w = S_ZERO;
  game_play_move(g, 0, 0, w);
  game_play_move(g, 0, 3, b);
  game_play_move(g, 0, 4, w);
  game_play_move(g, 0, 5, b);
  game_play_move(g, 1, 0, w);
  game_play_move(g, 1, 1, b);
  game_play_move(g, 1, 2, b);
  game_play_move(g, 1, 3, w);
  game_play_move(g, 1, 4, b);
  game_play_move(g, 1, 5, w);
  game_play_move(g, 2, 0, b);
  game_play_move(g, 2, 2, w);
  game_play_move(g, 2, 3, b);
  game_play_move(g, 2, 5, b);
  game_play_move(g, 3, 0, b);
  game_play_move(g, 3, 3, w);
  game_play_move(g, 3, 4, w);
  game_play_move(g, 3, 5, b);
  game_play_move(g, 4, 0, w);
  game_play_move(g, 4, 1, b);
  game_play_move(g, 4, 3, w);
  game_play_move(g, 4, 4, b);
  game_play_move(g, 5, 0, b);
  game_play_move(g, 5, 1, w);
  game_play_move(g, 5, 2, w);
  game_play_move(g, 5, 3, b);
  game_play_move(g, 5, 4, b);
  return g;
}
