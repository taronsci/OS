#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <pthread.h>

void *print_message(void *arg) {
    pthread_t tid = pthread_self();

    for (int i = 1; i < 6; i++)
        printf("Thread %lu prints %d\n", (unsigned long) tid, i);

    return NULL;
}

int main(void) {
    pthread_t thread1, thread2, thread3;

    pthread_create(&thread1, NULL, print_message, NULL);
    pthread_create(&thread2, NULL, print_message, NULL);
    pthread_create(&thread3, NULL, print_message, NULL);

    if (pthread_join(thread1, NULL) != 0) {
        perror("Failed to join thread 1");
        return 1;
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join thread 2");
        return 1;
    }

    if (pthread_join(thread3, NULL) != 0) {
        perror("Failed to join thread 3");
        return 1;
    }

    return 0;
}
