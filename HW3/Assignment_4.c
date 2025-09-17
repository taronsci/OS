#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    int ret = fork();
    if (ret == 0) {
        exit(42);
    }
    int status_1;
    waitpid(ret, &status_1, 0);

    ret = fork();
    if (ret == 0) {
        exit(0);
    }
    int status_2;
    waitpid(ret, &status_2, 0);

    if (WIFEXITED(status_1)) {
        printf("Child 1 exited with status %d \n", WEXITSTATUS(status_1));
    }
    if (WIFEXITED(status_2)) {
        printf("Child 2 exited with status %d \n", WEXITSTATUS(status_2));
    }

    return 0;
}