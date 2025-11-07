#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {

    int fd;
    fd = open("log.txt", O_WRONLY|O_CREAT|O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
    }

    char buffer[256];
    ssize_t ret;
    pid_t pid;
    char *p = "PID=";
    while ((ret = read(0, &buffer, 256)) > 0) {
        if (ret == -1) {
            perror("read");
        }
        pid = getpid();
        buffer[ret] = '\0';

        char pid_string[7];
        int len = snprintf(pid_string, sizeof(pid_string), "%d", pid);
        if (len < 0) {
            perror("snprintf failed");
            return 1;
        }

        write(fd, p, 4);
        write(fd, pid_string, len);
        write(fd, ": ", 2);
        write(fd, buffer, ret);
    }

    close(fd);

    return 0;
}