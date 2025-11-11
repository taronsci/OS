#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>

int arr[] = {2, 5, 3, 1, 10, 5};

void *sum(void *arg) {
    int *range = (int*) arg;
    int sum = 0;

    for (int i = range[0]; i < range[1]; i++)
        sum += arr[i];

    printf("Sum: %d\n", sum);
    return NULL;
}

int main(void) {
    pthread_t threads[2];

    int size = 6;
    int num_threads = 2;

    int *range;
    for (int i = 0; i < num_threads; i++) {
        range = (int*) malloc(2 * sizeof(int));
        range[0] = i * size/num_threads;
        range[1] = (i + 1) * size/num_threads;

        pthread_create(&threads[i], NULL, sum, (void*) range);
    }

    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL)!=0) {
            perror("Failed to join a thread");
        }
    }

    free(range);
    range = NULL;

    return 0;
}