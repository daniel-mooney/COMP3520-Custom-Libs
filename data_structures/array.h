/**
 * @file array.h
 * @author 500481433
 * @brief Dynamic array implementation in C
 * @version 0.1
 * @date 2024-09-02
 * 
 * @cite Inspired by the C++ STL vector class and the Dynamic Arrays
 * video by Dylan Falconer:
 * 
 * https://www.youtube.com/watch?v=_KSKH8C9Gf0
 * 
 */


#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// -------------------- Types

// @todo add custom allocator
struct array_header {
    size_t capacity;
    size_t length;
    size_t item_size;
};

// -------------------- Macros

/**
 * @brief Initialise an array of a given type
 * @note Capacity is initially 0
 * 
 * @param type 
 * The type of the array e.g. `int`, `char *`, ...
 * 
 * @return `array` Pointer to the start of the array
 * 
 */
#define array(type) (type *) array_init(sizeof(type), 0)


/**
 * @brief Append an item to the end of an array
 * 
 * @param array Pointer to the start of the array
 * @param item The item to append
 * 
 * @return `array` Pointer to the start of the array
 */
#define array_append(array, item) (\
    (array) = array_ensure_capacity(array, 1), \
    (array)[array_header(array)->length++] = (item), \
    (array))


/**
 * @brief Remove the last item from an array
 * 
 */
#define array_pop(array) (\
    (array_header(array)->length > 0) ? \
    (array_header(array)->length--, (array)) : \
    (array))


// +---------------------------------------------------------------------------+
// |                           Public Interface                                |
// +---------------------------------------------------------------------------+

/**
 * @brief Initialise memory for an array on the heap
 * 
 * @param item_size Size of data type in bytes
 * @param initial_capacity
 * @return `array` A pointer to the start of data
 */
void *array_init(size_t item_size, size_t initial_capacity);

/**
 * @brief Free the memory allocated for an array
 * 
 * @param array Pointer to the start of the array
 */
void array_destroy(void *array);


/**
 * @brief Change the capacity of an array
 * @note If the new capacity is less than the current length, 
 * the length will be truncated.
 * 
 * @param array Pointer to the start of the array
 * @param new_capacity 
 * @return `array` Pointer to the start of the array
 */
void *array_resize(void *array, size_t new_capacity);


/**
 * @brief Get the length of an array
 * 
 * @param array Pointer to the start of the array
 * @return size_t The length
 */
size_t array_length(void *array);


/**
 * @brief Get the capacity of an array
 * 
 * @param array Pointer to the start of the array
 * @return size_t The capacity
 */
size_t array_capacity(void *array);

/**
 * @brief Shuffles the elements of an array in place
 * @note Change the seed of the RNG by using `srand()`
 * 
 * @param array Pointer to the start of the array
 * @return void* 
 */
void *array_shuffle(void *array);


// +---------------------------------------------------------------------------+
// |                           Private Interface                               |
// +---------------------------------------------------------------------------+

/**
 * @brief Retrieve the array header of an array
 * 
 * @param array Pointer to the start of the array
 * @return struct array_header* 
 */
struct array_header *array_header(void *array);

/**
 * @brief Returns a pointer to the start of the data in the array
 * 
 * @param array 
 * @return void* 
 */
void *array_data(void *array);


/**
 * @brief Ensures that the array has enough capacity to append n_append items.
 * Allocates more memory if necessary
 * 
 * @param array Pointer to the start of the array
 * @param n_append Number of items allow space for
 * @return `array` Pointer to the start of the array
 */
void *array_ensure_capacity(void *array, size_t n_append);


// /**
//  * @todo
//  * @brief Converts a raw pointer to an `array` type
//  * 
//  * @param ptr Raw pointer defining a dynamic array
//  * @param length Length of the array
//  * @return `array` Converted array type 
//  */
// void *raw_to_array(void *ptr, size_t length);



#endif // ARRAY_H