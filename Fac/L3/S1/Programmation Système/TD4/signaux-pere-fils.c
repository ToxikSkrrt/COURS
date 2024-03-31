#define XOPEN_SOURCE 600
#define _GNU_SOURCE

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

#define NSIGNORT 32

int acc = 1;

sigset_t tout;

void handler(int sig)
{
  printf("%d - %s\n", acc, strsignal(sig));
  acc++;
}

int emetteur(int pere, int argc, char *argv[])
{
  struct sigaction usr1;
  int k = atoi(argv[1]);

  sleep(1);

  for (int i = 0; i < k; i++)
    for (int j = 2; j < argc; j++)
    {
      kill(pere, atoi(argv[j]));
      pause();
    }

  sleep(1);
  kill(pere, 9);
  return 0;
}

int recepteur(int fils)
{
  printf("récepteur : %d\n", getpid());

  // installation du handler pour tous les signaux non RT

  struct sigaction sa;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  sa.sa_handler = handler;

  for (int sig = 0; sig < NSIGNORT; sig++)
  {
    sigaction(sig, &sa, NULL);
    sigprocmask(SIG_UNBLOCK, &tout, NULL);
  }

  while (1)
  {
    sigsuspend(&tout);
    kill(fils, SIGUSR1);
  }

  return 0;
}

void traitant(int s)
{
  static int occ[32];
  print("%d fois %d\n", ++occ[s], s);
}

void traitant_usr1(int s) {}

int main(int argc, char *argv[])
{
  sigfillset(&tout);
  sigprocmask(SIG_BLOCK, &tout, NULL);
  pid_t pid = fork();
  if (pid == 0)
    emetteur(getppid(), argc, argv);
  else
    recepteur(pid);
}
