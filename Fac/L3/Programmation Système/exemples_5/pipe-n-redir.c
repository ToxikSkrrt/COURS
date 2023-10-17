#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "error.h"

char *FILENAME = "file.txt";

#define pprintf(format, ...)                                                   \
  printf ("[PID %d] " format, getpid (), ##__VA_ARGS__)

int tube[2];

enum { R, W };

void child (void)
{
  // TODO : redirect STDIN
  close (tube[W]);
  dup2 (tube[R], STDIN_FILENO); close (tube[R]);
  // tr a-z A-Z
  for (;;) {
    char c;
    int n = read (STDIN_FILENO, &c, 1);
    check_syscall (n, "Cannot read");

    if (n == 0)
      break;

    if (islower(c))
      c = toupper (c);

    n = write (STDOUT_FILENO, &c, 1);
    check_syscall (n, "Cannot write");
  }
}

void father (void)
{
  int newline = 1;
  int line = 1;
  char str[16];

  // TODO: redirect STDOUT
  close (tube[R]);
  dup2 (tube[W], STDOUT_FILENO); close (tube[W]);

  int fd = open (FILENAME, O_RDONLY);
  check_syscall (fd, "Cannot open %s file", FILENAME);

  // cat -n
  for (;;) {
    char c;
    int n = read (fd, &c, 1);
    check_syscall (n, "Cannot read from file %s", FILENAME);

    if (n == 0)
      break;

    if (newline) {
      snprintf (str, 16, "\t%d  ", line);
      write (STDOUT_FILENO, str, strlen (str));
      newline = 0;
    }
    
    n = write (STDOUT_FILENO, &c, 1);
    check_syscall (n, "Cannot write");
    if (c == '\n') {
      line++;
      newline = 1;
    }
  }
}

int main (int argc, char *argv[])
{
  if (argc > 1)
    FILENAME = argv[1];

  pipe (tube);

  if (fork () != 0) { // father
    father ();
  } else { //child
    child ();
  }

  return 0;
}
