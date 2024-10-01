/**
 * @file queue.h
 * @author 500481433
 * @version 0.1
 * @date 2024-09-02
 * 
 * @brief A queue that can store any data type. If the capacity is 
 * set to -1, the queue will be unbounded, otherwise the queue will
 * behave like a circular buffer.
 * 
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// ==================== Types ====================

/**
 * @brief Node for a singly linked list
 * 
 */
typedef struct queue_node {
    void *data;
    struct queue_node *next;
} queue_node_t;

/**
 * @brief Struct to store the queue metadata
 * 
 */
typedef struct queue_header {
    size_t capacity;                    // Capacity initialised by user
    size_t item_size;                   // Size of data type in bytes
    size_t length;                      // Current number of items in queue
    char is_bounded;                    // 1 if the queue is bounded, 0 otherwise
} queue_header_t;

/**
 * @brief The queue data structure
 * 
 */
typedef struct queue {
    queue_node_t *head;
    queue_node_t *tail;
    queue_header_t header;
} queue_t;

// ==================== Public Interface ====================

/**
 * @brief Initialises 
 * 
 * @param queue A pointer to the queue
 * @param item_size Size of the data type being stored
 * @param capacity Maximum capacity of the queue. If set to -1, the queue is unbounded
 * 
 * @return int 0 if successful, 1 queue could not be initialised
 */
int queue_init(queue_t *queue, size_t item_size, size_t capacity);

/**
 * @brief Pushes an item onto the queue
 * 
 * @param queue 
 * @param item 
 * @param removed_item NULL if no item is removed
 * 
 * @return int 0 if successful, 1 if the queue is full
 */
int queue_push(queue_t *queue, void *item, void *removed_item);

/**
 * @brief Pops an item from the queue
 * 
 * @param queue 
 * @param item If item is NULL, the item is not returned
 * 
 * @return int 0 if successful, 1 if the queue is empty
 */
int queue_pop(queue_t *queue, void *item);

/**
 * @brief Returns the item at the front of the queue
 * without removing it
 * 
 * @param queue 
 * @param item
 * 
 * @return int 0 if successful, 1 if the queue is empty
 */
int queue_head(queue_t *queue, void *item);

/**
 * @brief The item at the back of the queue
 * 
 * @param queue 
 * @param item
 * 
 * @return int 0 if successful, 1 if the queue is empty
 */
int queue_tail(queue_t *queue, void *item);

/**
 * @brief Returns the number of items in the queue
 * 
 * @param queue 
 * @return size_t 
 */
size_t queue_length(queue_t *queue);

/**
 * @brief Returns the capacity of the queue
 * 
 * @param queue 
 * @return size_t 
 */
size_t queue_capacity(queue_t *queue);

/**
 * @brief Returns the size of the data type in bytes
 * 
 * @param queue 
 * @return size_t 
 */
size_t queue_item_size(queue_t *queue);

/**
 * @brief Returns 1 if the queue is empty, 0 otherwise
 * 
 * @param queue 
 * @return int 
 */
int queue_is_empty(queue_t *queue);

/**
 * @brief Destroys the queue and frees all memory
 * 
 * @param queue 
 */
void queue_destroy(queue_t *queue);


#endif