#define _XOPEN_SOURCE 600

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>

void test_fd()
{
    int fd = open("file_test_fd.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    char c;

    printf("INPUT\n");

    while (read(STDIN_FILENO, &c, sizeof(c)) && c != '.')
    {
        write(fd, &c, sizeof(c));
    }

    close(fd);

    fd = open("file_test_fd.txt", O_RDONLY);

    printf("OUTPUT\n");

    while (read(fd, &c, sizeof(c)))
    {
        printf("%c", c);
    }

    close(fd);
}

void test_pipe()
{
    enum
    {
        R,
        W
    };

    int tube[2];
    pipe(tube);

    pid_t pid = fork();
    if (!pid)
    {
        close(tube[R]);
        dup2(tube[W], STDOUT_FILENO);
        execlp("ls", "ls", "-al", NULL);
        exit(EXIT_FAILURE);
    }
    else
    {
        close(tube[W]);
        int backup = dup(STDIN_FILENO);
        dup2(tube[R], STDIN_FILENO);

        execlp("cat", "cat", "-n", NULL);

        dup2(backup, STDIN_FILENO);
        close(backup);
        close(tube[R]);
    }
}

void test_fork()
{
    int pid = fork();

    if (pid)
    {
        printf("I'm the father -> %d\n", getpid());
    }
    else
    {
        printf("I'm the child -> %d\n", getpid());
    }
}

struct sigaction sa_alt;

void test_traitant()
{
    printf("ctrl-c\n");
    sigaction(SIGINT, &sa_alt, NULL);
}

void test_signaux_base()
{
    struct sigaction sa;

    sa.sa_flags = 0;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = test_traitant;

    sigaction(SIGINT, &sa, &sa_alt);

    while (1)
        ;
}

void test_traitant_mask()
{
    printf("Bloqué hihi\n");
}

void test_signaux_mask()
{
    struct sigaction sa;

    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = test_traitant_mask;

    sigaction(SIGINT, &sa, NULL);

    sigset_t s;
    sigfillset(&s);
    sigaddset(&s, SIGINT);

    sigprocmask(SIG_BLOCK, &s, NULL);

    printf("Any ^C will be postponed for 5 secs\n");

    sleep(5);

    sigprocmask(SIG_UNBLOCK, &s, NULL);

    printf("Not now :(\n)");

    while (1)
        ;
}

int NB_THREADS = 10;
pthread_barrier_t barrier;

void *test_HelloGoodbye(void *p)
{
    printf("%d: bonjour\n", p);
    sleep(1);
    pthread_barrier_wait(&barrier);

    printf("%d: a bientot\n", p);

    return NULL;
}

void test_thread_barrier()
{
    pthread_barrier_init(&barrier, NULL, NB_THREADS);

    pthread_t pids[NB_THREADS];

    for (int i = 0; i < NB_THREADS; i++)
        pthread_create(&pids[i], NULL, test_HelloGoodbye, i);

    for (int i = 0; i < NB_THREADS; i++)
        pthread_join(pids[i], NULL);

    pthread_barrier_destroy(&barrier);
}

unsigned long volatile k = 0;
const unsigned long MAX = 100 * 1000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // = pthread_mutex_init(mutex, NULL);

void *test_for_en_parallele(void *p)
{
    int tmp = 0;
    for (unsigned long i = 0; i < MAX; i++)
        tmp++;
    pthread_mutex_lock(&mutex);
    k += tmp;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void test_thread_mutex()
{
    int n = 10;

    pthread_t tids[n];

    for (int i = 0; i < n; i++)
        pthread_create(tids + i, NULL, test_for_en_parallele, NULL);

    for (int i = 0; i < n; i++)
        pthread_join(tids[i], NULL);

    printf("%lu\n", k);

    pthread_mutex_destroy(&mutex);
}

int main(int argc, char **argv)
{
    switch (atoi(argv[1]))
    {
    case 0:
        test_fd();
        break;
    case 1:
        test_pipe();
        break;
    case 2:
        test_fork();
        break;
    case 3:
        test_signaux_base(); // bloque un seul signal
        break;
    case 4:
        test_signaux_mask(); // bloque un seul signal
        break;
    case 5:
        test_thread_barrier();
        break;
    case 6:
        test_thread_mutex();
        break;
    }
}