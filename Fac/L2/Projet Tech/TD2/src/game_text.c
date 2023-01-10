#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_aux.h"

int main (void)
{
    game g = game_default();
    char c;
    int i;
    int j;
    while (!game_is_over(g))
    {
        game_print(g);
        for (int k = 0; k < DEFAULT_SIZE; k++)
        {
            for (int l = 0; l < DEFAULT_SIZE; l++)
            {
                if (game_has_error(g, k, l))
                {
                    printf("Error at square (%d, %d)\n", k, l);
                }
            }
        }
        printf("? [h for help]\n");
        scanf(" %c", &c);
        if (c == 'h')
        {
            printf("action : help\n- press 'w <i> <j>' to put a zero/white at square (i, j)\n- press 'b <i> <j>' to put a one/black at square (i, j)\n- press 'e <i> <j>' to empty square (i, j)\n- press 'r' to restart\n- press 'q' to quit\n");
        }
        else if (c == 'r')
        {
            printf("action : restart\n");
            game_restart(g);
        }
        else if (c == 'q')
        {
            printf("action : quit\nshame !\n");
            game_delete(g);
            return EXIT_SUCCESS;
        }
        else if (c == 'w')
        {
            scanf(" %d %d", &i, &j);
            if (game_check_move(g, i, j, S_ZERO))
            {
                game_play_move(g, i, j, S_ZERO);
            }
        }
        else if (c == 'b')
        {
            scanf(" %d %d", &i, &j);
            if (game_check_move(g, i, j, S_ONE))
            {
                game_play_move(g, i, j, S_ONE);
            }
        }
        else if (c == 'e')
        {
            scanf(" %d %d", &i, &j);
            if (game_check_move(g, i, j, S_EMPTY))
            {
                game_play_move(g, i, j, S_EMPTY);
            }
        }
    }
    printf("congratulation !\n");

    return EXIT_SUCCESS;
}