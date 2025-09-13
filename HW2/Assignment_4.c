#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void) {

    if (fork() == 0) {
        if (execl("/usr/bin/grep", "grep", "main", "HW2/test.txt", NULL) == -1)
            perror("Error fork\n");
    }

    wait(NULL);
    printf("Parent process completed");

    return 0;
}
