#include <stdio.h>

// #pragma pack(1)
#pragma pack(2)
struct structure1 {
    char a;
    int b;
    double c;
};

int main(void) {
    struct structure1 s;

    printf("size of struct is: %lu\n",sizeof(s));

    printf("address of a is %p\n", &s.a);
    printf("address of b is %p\n", &s.b);
    printf("address of c is %p\n", &s.c);


    return 0;
}