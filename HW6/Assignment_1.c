#include <stdio.h>

int main(void) {
    int var1;
    char var2;
    double var3;
    short var4;

    printf("size of int is %lu\n", sizeof(var1));
    printf("size of char is %lu\n", sizeof(var2));
    printf("size of double is %lu\n", sizeof(var3));
    printf("size of short is %lu\n", sizeof(var4));

    printf("address of var1 is %p\n", &var1);
    printf("address of var2 is %p\n", &var2);
    printf("address of var3 is %p\n", &var3);
    printf("address of var4 is %p\n", &var4);

    return 0;
}
