#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {

    if (fork() == 0) { //child process 1
        if (execl("/bin/ls", "ls", NULL) == -1)
            perror("Error fork\n");
    }
    wait(NULL);

    if (fork() == 0) { //child process 2
        if (execl("/bin/date", "date", NULL) == -1)
            perror("Error fork\n");
    }
    wait(NULL);

    printf("Parent process done");

    return 0;
}
