#include <stdio.h>
#include <unistd.h>

int main(void) {

    printf("parent process\n");

    if (fork() == 0)
        printf("Hello from child process\n");
    else
        printf("Hello from parent process\n");


    if (fork() == 0)
        printf("Hello from child process 1\n");
    else
        printf("Hello from parent process 1\n");

    if (fork() == 0)
        printf("Hello from child process 2\n");
    else
        printf("Hello from parent process 2\n");

    return 0;
}