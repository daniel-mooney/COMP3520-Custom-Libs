#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <pthread.h>

typedef struct semaphore {
    signed int counter;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} my_semaphore_t;


int my_sem_init(my_semaphore_t *sem, int init_value);

int my_sem_post(my_semaphore_t *sem);

int my_sem_post_many(my_semaphore_t *sem, int value);

int my_sem_wait(my_semaphore_t *sem);

int my_sem_destroy(my_semaphore_t *sem);


#endif