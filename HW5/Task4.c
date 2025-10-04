#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int size = 3;
    int maxLength = 50;

    char* arr = (char*) malloc(size * maxLength);
    if (arr == NULL) {
        perror("Malloc failed\n");
    }

    printf("Enter %d strings: ", size);
    for (int i = 0; i < size; i++) {
        scanf("%49s", arr + i * maxLength);
    }
    for (int i = 0; i < size; i++) {
        printf("%s ", arr + i * maxLength);
    }
    printf("\n");
    char* temp = (char*) realloc(arr, (size+2) * 50);
    if (temp == NULL) {
        perror("Realloc failed\n");
    }
    arr = temp;
    temp = NULL;

    printf("Enter 2 more strings: ");
    for (int i = size; i < size+2; i++) {
        scanf("%s", arr + i * maxLength);
    }
    for (int i = 0; i < size+2; i++) {
        printf("%s ", arr + i * maxLength);
    }
    free(arr);

    return 0;
}