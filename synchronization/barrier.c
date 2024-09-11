#include "barrier.h"


int my_barrier_init(my_barrier_t *barrier, int count) {
    pthread_mutex_init(&barrier->lock, NULL);
    pthread_cond_init(&barrier->cond, NULL);
    pthread_cond_init(&barrier->reset_cond, NULL);

    pthread_mutex_lock(&barrier->lock);
    barrier->count = count;
    barrier->waiting = 0;
    barrier->passed = 0;
    pthread_mutex_unlock(&barrier->lock);

    return 0;
}


int my_barrier_wait(my_barrier_t *barrier) {
    // passed is non-zero only when threads are currently leaving the barrier
    while (barrier->passed > 0);

    pthread_mutex_lock(&barrier->lock);
    barrier->waiting++;

    if (barrier->waiting == barrier->count) {
        // Let all waiting threads pass
        barrier->passed = barrier->count;
        pthread_cond_broadcast(&barrier->cond);
    } else {
        while (barrier->waiting < barrier->count) {
            pthread_cond_wait(&barrier->cond, &barrier->lock);
        }
    }

    // Passed condition variable works similar to a shift register
    barrier->passed--;

    if (barrier->passed == 0) {
        // Reset the barrier
        barrier->waiting = 0;
        pthread_cond_broadcast(&barrier->reset_cond);
    } else {
        while (barrier->passed > 0) {
            pthread_cond_wait(&barrier->reset_cond, &barrier->lock);
        }
    }

    pthread_mutex_unlock(&barrier->lock);
    return 0;
}


int my_barrier_destroy(my_barrier_t *barrier) {
    pthread_mutex_destroy(&barrier->lock);
    pthread_cond_destroy(&barrier->cond);
    return 0;
}
