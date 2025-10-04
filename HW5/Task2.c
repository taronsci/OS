#include <stdio.h>
#include <stdlib.h>
#include "print_utils.h"


int main(void) {
    printf("Enter number of elements: ");
    int number;
    scanf("%d", &number);

    int* arr = (int*) calloc(number ,sizeof(int));
    printf("Array after calloc: ");
    printArr(arr, number);

    printf("Enter %d integers: ", number);
    for (int i = 0; i < number; i++) {
        scanf("%d", arr + i);
    }

    printf("Updated array: ");
    printArr(arr, number);

    double avg = 0;
    for (int i = 0; i < number; i++) {
        avg += arr[i];
    }
    avg = avg / number;
    printf("Average of all numbers is: %.1f\n", avg);

    free(arr);
    arr = NULL;

    return 0;
}

