#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>

void *square(void *arg) {
    int *num = (int *) arg;
    int sq = *num * *num;
    pthread_t tid = pthread_self();

    printf("Thread %lu says square of %d is %d\n",(unsigned long) tid, *num, sq);

    return NULL;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    pthread_t threads[5];

    for (int i = 0; i < 5; i++) {
        int *a = arr + i;
        pthread_create(&threads[i], NULL, square, (void *) a);
    }

    for (int i = 0; i < 5; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join a thread");
            return 1;
        }
    }
    return 0;
}
