#include <stdio.h>

int main(void) {
    char str[] = "Hello";
    char *str1 = str;

    for (int i = 0; *str1 != '\0'; i++, str1++) {
        printf("%c", *(str + i));
    }
    printf("\n");
    printf("Length of string is %ld", str1 - str - 1);

    return 0;
}