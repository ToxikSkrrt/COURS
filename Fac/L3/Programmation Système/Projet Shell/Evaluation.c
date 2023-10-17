#include "Evaluation.h"
#include "Shell.h"

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int evaluateExpr(Expression *expr) {
  static int first = 1;
  if (first) {
    // code d'initialisation
    first = 0;
  }
  fprintf(stderr, "sorry, this shell is not yet implemented\n");
  shellStatus = 1;
  return shellStatus;
}
