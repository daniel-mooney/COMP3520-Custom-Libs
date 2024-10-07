#include "data_structures/deque.h"
#include <stdio.h>

int main() {
    int items[] = {1, 2, 3, 4, 5};

    deque_t deque;
    deque_from_raw(&deque, sizeof(int), 5, items);

    printf("Length: %zu\n", deque_length(&deque));
    printf("Item size: %zu\n", deque_item_size(&deque));
    printf("Empty: %d\n", deque_empty(&deque));

    int item;
    deque_pop_front(&deque, &item);

    printf("Popped item: %d\n", item);

    item = 6;
    deque_push_front(&deque, &item);

    deque_front(&deque, &item);
    printf("Front: %d\n", item);

    deque_back(&deque, &item);
    printf("Back: %d\n", item);

    printf("Length: %zu\n", deque_length(&deque));

    for (int i = 0; deque_length(&deque) > 0; i++) {
        deque_pop_front(&deque, &item);
        printf("Popped item: %d\n", item);
    }

    printf("Length: %zu\n", deque_length(&deque));
    printf("Empty: %d\n", deque_empty(&deque));

    deque_destroy(&deque);
    return 0;
}