#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PATH_LENGTH 256

int main(void) {
    char source[MAX_PATH_LENGTH];
    char dest[MAX_PATH_LENGTH];

    printf("Input source file path:\n");
    ssize_t n = read(STDIN_FILENO, source, sizeof(source) - 1);
    if (n == -1) {
        perror("read");
        return 1;
    }
    if (n > 0 && source[n - 1] == '\n')
        source[n - 1] = '\0';
    else
        source[n] = '\0';

    printf("Input destination file path:\n");
    n = read(STDIN_FILENO, dest, sizeof(dest)-1);
    if (n == -1) {
        perror("read");
        return 1;
    }
    if (n > 0 && dest[n-1] == '\n')
        dest[n-1] = '\0';
    else
        dest[n] = '\0';

    printf("Source file path: %s\n", source);
    printf("Destination file path: %s\n", dest);

    //open source file
    int fds;
    fds = open(source, O_RDONLY);
    if (fds == -1){
        perror("");
    }

    //open destination file
    int fdd;
    fdd = open(dest, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (fdd == -1){
        perror("");
    }

    // read from source file
    int capacity = 5;
    ssize_t totalRead = 0;

    ssize_t ret;
    char *buf = (char*) malloc(capacity);
    if (!buf) {
        perror("malloc");
        return 1;
    }
    while ((ret = read(fds, buf + totalRead, capacity - totalRead)) != 0){
        if (ret == -1){
            if (errno == EINTR)
                continue;
            perror("read");
            break;
        }
        totalRead += ret;

        if (totalRead == capacity) {
            capacity *= 2;
            char *temp = (char*) realloc(buf, capacity);
            if (!temp) {
                perror("realloc");
                free(buf);
                close(fds);
                return 1;
            }
            buf = temp;
            temp = NULL;
        }
    }
    buf[totalRead] = '\0';

    if (close (fds) == -1)
        perror ("");

    printf("Total read bytes is %ld", totalRead);

    // write to destination file
    ssize_t nr;
    nr = write(fdd, buf, strlen(buf));
    if (nr == -1){
        perror("");
    }

    if (close (fdd) == -1)
        perror ("");

    free(buf);
    buf = NULL;

    return 0;
}
