#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    //open
    int fd = open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
    }
    //write
    ssize_t nr;
    char *buf = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    nr = write(fd, buf, strlen(buf));
    if (nr == -1) {
        perror("write");
    }
    //close
    close(fd);
    //open again
    fd = open("data.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
    }
    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        perror("lseek");
    }
    printf("Current file size is %lld\n", size);

    ftruncate(fd, 10);

    size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        perror("lseek");
    }
    printf("New file size is %lld\n", size);

    lseek(fd, 0, SEEK_SET);
    char buffer[size + 1];
    ssize_t ret = read(fd, buffer, size);
    if (ret == -1) {
        perror("read");
    }
    buffer[ret] = '\0';
    printf("%s", buffer);
    close(fd);

    return 0;
}