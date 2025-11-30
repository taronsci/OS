#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <getopt.h>

#define N 4
#define M 1000000

long long counter = 0;
pthread_mutex_t mutex;
pthread_spinlock_t spinlock;
int flag = -1;

void *increment(void *arg) {
    switch (flag) {
        case 0:
            for (int i = 0; i < M; i++)
                counter++;
            break;
        case 1:
            for (int i = 0; i < M; i++) {
                pthread_mutex_lock(&mutex);
                counter++;
                pthread_mutex_unlock(&mutex);
            }
            break;
        case 2:
            for (int i = 0; i < M; i++) {
                pthread_spin_lock(&spinlock);
                counter++;
                pthread_spin_unlock(&spinlock);
            }
            break;
        default:
            printf("not supported flag");
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    const char *optstring = "ABC";

    int opt;
    while ((opt = getopt_long(argc, argv, optstring, NULL, NULL)) != -1) {
        switch (opt) {
            case 'A':
                flag = 0;
                break;
            case 'B':
                pthread_mutex_init(&mutex, NULL);
                flag = 1;
                break;
            case 'C':
                pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
                flag = 2;
                break;
            default:
                printf("not a valid option");
        }
    }
    if (flag == -1) {
        fprintf(stderr, "Please specify a single option: -A, -B or -C for each subproblem \n");
        return 1;
    }

    pthread_t threads[N];

    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, &increment, NULL);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    if(flag == 1)
        pthread_mutex_destroy(&mutex);
    else if(flag == 2)
	pthread_spin_destroy(&spinlock);

    printf("expected value is %d\n", N * M);
    printf("actual value is %lld\n", counter);

    return 0;
}
