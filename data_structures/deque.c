#include "deque.h"

int deque_init(deque_t *deque, size_t item_size) {
    return linkedlist_init(deque, item_size);
}

void deque_destroy(deque_t *deque) {
    linkedlist_destroy(deque);
}

size_t deque_length(deque_t *deque) {
    return linkedlist_length(deque);
}

int deque_empty(deque_t *deque) {
    return linkedlist_empty(deque);
}

size_t deque_item_size(deque_t *deque) {
    return linkedlist_item_size(deque);
}

int deque_push_front(deque_t *deque, const void *item) {
    return linkedlist_insert(deque, 0, item);
}

int deque_push_back(deque_t *deque, const void *item) {
    return linkedlist_append(deque, item);
}

int deque_pop_front(deque_t *deque, void *item) {
    return linkedlist_remove(deque, 0, item);
}

int deque_pop_back(deque_t *deque, void *item) {
    return linkedlist_pop(deque, item);
}

int deque_front(deque_t *deque, void *item) {
    return linkedlist_head(deque, item);
}

int deque_back(deque_t *deque, void *item) {
    return linkedlist_tail(deque, item);
}

int deque_copy(deque_t *dest, deque_t *src) {
    return linkedlist_copy(dest, src);
}

int deque_from_raw(
    deque_t *deque,
    size_t item_size,
    size_t length,
    const void *raw
) {
    return linkedlist_from_raw(deque, item_size, length, raw);
}