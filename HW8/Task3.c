#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 100

int main(void) {
    char source[MAX_PATH_LENGTH];

    printf("Input path to existing file:\n");
    ssize_t n = read(STDIN_FILENO, source, sizeof(source) - 1);
    if (n == -1) {
        perror("read");
        return 1;
    }
    if (n > 0 && source[n-1]=='\n')
        source[n-1] = '\0';
    else
        source[n] = '\0';

    int fd;
    fd = open(source, O_RDONLY);
    if (fd == -1) {
        perror("open");
    }

    ssize_t size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        perror("lseek");
    }
    printf("Size is %ld\n", size);

    lseek(fd, -1, SEEK_CUR);
    for (ssize_t i = size; i > 0; i--) {
        char c;
        ssize_t ret = read(fd, &c, 1);
        if (ret == -1) {
            perror("read");
        }

        if (i > 1) {
            if (lseek(fd, -2, SEEK_CUR) == -1)
                perror("lseek");
        }

        write(STDOUT_FILENO, &c, 1);
    }

    return 0;
}