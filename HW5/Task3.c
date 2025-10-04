#include <stdio.h>
#include <stdlib.h>
#include "print_utils.h"

int main(void) {
    int size = 10;
    int new_size = 5;

    int* arr = (int*) malloc(size * sizeof(int));
    if (arr == NULL) {
        perror("malloc failed");
    }

    printf("Enter %d integers: ", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", arr + i);
    }

    int* temp = (int*) realloc(arr, new_size * sizeof(int));
    if (temp == NULL) {
        perror("error in realloc()");
        free(arr);
        return 1;
    }
    arr = temp;
    temp = NULL;

    printf("Array after resizing: ");
    printArr(arr, 5);

    free(arr);
    arr = NULL;

    return 0;
}
