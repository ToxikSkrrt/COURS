#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("hello ");
    write(1, "world", 5);
    return 0;
}