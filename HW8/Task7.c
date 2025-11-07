#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 100
#define CHUNK_SIZE 10

ssize_t compare (const char*, ssize_t, const char*, ssize_t);

int main(void) {
    char first[MAX_PATH_LENGTH];
    char second[MAX_PATH_LENGTH];

    printf("Input source file path:\n");
    ssize_t n = read(STDIN_FILENO, first, sizeof(first)-1);
    if (n == -1) {
        perror("read");
        return 1;
    }
    if (n > 0 && first[n-1]=='\n')
        first[n-1] = '\0';
    else
        first[n] = '\0';

    printf("Input destination file path:\n");
    n = read(STDIN_FILENO, second, sizeof(second)-1);
    if (n == -1) {
        perror("read");
        return 1;
    }
    if (n > 0 && second[n-1]=='\n')
        second[n-1] = '\0';
    else
        second[n] = '\0';

    int fd1 = open(first, O_RDONLY);
    if (fd1 == -1) {
        perror("open");
        return 1;
    }

    int fd2 = open(second, O_RDONLY);
    if (fd2 == -1) {
        perror("open");
        return 1;
    }

    char buf1[CHUNK_SIZE + 1];
    char buf2[CHUNK_SIZE + 1];
    buf1[CHUNK_SIZE] = '\0';
    buf2[CHUNK_SIZE] = '\0';

    int count = -1;
    ssize_t ret1, ret2;
    while ((ret1 = read(fd1, buf1, CHUNK_SIZE)) > 0) {
        count++;
        ret2 = read(fd2, buf2, CHUNK_SIZE);

        if (ret1 != CHUNK_SIZE)
            buf1[ret1] = '\0';
        if (ret2 != CHUNK_SIZE)
            buf2[ret2] = '\0';

        // printf("Read from 1: %s number of bytes %ld\n", buf1, ret1);
        // printf("Read from 2: %s number of bytes %ld\n", buf2, ret2);

        ssize_t ret = compare(buf1, ret1, buf2, ret2);
        if (ret != -1) {
            printf("Files differ at byte %ld (0-based index)\n", ret + count * CHUNK_SIZE);
            return 1;
        }
    }
    if (count == -1 && read(fd2, buf2, CHUNK_SIZE) != 0) {
        printf("Files differ at byte 0 (0-based index)\n");
    }else {
        printf("Files are identical");
    }

    close(fd1);
    close(fd2);

    return 0;
}

ssize_t compare (const char *buffer1, ssize_t buf1size, const char *buffer2, ssize_t buf2size) {
    ssize_t small = buf1size < buf2size ? buf1size : buf2size;

    for (ssize_t i = 0; i < small; i++) {
        if (buffer1[i] != buffer2[i]) {
            return i;
        }
    }
    if (buf1size != buf2size && small < CHUNK_SIZE)
        return small;

    return -1;
}

