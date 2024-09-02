#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "synchronization/semaphore.h"
#include "synchronization/barrier.h"

my_semaphore_t sem_test;
my_barrier_t barrier_test;

void *dummy_thread(void *);
void *control_thread(void *);


int main() {
    int n_threads;

    printf("How many threads: ");
    fflush(stdout);

    scanf("%d", &n_threads);

    my_sem_init(&sem_test, 1);
    my_barrier_init(&barrier_test, n_threads);

    // Create n threads that wait for semaphore
    pthread_t *thread_id = (pthread_t *) malloc(n_threads * sizeof(pthread_t));
    int *id = (int *) malloc(n_threads * sizeof(int));

    for (int i = 0; i < n_threads; i++) {
        id[i] = i;
        if (pthread_create(&thread_id[i], NULL, dummy_thread, &id[i])) {
            printf("Could not create dummy thread %d\n", i);
        }
    }

    // Create control thread
    pthread_t ctrl_thread;
    int to_free = n_threads - 2;

    if (pthread_create(&ctrl_thread, NULL, control_thread, &to_free)) {
        printf("Failed to create control thread.\n");
    }

    int final_free = 2;
    pthread_t ctrl_thread2;

    if (pthread_create(&ctrl_thread2, NULL, control_thread, &final_free)) {
        printf("Failed to create control thread.\n");
    }

    // Join threads
    for (int i = 0; i < n_threads; i++) {
        pthread_join(thread_id[i], NULL);
    }

    pthread_join(ctrl_thread, NULL);
    pthread_join(ctrl_thread2, NULL);

    free(thread_id);
    free(id);

    my_sem_destroy(&sem_test);
    my_barrier_destroy(&barrier_test);

    return 0;
}


void *dummy_thread(void *arg) {
    int *id = arg;

    printf("Thread [%d] is waiting...counter = %d\n", *id, sem_test.counter);
    my_sem_wait(&sem_test);
    // my_barrier_wait(&barrier_test);

    printf("Thread [%d] is free!\n", *id);

    return NULL;
}


void *control_thread(void *arg) {
    int *n_threads = arg;

    printf("Control thread will post the semaphore\n");
    for (int i = 0; i < *n_threads + 1; i++) {
        // printf("Semaphore count: %d\n", sem_test.counter);
        my_sem_post(&sem_test);
        
        printf("Posting semaphore to %d\n", sem_test.counter);
    }

    printf("Control thread done posting the semaphore\n");

    return NULL;
}