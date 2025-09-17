#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void print1(void) {
    printf("Print statement 1\n");
}
void print2(void) {
    printf("Print statement 2\n");
    exit(0);
}

int main(void) {
    //LIFO (stack)
    atexit(print1);
    atexit(print2);

    exit(0);
}