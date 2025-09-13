#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void) {

    if (fork() == 0) {
        if (execl("/bin/echo", "echo", "Hello from the child process", NULL) == -1)
            perror("Error fork\n");
    }

    wait(NULL);
    printf("Parent process done");

    return 0;
}
