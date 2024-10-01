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
 * @param current Pointer to the current node
 * @param reverse Flag to indicate if the iterator is in reverse
 * 
 */
typedef struct linkedlist_iterator {
    linkedlist_node_t *current;
    int reverse;
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
int linkedlist_insert(linkedlist_t *list, size_t index, const void *item);

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
 * @brief Create a linked list from a raw array
 * 
 * @param list A pointer to the linked list object
 * @param item_size The size of an item in the list
 * @param length The length of the raw array
 * @param raw A pointer to the raw array
 * @return int 0 if successful, 1 otherwise
 */
int linkedlist_from_raw(linkedlist_t *list, size_t item_size, size_t length, const void *raw);

/**
 * @brief Create an iterator for the list
 * 
 * @param list A pointer to the linked list object
 * @param start The index to start the iterator. Negative indices are from the end.
 * @param reverse Flag to indicate if the iterator should be in reverse
 * @return linkedlist_iterator_t The iterator object
 */
linkedlist_iterator_t linkedlist_iterator(linkedlist_t *list, int start, int reverse);

/**
 * @brief Get the next item from the iterator
 * 
 * @param iterator A pointer to the iterator object
 * @param item A pointer to the item to store the retrieved item
 * @return int 0 if successful, 1 if the end of the list is reached
 */
int linkedlist_next(linkedlist_iterator_t *iterator, void *item);

/**
 * @brief Get the previous item from the iterator
 * 
 * @param iterator A pointer to the iterator object
 * @param item A pointer to the item to store the retrieved item
 * @return int 0 if successful, 1 if the start of the list is reached
 */
int linkedlist_prev(linkedlist_iterator_t *iterator, void *item);


// +---------------------------------------------------------------------------+
// |                           Private Interface                               |
// +---------------------------------------------------------------------------+

/**
 * @brief Create a linked list node
 * 
 * @param item_size The size of the item in bytes
 * @param item A pointer to the item to store in the node
 * @return linkedlist_node_t* A pointer to the created node
 */
static linkedlist_node_t *node_create(size_t item_size, const void *item);

/**
 * @brief Destroy a linked list node
 * 
 * @param current A pointer to the node to destroy
 */
static void node_destory(linkedlist_node_t *current);

/**
 * @brief Insert a node after a given node
 * 
 * @param prev_node A pointer to the previous node
 * @param new_node A pointer to the new node
 */
static void node_insert(linkedlist_node_t *prev_node, linkedlist_node_t *insert_node);

/**
 * @brief Detach a node from the list
 * @note The memory for the node is not freed
 * 
 * @param node A pointer to the node to detach
 */
static void node_detach(linkedlist_node_t *node);


#endif // LINKEDLIST_H