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

// +---------------------------------------------------------------------------+
// |                           Public Interface                                |
// +---------------------------------------------------------------------------+

/**
 * @brief Initialise memory for an array on the heap
 * 
 * @param item_size Size of data type in bytes
 * @param initial_length Initial length of the array
 * @return `array` A pointer to the start of data
 */
void *array_init(size_t item_size, size_t initial_length);

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
 * @brief Adds an item to the end of an array
 * 
 * @param array 
 * @param item 
 * @return void* Pointer to the start of the array
 */
void *array_append(void *array, void *item);

/**
 * @brief Removes the last item from the array
 * 
 * @param array Pointer to the array
 * @param item Item that was removed. If NULL, the item is not returned
 * 
 * @return void* Pointer to the start of the array
 */
void *array_pop(void *array, void *item);

/**
 * @brief Retrieves the item at the given index
 * 
 * @param array 
 * @param index 
 * @param item The item at the given index
 * @return void* Pointer to the start of the array
 */
void *array_get(void *array, size_t index, void *item);

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
 * @warning Not thread-safe
 * 
 * @param array Pointer to the start of the array
 * @return void* 
 */
void *array_shuffle(void *array);

/**
 * @brief Converts a raw pointer to an `array` type
 * 
 * @param ptr Raw pointer defining a dynamic array
 * @param item_size Size of the data type in bytes
 * @param length Length of the array
 * @return void * Converted array type 
 */
void *raw_to_array(void *ptr, size_t item_size, size_t length);

/**
 * @brief Creates a deep copy of an array
 * 
 * @param array 
 * @return void* A pointer to the copy of the array
 */
void *array_copy(void *array);

/**
 * @brief Returns the size of an item in the array
 * 
 * @param array 
 * @return size_t 
 */
size_t array_item_size(void *array);


#endif // ARRAY_H