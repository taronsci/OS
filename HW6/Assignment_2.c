#include <stdio.h>

struct structure1 {
    char var1;      //1
    int var2;       //4
    double var3;    //8
};                  //total = 16

struct structure2 {
    double var1;    //8
    int var2;       //4
    char var3;      //1
};                  //total = 16

int main(void) {
    struct structure1 s;
    struct structure2 p;

    printf("size of struct is: %lu\n",sizeof(s));
    printf("size of struct is: %lu\n",sizeof(p));

    printf("structure s: \n");
    printf("address of var1 is %p\n", &s.var1);
    printf("address of var2 is %p\n", &s.var2);
    printf("address of var3 is %p\n", &s.var3);

    printf("structure p: \n");
    printf("address of var1 is %p\n", &p.var1);
    printf("address of var2 is %p\n", &p.var2);
    printf("address of var3 is %p\n", &p.var3);

    return 0;
}