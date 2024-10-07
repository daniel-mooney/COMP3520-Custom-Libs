#include "data_structures/deque.h"
#include <stdio.h>

int main() {
    int items[] = {1, 2, 3, 4, 5};

    deque_t deque;
    deque_from_raw(&deque, sizeof(int), 5, items);

    printf("Length: %zu\n", deque_length(&deque));
    printf("Item size: %zu\n", deque_item_size(&deque));

    int item;
    deque_pop_front(&deque, &item);

    printf("Popped item: %d\n", item);

    deque_push_front(&deque, &item);

    deque_front(&deque, &item);
    printf("Front: %d\n", item);

    deque_back(&deque, &item);
    printf("Back: %d\n", item);

    deque_destroy(&deque);
    return 0;
}