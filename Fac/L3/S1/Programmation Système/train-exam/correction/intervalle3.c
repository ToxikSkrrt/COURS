#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

sigjmp_buf b;
int i = 0;

int second_time = 0;

void afficher (int i)
{
  printf ("i = %d\n", i);
  sleep (3);
  //sleep (10);
}

void handler (int sig)
{
  i++;
  alarm (2);
  printf("alarme !...\n");
  if (!second_time)
    second_time = 1;
  else
    siglongjmp (b, 1);
}

int main ()
{
  struct sigaction sa;

  sa.sa_flags = 0;
  sa.sa_handler = handler;
  sigemptyset(&sa.sa_mask);

  sigaction(SIGALRM, &sa, NULL);

  alarm (2);

  while (1) {
    sigsetjmp (b, 1);
    second_time = 0;
    afficher (i);
    pause ();
  }

  return 0;
}
