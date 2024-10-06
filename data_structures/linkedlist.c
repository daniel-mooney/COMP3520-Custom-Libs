#include "linkedlist.h"
#include <stdio.h>

// +---------------------------------------------------------------------------+
// |                           Static Functions                                |
// +---------------------------------------------------------------------------+

/**
 * @brief Creates a new node
 * 
 * @param item_size 
 * @param item 
 * @return linkedlist_node_t* Pointer to the new node
 */
static linkedlist_node_t *node_create(size_t item_size, const void *item) {
    linkedlist_node_t *node = (linkedlist_node_t *) malloc(sizeof(linkedlist_node_t));

    if (!node) {
        return NULL;
    }

    node->data = malloc(item_size);

    if (!node->data) {
        free(node);
        return NULL;
    }

    // Copy the item to the node
    memcpy(node->data, item, item_size);
    node->next = NULL;
    node->prev = NULL;

    return node;
}

/**
 * @brief De-allocates a node's memory
 * 
 * @param current 
 */
static void node_destroy(linkedlist_node_t *node) {
    free(node->data);
    free(node);
}

/**
 * @brief Inserts a node after the given node
 * 
 * @param prev_node 
 * @param insert_node 
 */
static void node_insert(linkedlist_node_t *prev_node, linkedlist_node_t *insert_node) {
    insert_node->next = prev_node->next;
    insert_node->prev = prev_node;

    if (prev_node->next) {
        prev_node->next->prev = insert_node;
    }

    prev_node->next = insert_node;
}

/**
 * @brief Detaches a node from the list
 * 
 * @param node 
 */
static void node_detach(linkedlist_node_t *node) {
    if (node->prev) {
        node->prev->next = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    }
}


// +---------------------------------------------------------------------------+
// |                           Public Functions                                |
// +---------------------------------------------------------------------------+


// --------------------
int linkedlist_init(linkedlist_t *list, size_t item_size) {
    list->head = NULL;
    list->tail = NULL;
    list->header.length = 0;
    list->header.item_size = item_size;

    return 0;
}


// --------------------
void linkedlist_destroy(linkedlist_t *list) {
    linkedlist_node_t *current = list->head;
    linkedlist_node_t *next;

    // Free each node in the list
    while (current) {
        next = current->next;
        node_destroy(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->header.length = 0;
}

size_t linkedlist_length(linkedlist_t *list) {
    return list->header.length;
}


// --------------------
size_t linkedlist_item_size(linkedlist_t *list) {
    return list->header.item_size;
}


// --------------------
int linkedlist_insert(linkedlist_t *list, size_t index, const void *item) {
    if (index > list->header.length) {
        return 1;
    }

    linkedlist_node_t *node = node_create(list->header.item_size, item);

    if (!node) {
        return 1;
    }

    if (index == 0) {
        node->next = list->head;
        
        if (list->head) {
            list->head->prev = node;
        }

        list->head = node;
    } else {
        linkedlist_node_t *current = list->head;

        // Traverse to the node at the given index
        for (size_t i = 0; i < index - 1; i++) {
            current = current->next;
        }

        // insert the new node after the current node
        node_insert(current, node);
    }

    if (index == list->header.length) {
        list->tail = node;
    }

    list->header.length++;

    return 0;
}

// --------------------
int linkedlist_remove(linkedlist_t *list, size_t index, void *item) {
    if (index >= list->header.length) {
        return 1;
    }

    linkedlist_node_t *current = list->head;

    // Traverse to the node at the given index
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    if (item) {
        memcpy(item, current->data, list->header.item_size);
    }

    node_detach(current);
    node_destroy(current);

    list->header.length--;

    return 0;
}

// --------------------
int linkedlist_append(linkedlist_t *list, const void *item) {
    return linkedlist_insert(list, list->header.length, item);
}

// --------------------
int linkedlist_pop(linkedlist_t *list, void *item) {
    return linkedlist_remove(list, list->header.length - 1, item);
}

// --------------------
int linkedlist_get(linkedlist_t *list, size_t index, void *item) {
    if (index >= list->header.length) {
        return 1;
    }

    linkedlist_node_t *current = list->head;

    // Traverse to the node at the given index
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }

    memcpy(item, current->data, list->header.item_size);

    return 0;
}

// --------------------
int linkedlist_from_raw(linkedlist_t *list, size_t item_size, size_t length, const void *raw) {
    linkedlist_init(list, item_size);

    const char *raw_ptr = (const char *) raw;

    for (size_t i = 0; i < length; i++) {
        linkedlist_append(list, raw_ptr + i * item_size);
    }

    return 0;
}

// --------------------
void linkedlist_sort(linkedlist_t *list, int (*compare)(const void *, const void *)) {
    linkedlist_node_t *current = list->head;
    linkedlist_node_t *next;

    while (current) {
        next = current->next;

        while (next) {
            if (compare(current->data, next->data) > 0) {
                void *temp = current->data;
                current->data = next->data;
                next->data = temp;
            }

            next = next->next;
        }

        current = current->next;
    }
}

// --------------------
int linkedlist_iter_init(
    linkedlist_iterator_t *iterator,
    linkedlist_t *list,
    int start,
    int reverse
) {
    if (abs(start) > list->header.length) {
        return 1;
    }

    size_t start_idx = start < 0 ? list->header.length + start : start;

    // Find the node at the start index
    linkedlist_node_t *current = list->head;

    for (size_t i = 0; i < start_idx; i++) {
        current = current->next;
    }

    iterator->next = current;
    iterator->reverse = reverse;
    iterator->item_size = list->header.item_size;

    return 0;
}

// --------------------
int linkedlist_iter_next(linkedlist_iterator_t *iterator, void *item) {
    if (!iterator->next) {
        return 1;
    }

    memcpy(item, iterator->next->data, iterator->item_size);

    if (iterator->reverse) {
        iterator->next = iterator->next->prev;
    } else {
        iterator->next = iterator->next->next;
    }

    return 0;
}