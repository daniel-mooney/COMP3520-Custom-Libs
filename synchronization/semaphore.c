#include "semaphore.h"


int my_sem_init(my_semaphore_t *sem, int init_value) {
    pthread_mutex_init(&sem->lock, NULL);
    pthread_cond_init(&sem->cond, NULL);

    pthread_mutex_lock(&sem->lock);
    sem->counter = init_value;
    pthread_mutex_unlock(&sem->lock);

    return 0;
}

int my_sem_post(my_semaphore_t *sem) {
    pthread_mutex_lock(&sem->lock);
    sem->counter++;

    // Release waiting threads if newly positive
    if (sem->counter == 1) {
        pthread_cond_broadcast(&sem->cond);
    }

    pthread_mutex_unlock(&sem->lock);
    return 0;
}

int my_sem_post_many(my_semaphore_t *sem, int value) {
    pthread_mutex_lock(&sem->lock);
    sem->counter += value;

    // Release waiting threads if newly positive
    if (sem->counter > 0 && sem->counter <= value) {
        pthread_cond_broadcast(&sem->cond);
    }

    pthread_mutex_unlock(&sem->lock);
    return 0;
}

int my_sem_wait(my_semaphore_t *sem) {
    pthread_mutex_lock(&sem->lock);
    sem->counter--;

    // Busy wait, can use condition variable instead
    while (sem->counter < 0) {
        pthread_cond_wait(&sem->cond, &sem->lock);
    }

    pthread_mutex_unlock(&sem->lock);
    return 0;
}

int my_sem_destroy(my_semaphore_t *sem) {
    pthread_mutex_destroy(&sem->lock);
    pthread_cond_destroy(&sem->cond);

    return 0;
}