#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define pprintf(format, ...) printf("[PID %d] " format, getpid(), ##__VA_ARGS__)

int main(int argc, char *argv[])
{
  pid_t pid;

  pid = fork();
  if (pid)
  { // father
    pprintf("Parent's fork return value: %d\n", pid);
  }
  else
  { // Child
    pprintf("Child's fork return value: %d\n", pid);
  }

  return 0;
}
