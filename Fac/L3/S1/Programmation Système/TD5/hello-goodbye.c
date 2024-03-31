#define _XOPEN_SOURCE 600

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int NB_THREADS = 10;

pthread_barrier_t barrier;

void *HelloGoodbye(void *p)
{
  printf("%d: bonjour\n", p);

  pthread_barrier_wait(&barrier);
  sleep(1);
  printf("%d: a bientot\n", p);

  return NULL;
}

int main(int argc, char *argv[])
{
  if (argc > 1)
  {
    NB_THREADS = atoi(argv[1]);
  }

  pthread_barrier_init(&barrier, NULL, NB_THREADS);

  pthread_t pids[NB_THREADS];

  for (int i = 0; i < NB_THREADS; i++)
    pthread_create(&pids[i], NULL, HelloGoodbye, i);

  for (int i = 0; i < NB_THREADS; i++)
    pthread_join(pids[i], NULL);

  pthread_barrier_destroy(&barrier);

  return EXIT_SUCCESS;
}
