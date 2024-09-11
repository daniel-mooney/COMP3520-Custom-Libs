#include "array.h"


//----------
void *array_init(size_t item_size, size_t initial_length) {
    size_t init_size = item_size * initial_length + sizeof(struct array_header);
    struct array_header *header = malloc(init_size);
    void *ptr = NULL;           // pointer to the start of data

    // Initialise header values
    if (header) {
        header->length = initial_length;
        header->capacity = initial_length;
        header->item_size = item_size;

        ptr = header + 1;
    }

    return ptr;
}


//----------
void array_destroy(void *array) {
    struct array_header *h = array_header(array);
    free(h);

    return;
}


//----------
void *array_resize(void *array, size_t new_capacity) {
    // void *header at the start of allocated data
    struct array_header *h = array_header(array);
    size_t new_size = h->item_size * new_capacity + sizeof(struct array_header);

    h = realloc(h, new_size);
    
    return h != NULL ? (h + 1) : NULL;
}

//----------
void *array_append(void *array, void *item) {
    array = array_ensure_capacity(array, 1);

    // Location of array header may change after ensure_capacity
    struct array_header *h = array_header(array);

    char *data_ptr = array;

    if (array) {
        char *dest = data_ptr + h->length * h->item_size;
        memcpy(dest, item, h->item_size);
        h->length++;
    }

    return array;
}


//----------
size_t array_length(void *array) {
    struct array_header *h = array_header(array);
    return h->length;
}


//----------
size_t array_capacity(void *array) {
    struct array_header *h = array_header(array);
    return h->capacity;
}


//----------
struct array_header *array_header(void *array) {
    return (struct array_header *) array - 1;
}


//----------
void *array_data(void *array) {
    return array_header(array) + 1;
}


//----------
void *array_ensure_capacity(void *array, size_t n_append) {
    struct array_header *h = array_header(array);
    size_t req_capacity = h->length + n_append;

    if (req_capacity > h->capacity) {
        array = array_resize(array, req_capacity);
    }

    return array;
}


void *array_shuffle(void *array) {
    struct array_header *h = array_header(array);
    char *data_ptr = array;

    for (int i = 0; i < h->length; i++) {
        // Swap the elements with a random index
        int swap_index = rand() % h->length;

        void *temp = malloc(h->item_size);          // Variable size temp buffer
        char *curr_loc = data_ptr + (i * h->item_size);
        char *swap_loc = data_ptr + swap_index * h->item_size;

        // Swap the elements
        memcpy(temp, curr_loc, h->item_size);
        memcpy(curr_loc, swap_loc, h->item_size);
        memcpy(swap_loc, temp, h->item_size);

        free(temp);
    }

    return data_ptr;
}


//----------
void *raw_to_array(void *ptr, size_t item_size, size_t length) {
    void *array = array_init(item_size, length);

    if (array) {
        memcpy(array, ptr, item_size * length);
    }

    return array;
}

//----------
void *array_copy(void *array) {
    struct array_header *h = array_header(array);
    void *copy = array_init(h->item_size, h->length);

    if (copy) {
        memcpy(copy, array, h->item_size * h->length);
    }

    return copy;
}