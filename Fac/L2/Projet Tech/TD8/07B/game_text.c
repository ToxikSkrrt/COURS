#include <stdio.h>
#include <stdlib.h>

#include "game_aux.h"
#include "game_ext.h"
#include "game_struct.h"
#include "queue.h"

int main(void) {
  game g = game_new_empty_ext(10, 6, true, false);
  char c;
  bool quit = false;
  while (game_is_over(g) == 0) {  // game is running
    if (quit) {
      break;
    }  // vérification que le joueur n'as pas quitté la partie
    game_print(g);
    unsigned int i, j;
    printf("*** votre coup ? ***\n");
    scanf(" %c", &c);
    switch (c) {
      case 'h':
        printf("*******************\n");
        printf("*** page d'aide ***\n");
        printf("*******************\n");
        break;

      case 'r':
        printf("|| réinitialisation de la grille ||\n");
        game_restart(g);
        break;

      case 'q':
        printf("|| Vous venez de quitter la partie ||\n");
        quit = true;  // variable indiquant que le joueur quitte la partie
        break;

      case 'z':
        if (queue_is_empty(g->q_undo)) /*verif juste pour afficher le texte*/ {
          printf("|| Vous n'avez pas de coup à annuler ||\n");
        } else {
          game_undo(g);
        }
        break;

      case 'y':
        if (queue_is_empty(g->q_redo)) /*verif juste pour afficher le texte*/ {
          printf("|| Vous n'avez pas de coup annulé à rejouer ||\n");
        } else {
          game_redo(g);
        }
        break;

      case 'w':
      case 'b':
      case 'e':

        printf("|| Veuillez rentrer la ligne de votre coup ||\n");
        scanf(" %d", &i);

        printf("|| Veuillez rentrer la colonne de votre coup ||\n");
        scanf(" %d", &j);
        square s;
        switch (c) {
          case 'w':
            s = S_ZERO;
            break;

          case 'b':
            s = S_ONE;
            break;

          case 'e':
            s = S_EMPTY;
            break;
        }

        if (game_check_move(g, i, j, s) == false) {
          printf(
              "|| Vous ne pouvez pas jouer votre coup en position %d / %d  "
              "||\n",
              i, j);
        } else {
          game_play_move(g, i, j, s);
          queue_clear_full(g->q_redo, free);
        }
        break;

      default:
        printf("|| Vous n'avez pas rentré une instruction valide ||\n");
        break;
    }
  }

  if (game_is_over(g) == 0) {
    printf("shame\n");
  } else {
    printf("congratulation\n");
  }
  game_print(g);
  game_delete(g);
  // end of the programm to keep
  return (EXIT_SUCCESS);
}
