#include "queue.h"


//----------
int queue_init(queue_t *queue, size_t item_size, size_t capacity) {
    // Initialise struct values
    queue->head = NULL;
    queue->tail = NULL;

    // Initialize the header
    queue->header.capacity = capacity;
    queue->header.item_size = item_size;
    queue->header.length = 0;

    return 0;
}

//----------
int queue_push(queue_t *queue, void *item, void *removed_item) {
    // If the queue is full, remove the item at the front
    int queue_is_full = 0;

    if (queue->header.length == queue->header.capacity) {
        queue_pop(queue, removed_item);
        queue_is_full = 1;
    }

    // Create a new node
    queue_node_t *new_node = (queue_node_t *) malloc(sizeof(queue_node_t));
    new_node->next = NULL;
    new_node->data = malloc(queue->header.item_size);

    memcpy(new_node->data, item, queue->header.item_size);

    // Add the new node to the queue
    if (queue->header.length == 0) {
        queue->head = new_node;
        queue->tail = new_node;
    } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }

    // queue length was decremented in pop if the queue was full
    queue->header.length++;   

    return queue_is_full;    
}

//----------
int queue_pop(queue_t *queue, void *item) {
    if (queue->header.length == 0) {
        return 1;
    }

    // Increment the queue head
    queue_node_t *node = queue->head;
    queue->head = node->next;
    queue->header.length--;

    // Check if the queue is now empty
    if (queue->header.length == 0) {
        queue->tail = NULL;
    }

    // Copy the old head's data to the item
    if (item != NULL && node->data != NULL) {
        memcpy(item, node->data, queue->header.item_size);
    }

    free(node->data);
    free(node);

    return 0;
}

//----------
int queue_head(queue_t *queue, void *item) {
    if (queue->header.length == 0) {
        return 1;
    }

    memcpy(item, queue->head->data, queue->header.item_size);

    return 0;
}

//----------
int queue_tail(queue_t *queue, void *item) {
    if (queue->header.length == 0) {
        return 1;
    }

    memcpy(item, queue->tail->data, queue->header.item_size);

    return 0;
}

//----------
size_t queue_length(queue_t *queue) {
    return queue->header.length;
}

//----------
size_t queue_capacity(queue_t *queue) {
    return queue->header.capacity;
}

//----------
size_t queue_item_size(queue_t *queue) {
    return queue->header.item_size;
}

//----------
int queue_is_empty(queue_t *queue) {
    return queue->header.length == 0;
}

//----------
void queue_destroy(queue_t *queue) {
    while (!queue_is_empty(queue)) {
        queue_pop(queue, NULL);
    }
}