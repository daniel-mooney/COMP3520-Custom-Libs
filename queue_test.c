#include "data_structures/queue.h"
#include <stdio.h>


int main() {

    queue_t num_queue;
    queue_init(&num_queue, sizeof(int), 5);

    for (int i = 0; i < 7; i++) {
        printf("Pushing %d\n", i);

        int removed_item;

        if (queue_push(&num_queue, &i, &removed_item)) {
            printf("Queue is full, removing %d\n", removed_item);
        }
    }

    while (queue_length(&num_queue) > 0) {
        int num;
        queue_pop(&num_queue, &num);
        printf("popping %d\n", num);
    }

    return 0;
}