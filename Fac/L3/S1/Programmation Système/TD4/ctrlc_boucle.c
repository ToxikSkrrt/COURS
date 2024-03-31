#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

struct sigaction sa_alt;

void handler(int sig)
{
    printf("ctrl-c\n");
    sigaction(SIGINT, &sa_alt, NULL);
}

int main()
{
    struct sigaction sa;

    sa.sa_flags = 0;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handler;

    sigaction(SIGINT, &sa, &sa_alt);

    while (1)
        ;

    return EXIT_SUCCESS;
}
