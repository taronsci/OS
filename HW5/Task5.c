#include <stdio.h>
#include <stdlib.h>

float highest(float*, int);
float lowest(float*, int);

int main(void) {

    printf("Enter the number of students: ");
    int number;
    scanf("%d", &number);

    float* grades = (float*) malloc(number * sizeof(float));
    printf("Enter the grades: ");
    for (int i = 0; i < number; i++) {
        scanf("%f", grades + i);
    }

    printf("Highest grade: %0.2f\n" , highest(grades,number));
    printf("Lowest grade: %0.2f\n" , lowest(grades,number));

    free(grades);
    grades = NULL;

    return 0;
}

float highest(float *grades, int size) {
    float highest = grades[0];
    for (int i=1; i < size; i++) {
        if (grades[i] > highest)
            highest = grades[i];
    }
    return highest;
}
float lowest(float *grades, int size) {
    float lowest = *grades;
    for (int i=1; i < size; i++) {
        if (grades[i] < lowest)
            lowest = grades[i];
    }
    return lowest;
}


