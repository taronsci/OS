#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {

    if (fork() == 0) {
        if (execl("/bin/ls", "ls", NULL) == -1)
            perror("Error fork\n");
    }

    wait(NULL);
    printf("Parent process is done");

    return 0;
}
