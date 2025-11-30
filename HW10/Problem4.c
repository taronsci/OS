#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define N 5

sem_t semaphores[3];
pthread_mutex_t lock;

struct index {
    int i;
    char letter;
};

void *print(void *args) {
    const struct index index = *(struct index *) args;
    int j = index.i;

    for (int i = 0; i < N; i++) {
        sem_wait(&semaphores[j]);
        pthread_mutex_lock(&lock);
        printf("%c %d\n", index.letter, i);
        pthread_mutex_unlock(&lock);
        sem_post(&semaphores[(j+1) % 3]);
    }
    return NULL;
}

int main(void) {
    sem_init(&semaphores[0], 0, 1);
    sem_init(&semaphores[1], 0, 0);
    sem_init(&semaphores[2], 0, 0);

    pthread_mutex_init(&lock, NULL);

    pthread_t thread_A, thread_B, thread_C;

    struct index A_index;
    A_index.i = 0;
    A_index.letter = 'A';
    pthread_create(&thread_A, NULL, print, &A_index);

    struct index B_index;
    B_index.i = 1;
    B_index.letter = 'B';
    pthread_create(&thread_B, NULL, print, &B_index);

    struct index C_index;
    C_index.i = 2;
    C_index.letter = 'C';
    pthread_create(&thread_C, NULL, print, &C_index);

    pthread_join(thread_A, NULL);
    pthread_join(thread_B, NULL);
    pthread_join(thread_C, NULL);

    sem_destroy(&semaphores[0]);
    sem_destroy(&semaphores[1]);
    sem_destroy(&semaphores[2]);

    return 0;
}