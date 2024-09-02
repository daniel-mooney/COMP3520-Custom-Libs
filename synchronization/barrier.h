#ifndef BARRIER_H
#define BARRIER_H

#include <pthread.h>

typedef struct barrier {
    pthread_mutex_t lock;
    pthread_cond_t cond;
    unsigned int count;
    unsigned int waiting;
} my_barrier_t;


int my_barrier_init(my_barrier_t *barrier, int count);

int my_barrier_wait(my_barrier_t *barrier);

int my_barrier_destroy(my_barrier_t *barrier);

#endif