#include <stdio.h>

int main(void) {
    char str[] = "Hello";
    char *str1 = str;

    for (; *str1 != '\0'; str1++) {
        printf("%c", *str1);
    }
    printf("\n");
    printf("Length of string is %ld", str1 - str);

    return 0;
}