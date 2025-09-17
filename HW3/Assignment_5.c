#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    if (fork() == 0) {
        printf("Child pid is %d \n", getpid());
        exit(0);
    }
    // wait(NULL);
    sleep(20);

    return 0;
}