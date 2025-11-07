#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd;
    fd = open("numbers.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
    }

    char buf[3];
    buf[1] = '\n';
    int len = 2;
    for (int i = 1; i < 11; i++) {
        if (i == 10) {
            buf[0] = '1';
            buf[1] = '0';
            buf[2] = '\n';
            len++;
        }else
            buf[0] = '0' + i;

        ssize_t ret = write(fd, buf, len);
        if (ret == -1) {
            perror("write");
            return 1;
        }
    }
    close(fd);

    fd = open("numbers.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
    }

    off_t size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char buffer[size];

    ssize_t ret = read(fd, &buffer, sizeof(buffer));
    if (ret == -1)
        return 1;

    int target = 4;
    for (int i = 0; i < ret; i++) {
        if (buffer[i] == '\n')
            target--;

        if (target == 0) {
            target = i;
            break;
        }
    }

    lseek(fd, target - 1, SEEK_SET);
    write(fd, "100\n", 4);
    write(fd, buffer + target + 1,size - target - 1);

    close(fd);

    execl("/bin/cat", "cat", "numbers.txt", NULL);
    perror("exec");
    return 1;
}