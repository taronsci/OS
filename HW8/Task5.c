#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    //open
    int fd;
    fd = open("sparse.bin", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
    }
    //write START
    ssize_t ret = write(fd, "START", 5);
    if (ret == -1) {
        perror("write");
    }
    //skip
    int const MiB = 1024 * 1024;
    lseek(fd, MiB, SEEK_CUR);
    //write END
    ret = write(fd, "END", 3);
    if (ret == -1) {
        perror("write");
    }
    close(fd);
    //reopen
    fd = open("sparse.bin", O_RDONLY);
    if (fd == -1) {
        perror("open");
    }

    off_t size = lseek(fd, 0, SEEK_END);
    printf("File size: %lld\n", size);

    system("du -h sparse.bin");
    system("ls -lh sparse.bin");

    return 0;
}
