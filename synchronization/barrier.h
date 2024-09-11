#ifndef BARRIER_H
#define BARRIER_H

#include <pthread.h>

typedef struct barrier {
    unsigned int count;             // Number of threads the barrier can hold
    unsigned int waiting;           // Number of threads waiting at the barrier
    unsigned int passed;            // Number of threads that have passed the barrier
    pthread_mutex_t lock;
    pthread_cond_t cond;
    pthread_cond_t reset_cond;      // Reset the barrier when all threads have passed
} my_barrier_t;

/**
 * @brief Initialize a barrier
 * 
 * @param barrier 
 * @param count The number of threads that must call my_barrier_wait() before the barrier is released
 * @return int 
 */
int my_barrier_init(my_barrier_t *barrier, int count);

/**
 * @brief Wait for all threads to reach the barrier
 * @note This function blocks until all threads have reached the barrier
 * 
 * @param barrier 
 * @return int 
 */
int my_barrier_wait(my_barrier_t *barrier);

/**
 * @brief Destroys the barrier
 * 
 * @param barrier 
 * @return int 
 */
int my_barrier_destroy(my_barrier_t *barrier);

#endif