#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#define N 4
#define M 10000
long long balance = 0;

pthread_mutex_t mutex;
pthread_spinlock_t spinlock;

struct arguments {
    int locking;
    int speed;
};

void *deposit(void *arg) {
    struct arguments *args = (struct arguments *)arg;
    switch (args->locking) {
        case 0:
            if (args->speed == 1) {
                for (int i = 0; i < M; i++) {
                    pthread_mutex_lock(&mutex);
                    balance++;
                    if (args->speed == 1)
                        usleep(100);
                    pthread_mutex_unlock(&mutex);
                }
            }else {
                for (int i = 0; i < M; i++) {
                    pthread_mutex_lock(&mutex);
                    balance++;
                    pthread_mutex_unlock(&mutex);
                }
            }
        break;
        case 1:
            if (args->speed == 1) {
                for (int i = 0; i < M; i++) {
                    pthread_spin_lock(&spinlock);
                    balance++;
                    if (args->speed == 1)
                        usleep(100);
                    pthread_spin_unlock(&spinlock);
                }
            }else {
                for (int i = 0; i < M; i++) {
                    pthread_spin_lock(&spinlock);
                    balance++;
                    pthread_spin_unlock(&spinlock);
                }
            }
        break;
        default:
            printf("not supported flag\n");
    }
    return NULL;
}

void *withdraw(void *arg) {
    struct arguments *args = (struct arguments *)arg;
    switch (args->locking) {
        case 0:
            if (args->speed == 1) {
                for (int i = 0; i < M; i++) {
                    pthread_mutex_lock(&mutex);
                    balance--;
                    if (args->speed == 1)
                        usleep(100);
                    pthread_mutex_unlock(&mutex);
                }
            }else {
                for (int i = 0; i < M; i++) {
                    pthread_mutex_lock(&mutex);
                    balance--;
                    pthread_mutex_unlock(&mutex);
                }
            }
            break;
        case 1:
            if (args->speed == 1) {
                for (int i = 0; i < M; i++) {
                    pthread_spin_lock(&spinlock);
                    balance--;
                    if (args->speed == 1)
                        usleep(100);
                    pthread_spin_unlock(&spinlock);
                }
            }else {
                for (int i = 0; i < M; i++) {
                    pthread_spin_lock(&spinlock);
                    balance--;
                    pthread_spin_unlock(&spinlock);
                }
            }
            break;
        default:
            printf("not supported flag\n");
    }
    return NULL;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("first argument must be either mutex or spin\n");
        printf("second argument must be either short or long\n");
        return 1;
    }

    pthread_t threads[N];

    struct arguments args;
    if (strcmp(argv[1], "mutex") == 0) {
        pthread_mutex_init(&mutex, NULL);
        args.locking = 0;
    }
    else if (strcmp(argv[1], "spin") == 0) {
        pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
        args.locking = 1;
    }
    else {
        printf("first argument not supported\n");
        return 1;
    }


    if (strcmp(argv[2], "short") == 0)
        args.speed = 0;
    else if (strcmp(argv[2], "long") == 0)
        args.speed = 1;
    else {
        printf("second argument not supported\n");
        return 1;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < N/2; i++) {
        pthread_create(&threads[i], NULL, &deposit, &args);
    }
    for (int i = N/2; i < N; i++) {
        pthread_create(&threads[i], NULL, &withdraw, &args);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    gettimeofday(&end, NULL);

    if(args.locking == 0)
	pthread_mutex_destroy(&mutex);
    else if(args.locking == 1)
	pthread_spin_destroy(&spinlock);

    double execution_time = (end.tv_sec - start.tv_sec) * 1000.0;
    execution_time += (end.tv_usec - start.tv_usec) / 1000.0;

    printf("Total time using %s and %s critical section is: %f\n", argv[1], argv[2], execution_time);
    printf("expected value of balance is %d\n", 0);
    printf("actual value is %lld\n", balance);

    return 0;
}
