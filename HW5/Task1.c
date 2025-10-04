#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("Please input a number n: ");
    int number;
    scanf("%d", &number);
    printf("Please input %d numbers: ", number);

    int* arr = (int*) malloc(number * sizeof(int));
    for (int i = 0; i < number; i++) {
        scanf("%d", arr + i);
    }

    int sum = 0;
    for (int i = 0; i < number; i++) {
        sum += arr[i];
    }
    printf("Sum of all numbers is: %d\n", sum);

    free(arr);
    arr = NULL;

    return 0;
}
