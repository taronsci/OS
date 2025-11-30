#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

#define K 3
#define N 10

int counter = 0;
sem_t printers;
pthread_mutex_t printer_mutex;

void *print(void *args) {
    sem_wait(&printers);

    pthread_mutex_lock(&printer_mutex);
    counter++;
    printf("Thread %ld is printing... Threads currently printing: %d\n", pthread_self(), counter);
    pthread_mutex_unlock(&printer_mutex);

    usleep(5000000);

    pthread_mutex_lock(&printer_mutex);
    counter--;
    pthread_mutex_unlock(&printer_mutex);

    sem_post(&printers);

    return NULL;
}

int main(void) {
    sem_init(&printers, 0, 1);
    pthread_mutex_init(&printer_mutex, NULL);

    pthread_t threads[N];
    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, print, NULL);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&printers);

    return 0;
}
