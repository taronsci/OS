#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    if (fork() == 0) {
        printf("Child 1 pid is %d \n", getpid());
        exit(0);
    }
    printf("%d\n", wait(NULL)); //process ID of child
    printf("Parent pid is %d \n", getpid());

    int ret = fork();
    if (ret == 0) {
        printf("Child 2 pid is %d \n", getpid());
        exit(0);
    }
    printf("%d\n", waitpid(ret, NULL, 0)); //process ID of child (ret)

    return 0;
}
