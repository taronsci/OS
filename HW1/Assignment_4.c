#include <stdio.h>

int main(void){
    //Assignment 4
    int var = 10;
    int *ptr = &var;
    int *ptr1 = ptr;
    printf("%d \n", *ptr);
    printf("%d \n", *ptr1);

    return 0;
}