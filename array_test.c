#include "data_structures/array.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {

    srand(time(NULL));

    int *numbers = array(int);

    for (int i = 0; i < 10; i++) {
        numbers = array_append(numbers, i);
    }

    // Print the array
    for (int i = 0; i < array_length(numbers); i++) {
        printf("%d ", numbers[i]);
    }

    printf("\n");

    array_shuffle(numbers);

    // Print the shuffled array
    for (int i = 0; i < array_length(numbers); i++) {
        printf("%d ", numbers[i]);
    }

    printf("\n");

    array_destroy(numbers);

    return 0;
}