#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <pthread.h>

typedef struct semaphore {
    signed int counter;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} my_semaphore_t;


/**
 * @brief Initialize a semaphore
 * 
 * @param sem 
 * @param init_value The initial value of the semaphore
 * @return
 */
int my_sem_init(my_semaphore_t *sem, int init_value);

/**
 * @brief Increments the semaphore counter
 * 
 * @param sem 
 * @return int 
 */
int my_sem_post(my_semaphore_t *sem);

/**
 * @brief Increments the semaphore counter by a specified value
 * 
 * @param sem 
 * @param value 
 * @return int 
 */
int my_sem_post_many(my_semaphore_t *sem, int value);

/**
 * @brief Waits on a semaphore if the counter is negative
 * 
 * @param sem 
 * @return int 
 */
int my_sem_wait(my_semaphore_t *sem);

int my_sem_destroy(my_semaphore_t *sem);


#endif