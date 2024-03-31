#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

sigjmp_buf b;
int i = 0;

void afficher (int i)
{
  printf ("i = %d\n", i);
  //sleep (3);
}

void handler (int sig)
{
  i++;
  alarm (2);
  printf("alarme !...\n");
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

    sigsetjmp (b, 1);
    afficher (i);
    pause ();
  

  return 0;
}
