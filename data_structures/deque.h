#ifndef DEQUE_H
#define DEQUE_H

#include "linkedlist.h"

typedef linkedlist_t deque_t;


/**
 * @brief Initialise a deque
 * 
 * @param deque A pointer to the deque object
 * @param item_size The size of an item in the deque
 * @return int 0 if successful, 1 otherwise
 */
int deque_init(deque_t *deque, size_t item_size);

/**
 * @brief Destroy a deque
 * 
 * @param deque A pointer to the deque object
 */
void deque_destroy(deque_t *deque);

/**
 * @brief Get the length of the deque
 * 
 * @param deque A pointer to the deque object
 * @return size_t The length of the deque
 */
size_t deque_length(deque_t *deque);

/**
 * @brief Get the size of an item in the deque
 * 
 * @param deque A pointer to the deque object
 * @return size_t The size of an item in the deque
 */
size_t deque_item_size(deque_t *deque);

/**
 * @brief Push an item to the front of the deque
 * 
 * @param deque A pointer to the deque object
 * @param item A pointer to the item to push
 * @return int 0 if successful, 1 otherwise
 */
int deque_push_front(deque_t *deque, const void *item);

/**
 * @brief Push an item to the back of the deque
 * 
 * @param deque A pointer to the deque object
 * @param item A pointer to the item to push
 * @return int 0 if successful, 1 otherwise
 */
int deque_push_back(deque_t *deque, const void *item);

/**
 * @brief Pop an item from the front of the deque
 * 
 * @param deque A pointer to the deque object
 * @param item A pointer to the item to store the popped item
 * @return int 0 if successful, 1 otherwise
 */
int deque_pop_front(deque_t *deque, void *item);

/**
 * @brief Pop an item from the back of the deque
 * 
 * @param deque A pointer to the deque object
 * @param item A pointer to the item to store the popped item
 * @return int 0 if successful, 1 otherwise
 */
int deque_pop_back(deque_t *deque, void *item);

/**
 * @brief Get the front of the deque
 * 
 * @param deque A pointer to the deque object
 * @param item A pointer to the item to store the front
 * @return int 0 if successful, 1 otherwise
 */
int deque_front(deque_t *deque, void *item);

/**
 * @brief Get the back of the deque
 * 
 * @param deque A pointer to the deque object
 * @param item A pointer to the item to store the back
 * @return int 0 if successful, 1 otherwise
 */
int deque_back(deque_t *deque, void *item);

/**
 * @brief Copy the deque
 * 
 * @param dest A pointer to the destination deque object
 * @param src A pointer to the source deque object
 * @return int 0 if successful, 1 otherwise
 */
int deque_copy(deque_t *dest, deque_t *src);

/**
 * @brief Create a deque from raw data
 * 
 * @param deque A pointer to the deque object
 * @param item_size The size of an item in the deque
 * @param length The length of the raw data
 * @param raw A pointer to the raw data
 * @return int 0 if successful, 1 otherwise
 */
int deque_from_raw(
    deque_t *deque,
    size_t item_size,
    size_t length,
    const void *raw
);

/**
 * @brief Check if the deque is empty
 * 
 * @param deque A pointer to the deque object
 * @return int 1 if empty, 0 otherwise
 */
int deque_empty(deque_t *deque);

#endif