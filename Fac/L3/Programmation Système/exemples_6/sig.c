#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/mman.h>

#define pprintf(format, ...) printf ("[PID %d] " format, getpid(), ##__VA_ARGS__)

int main (int argc, char *argv[])
{
  pid_t pid;

  pid = fork ();
  if (pid) { // father
    int status;

    sleep (1);
    kill (pid, SIGSEGV);
    
    wait (&status);

    if (WIFSIGNALED(status)) {
      int sig = WTERMSIG(status);
      pprintf ("Child killed by signal %d (%s)\n", sig, strsignal (sig));
    } else {
      pprintf ("Child exited normally (code: %d)\n", WEXITSTATUS (status));
    }

  } else { // Child
    pprintf ("Child start\n");
    
    // SIGABRT
    //abort();
    // SIGINT
    //raise (SIGINT);
    // SIGALRM
    //alarm (1);
    // SIGSEGV
    //((int *)NULL)[0] = 12;

    // SIGFPE
    //float i = 5.0, j = 0.0;
    //printf ("somme = %f\n", i / j);

    // SIGPIPE
    //int tube[2];
    //pipe(tube);
    //close (tube[0]);
    //write (tube[1], "bonjour", 7);

    sleep(2);

    pprintf ("Child end\n");
  }

  return 0;
}
