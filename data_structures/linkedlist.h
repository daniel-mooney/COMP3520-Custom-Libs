#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include <string.h>

// -------------------- Types
/**
 * @brief A node in a doubly linked list
 * 
 * @param data Pointer to the data stored in the node
 * @param next Pointer to the next node in the list
 * @param prev Pointer to the previous node in the list
 * 
 */
typedef struct linkedlist_node {
    void *data;
    struct linkedlist_node *next;
    struct linkedlist_node *prev;
} linkedlist_node_t;

/**
 * @brief Header for a doubly linked list
 * 
 * @param length Number of items in the list
 * @param item_size Size of each item in bytes
 * 
 */
typedef struct linkedlist_header {
    size_t length;
    size_t item_size;
} linkedlist_header_t;

/**
 * @brief A linked list object
 * 
 * @param head Pointer to the first node in the list
 * @param tail Pointer to the last node in the list
 * @param header Header for the list
 * 
 */
typedef struct linkedlist {
    linkedlist_node_t *head;
    linkedlist_node_t *tail;
    linkedlist_header_t header;
} linkedlist_t;

/**
 * @brief An iterator for a linked list
 * 
 * @param next Pointer to the next node in the list
 * @param reverse Flag to indicate if the iterator is in reverse
 * 
 */
typedef struct linkedlist_iterator {
    linkedlist_node_t *next;
    int reverse;
    size_t item_size;
} linkedlist_iterator_t;


/**
 * @brief Initialise a linked list
 * 
 * @param list A pointer to the linked list object
 * @param item_size The size of an item in the list
 * @return int 0 if successful, 1 otherwise
 */
int linkedlist_init(linkedlist_t *list, size_t item_size);

/**
 * @brief Destroy a linked list
 * 
 * @param list A pointer to the linked list object
 */
void linkedlist_destroy(linkedlist_t *list);

/**
 * @brief Get the length of the list
 * 
 * @param list A pointer to the linked list object
 * @return size_t The length of the list
 */
size_t linkedlist_length(linkedlist_t *list);

/**
 * @brief Check if the list is empty
 * 
 * @param list A pointer to the linked list object
 * @return int 1 if the list is empty, 0 otherwise
 */
int linkedlist_empty(linkedlist_t *list);

/**
 * @brief Get the size of an item in the list
 * 
 * @param list A pointer to the linked list object
 * @return size_t The size of an item in the list
 */
size_t linkedlist_item_size(linkedlist_t *list);

/**
 * @brief Insert an item at the given index
 * @note If the index is invalid, the item is not inserted
 * 
 * @param list A pointer to the linked list object
 * @param index The index to insert the item
 * @param item A pointer to the item to insert
 * @return int 0 if successful, 1 otherwise
 */
int linkedlist_insert(
    linkedlist_t *list,
    size_t index,
    const void *item
);

/**
 * @brief Remove the item at the given index
 * 
 * @param list A pointer to the linked list object
 * @param index The index of the item to remove
 * @param item A pointer to the item to store the removed item
 * @return int 0 if successful, 1 otherwise
 */
int linkedlist_remove(linkedlist_t *list, size_t index, void *item);

/**
 * @brief Append an item to the end of the list
 * @note A copy of the item is stored in the list
 * 
 * @param list A pointer to the linked list object
 * @param item A pointer to the item to append
 * @return int 0 if successful, 1 otherwise
 */
int linkedlist_append(linkedlist_t *list, const void *item);

/**
 * @brief Pop an item from the end of the list
 * 
 * @param list A pointer to the linked list object
 * @param item A pointer to the item to store the popped item
 * @return int 0 if successful, 1 otherwise
 */
int linkedlist_pop(linkedlist_t *list, void *item);

/**
 * @brief Get the item at the given index
 * 
 * @param list A pointer to the linked list object
 * @param index The index of the item to get
 * @param item A pointer to the item to store the retrieved item
 * @return int 0 if successful, 1 otherwise
 */
int linkedlist_get(linkedlist_t *list, size_t index, void *item);

/**
 * @brief Get the head of the list
 * 
 * @param list A pointer to the linked list object
 * @param item A pointer to the item to store the head
 * @return int 0 if successful, 1 otherwise
 */
int linkedlist_head(linkedlist_t *list, void *item);

/**
 * @brief Get the tail of the list
 * 
 * @param list A pointer to the linked list object
 * @param item A pointer to the item to store the tail
 * @return int 0 if successful, 1 otherwise
 */
int linkedlist_tail(linkedlist_t *list, void *item);

/**
 * @brief Copy the contents of one list to another
 * 
 * @param dest A pointer to the destination linked list object
 * @param src A pointer to the source linked list object
 * @return int 0 if successful, 1 otherwise
 */
int linkedlist_copy(linkedlist_t *dest, linkedlist_t *src);

/**
 * @brief Sort the list in place
 * 
 * @param list A pointer to the linked list object
 * @param compare A function to compare two items
 */
void linkedlist_sort(
    linkedlist_t *list,
    int (*compare)(const void *, const void *)
);


/**
 * @brief Create a linked list from a raw array
 * 
 * @param list A pointer to the linked list object
 * @param item_size The size of an item in the list
 * @param length The length of the raw array
 * @param raw A pointer to the raw array
 * @return int 0 if successful, 1 otherwise
 */
int linkedlist_from_raw(
    linkedlist_t *list,
    size_t item_size,
    size_t length,
    const void *raw
);

/**
 * @brief Create an iterator for the list
 * 
 * @param iterator A pointer to the iterator object
 * @param list A pointer to the linked list object
 * @param start The index to start the iterator. Negative indices are from the end.
 * @param reverse Flag to indicate if the iterator should be in reverse
 * @return int 0 if successful, 1 otherwise
 */
int linkedlist_iter_init(
    linkedlist_iterator_t *iterator,
    linkedlist_t *list,
    int start,
    int reverse
);

/**
 * @brief Get the next item from the iterator
 * 
 * @param iterator A pointer to the iterator object
 * @param item A pointer to the item to store the retrieved item
 * @return int 0 if successful, 1 if the end of the list is reached
 */
int linkedlist_iter_next(linkedlist_iterator_t *iterator, void *item);

#endif // LINKEDLIST_H