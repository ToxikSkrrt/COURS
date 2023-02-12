#include "game.h"
#include "queue.h"

struct game_s {
    uint rows;
    uint columns;
    square **board;
    bool wrapping;
    bool unique;
    queue *undo;
    queue *redo;
};

typedef struct {
    uint i;        // i value of the square
    uint j;        // j value of the square
    square value;  // value of the square that will be added to one of the two
                   // queues of the game
} queueSquare;