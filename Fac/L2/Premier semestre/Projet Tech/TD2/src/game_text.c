#include <stdlib.h>
#include "game.h"
#include "game_aux.h"

int main (void)
{
    game g = game_default();
    game_play_move(g, 0, 0, S_ZERO); 
    game_print(g);
    game_delete(g);

    return EXIT_SUCCESS;
}