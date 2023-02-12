#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_aux.h"
#include "game_ext.h"

/**
 * @brief Prints all the errors detected in a game.
 *
 * @param g the game
 */
void print_error_list(cgame g) {
    for (uint i = 0; i < DEFAULT_SIZE; i++) {
        for (uint j = 0; j < DEFAULT_SIZE; j++) {
            if (game_has_error(g, i, j)) {
                printf("Error at square (%u,%u)\n", i, j);
            }
        }
    }
}

/**
 * @brief Prints the help text.
 */
void print_help(void) {
    printf("- press 'w <i> <j>' to put a zero/white at square (i,j)\n");
    printf("- press 'b <i> <j>' to put a one/black at square (i,j)\n");
    printf("- press 'e <i> <j>' to empty square (i,j)\n");
    printf("- press 'z' to undo a move\n");
    printf("- press 'y' to redo a move\n");
    printf("- press 'r' to restart\n");
    printf("- press 'q' to quit\n");
}

int main(void) {
    game g = game_default();

    while (!game_is_over(g)) {
        game_print(g);
        print_error_list(g);
        printf("? [h for help]\n");
        char letter;
        int ret = scanf(" %c", &letter);
        if (ret == 1) {
            if (letter == 'h') {
                printf("action: help\n");
                print_help();

            } else if (letter == 'r') {
                printf("action: restart\n");
                game_restart(g);

            } else if (letter == 'q') {
                printf("action: quit\n");
                printf("shame on you for giving up (you lost)\n");
                game_delete(g);
                return EXIT_SUCCESS;

            } else if (letter == 'z') {
                printf("action: undo\n");
                game_undo(g);

            } else if (letter == 'y') {
                printf("action: redo\n");
                game_redo(g);

            } else if (letter == 'w' || letter == 'b' || letter == 'e') {
                int row, column;
                ret = scanf("%d %d", &row, &column);
                if (ret == 2) {
                    printf("action: play move '%c' into square (%d,%d)\n",
                           letter, row, column);
                    int square_value;
                    if (letter == 'w') {
                        square_value = S_ZERO;

                    } else if (letter == 'b') {
                        square_value = S_ONE;

                    } else if (letter == 'e') {
                        square_value = S_EMPTY;
                    }

                    if (game_check_move(g, row, column, square_value)) {
                        game_play_move(g, row, column, square_value);
                    } else {
                        printf("invalid move !\n");
                    }
                }

            } else {
                printf("'%c' is an invalid command\n", letter);
            }
        }
    }
    game_print(g);
    printf("you won ! you get one congratulation (yes, only one)\n");
    game_delete(g);

    return EXIT_SUCCESS;
}