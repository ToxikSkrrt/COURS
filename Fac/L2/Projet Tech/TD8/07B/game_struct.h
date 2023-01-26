
#ifndef __GAME_STRUCT_H__
#define __GAME_STRUCT_H__

#include <stdbool.h>
#include <stddef.h>

#include "game_aux.h"
#include "game_ext.h"
#include "queue.h"

struct game_s {
  bool unique;
  bool wrapping;
  uint nb_rows;
  uint nb_cols;
  square* tab;
  queue* q_redo;
  queue* q_undo;
};

// structure pour stocker les coups à redo et undo dans les piles
struct move {
  uint row;
  uint col;
  square square_prev;
};

#endif