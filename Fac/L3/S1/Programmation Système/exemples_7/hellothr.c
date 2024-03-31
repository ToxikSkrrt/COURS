
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void *thread_func (void *arg)
{
  printf ("%s from thread!\n", (char *)arg);

  return NULL;
}

int main (int argc, char *argv[])
{
  pthread_t pid1, pid2;

  pthread_create (&pid1, NULL, thread_func, "Hello from 1");
  pthread_create (&pid2, NULL, thread_func, "Hello from 2");

  thread_func ("Hello from main");

  pthread_join (pid1, NULL);
  pthread_join (pid2, NULL);

  return 0;
}
