#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <stdbool.h>

#define P 10
#define C 15
#define STOP (P * C)
#define BUFFER_SIZE 8

int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;

int counter = 0;

pthread_mutex_t buffer_mutex;
pthread_mutex_t counter_mutex;

sem_t empty_slots;
sem_t full_slots;

bool stop = false;

void *produce(void *arg) {
    while (true) {
        if (stop) return NULL;
        sem_wait(&empty_slots);
        pthread_mutex_lock(&buffer_mutex);

        printf("producing position %d\n", in_pos);
        buffer[in_pos] = 1;
        in_pos = (in_pos + 1) % BUFFER_SIZE;

        pthread_mutex_lock(&counter_mutex);
        if (counter >= STOP) {
            stop = true;
            pthread_mutex_unlock(&counter_mutex);
            pthread_mutex_unlock(&buffer_mutex);

            for (int i = 0; i < P+C-1; i++) {
                sem_post(&full_slots);
                sem_post(&empty_slots);
            }
            break;
        }
        counter++;
        pthread_mutex_unlock(&counter_mutex);

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&full_slots);
    }
    return NULL;
}

void *consume(void *arg) {
    while (true) {
        sem_wait(&full_slots);
        pthread_mutex_lock(&buffer_mutex);
        printf("consuming position %d\n", out_pos);

        buffer[out_pos] = 0;
        out_pos = (out_pos + 1) % BUFFER_SIZE;

        pthread_mutex_lock(&counter_mutex);
        if (counter >= STOP) {
            stop = true;
            pthread_mutex_unlock(&counter_mutex);
            pthread_mutex_unlock(&buffer_mutex);

            for (int i = 0; i < P+C-1; i++) {
                sem_post(&full_slots);
                sem_post(&empty_slots);
            }
            break;
        }
        counter++;
        pthread_mutex_unlock(&counter_mutex);

        pthread_mutex_unlock(&buffer_mutex);
        sem_post(&empty_slots);
    }
    return NULL;
}

int main(void) {
    pthread_t producers[P];
    pthread_t consumers[C];

    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);

    pthread_mutex_init(&buffer_mutex, NULL);
    pthread_mutex_init(&counter_mutex, NULL);

    for (int i = 0; i < P; i++)
        pthread_create(&producers[i], NULL, produce, NULL);
    for (int i = 0; i < C; i++)
        pthread_create(&consumers[i], NULL, consume, NULL);

    for (int i = 0; i < P; i++)
        pthread_join(producers[i], NULL);
    for (int i = 0; i < C; i++)
        pthread_join(consumers[i], NULL);

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&buffer_mutex);
    pthread_mutex_destroy(&counter_mutex);

    printf("finished, counter = %d\n", counter);
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    return 0;
}