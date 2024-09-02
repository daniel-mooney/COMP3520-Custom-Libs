#include "barrier.h"


int my_barrier_init(my_barrier_t *barrier, int count) {
    pthread_mutex_init(&barrier->lock, NULL);
    pthread_cond_init(&barrier->cond, NULL);

    pthread_mutex_lock(&barrier->lock);
    barrier->count = count;
    barrier->waiting = 0;
    pthread_mutex_unlock(&barrier->lock);

    return 0;
}


int my_barrier_wait(my_barrier_t *barrier) {
    pthread_mutex_lock(&barrier->lock);
    barrier->waiting++;

    if (barrier->waiting >= barrier->count) {
        // Let all waiting threads pass
        pthread_cond_broadcast(&barrier->cond);
        barrier->waiting = 0;
    } else {
        pthread_cond_wait(&barrier->cond, &barrier->lock);
    }    

    pthread_mutex_unlock(&barrier->lock);

    return 0;
}


int my_barrier_destroy(my_barrier_t *barrier) {
    pthread_mutex_destroy(&barrier->lock);
    pthread_cond_destroy(&barrier->cond);
    return 0;
}
