/**
 * @file hashtable.h
 * @brief Implements a hashtable as an array of linked lists
 * 
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>

// +---------------------------------------------------------------------------+
// |                               Data Types                                  |
// +---------------------------------------------------------------------------+

/**
 * @brief A function which hashes the key value of a hashtable.
 * @note The return value should be between 0 and `n_buckets - 1`.
 * 
 * @param key A key from the hashtable
 * @param n_buckets The number of buckets in the hashtable
 * 
 * @return `unsigned int` The index of the bucket to place the key.
 * 
 */
typedef unsigned int (*ht_hashing_function)(const void *key, size_t n_buckets);


/**
 * @brief A function that tests the equality of two values
 * @note This should be defined for the key data type
 * 
 * @param a
 * @param b
 * 
 * @return `int` 1 if `a` equals `b`, otherwise 0.
 * 
 */
typedef int (*ht_equality_function)(const void *a, const void *b);


/**
 * @brief Deallocates the memory used by the key.
 * 
 * @param key A pointer to the key.
 * 
 */
typedef void (*ht_key_free)(void *key);


/**
 * @brief Creates a copy of a key value.
 * @note The return value should be dynamically allocated.
 * 
 * @param key A pointer to the key.
 * 
 * @return `void*` A pointer to the copied key.
 * 
 */
typedef void *(*ht_key_copy)(const void *key);


/**
 * @brief Deallocates the memory used by the value.
 * 
 * @param value A pointer to the value.
 * 
 */
typedef void (*ht_value_free)(void *value);


/**
 * @brief Creates a copy of a value.
 * @note The return value should be dynamically allocated.
 * 
 * @param value A pointer to the value.
 * 
 * @return `void*` A pointer to the copied value.
 * 
 */
typedef void *(*ht_value_copy)(const void *value);


/**
 * @struct memory_deallocator
 * @brief A struct for deallocating the memory used by the key and value.
 * 
 * @param key_free A function that deallocates the memory used by the key.
 * If NULL is passed, `free()` is used.
 * @param value_free A function that deallocates the memory used by the value.
 * If NULL is passed, `free()` is used.
 * @param key_copy A function that creates a copy of the key.
 * If NULL is passed, the assignment operator is used.
 * @param value_copy A function that creates a copy of the value.
 * If NULL is passed, the assignment operator is used.
 * 
 */
typedef struct ht_auxillary_functions {
    ht_key_free key_free;
    ht_value_free value_free;
    ht_key_copy key_copy;
    ht_value_copy value_copy;
} ht_auxillary_functions;


/**
 * @struct hashtable_entry
 * @brief A node for a hashtable entry.
 * @note Can form a linked list with other `hashtable entries`.
 * 
 * @param key The key of the hashtable entry.
 * @param value The value of the hashtable entry.
 * @param next A pointer to the next hashtable entry in the linked list.
 * 
 */
typedef struct hashtable_entry {
    void *key;
    void *value;
    struct hashtable_entry *next;
} hashtable_entry;


/**
 * @struct hashtable
 * @brief A hashtable data structure.
 * 
 * @param n_buckets The number of buckets in the hashtable.
 * @param key_size The size of the key data in bytes.
 * @param value_size The size of the value data in bytes.
 * @param table An array of pointers to hashtable entries.
 * @param hash A hashing function for the hashtable.
 * @param eq_func A function that tests the equality of two values.
 * If NULL is passed, `==` is used.
 * @param aux_funcs A struct for auxillary functions.
 * 
 */
typedef struct hashtable {
    int n_buckets;
    size_t key_size;
    size_t value_size;
    hashtable_entry **table;                // Array of pointers
    ht_hashing_function hash;
    ht_equality_function key_eq_func;
    ht_auxillary_functions aux_funcs;
} hashtable;


// +---------------------------------------------------------------------------+
// |                             MACROS                                        |
// +---------------------------------------------------------------------------+

#define HT_DEFAULT_SIZE 3000
#define HT_SUCCESS 1
#define HT_FAIL 0

/**
 * @brief Creates a new hashtable
 * 
 * @param key_type The data type of the key.
 * @param value_type The data type of the value.
 * @param hash_func The hashing function for the hashtable.
 * @param key_eq_func A function that tests the equality of two keys.
 * @param aux_funcs A struct containing deallocation and copy functions.
 * 
 * @return `hashtable*` A pointer to the hashtable.
 * 
 */
#define hashtable_create(key_type, value_type, hash_func, key_eq_func, aux_funcs) (\
    hashtable_init(sizeof(key_type), sizeof(value_type), \
        HT_DEFAULT_SIZE, hash_func, key_eq_func, aux_funcs))


// +---------------------------------------------------------------------------+
// |                             Functions                                     |
// +---------------------------------------------------------------------------+

/**
 * @brief Initialise a hashtable
 * 
 * @param hash_func The hashing function for the hashtable.
 * @param key_eq_func A function that tests the equality of two keys.
 * @param n_buckets The number of buckets in the hashtable.
 * @return hashtable* A pointer to the hashtable.
 */
hashtable *hashtable_init(
    size_t key_size,
    size_t value_size,
    size_t n_buckets,
    ht_hashing_function hash_func,
    ht_equality_function key_eq_func,
    ht_auxillary_functions aux_funcs
);

/**
 * @brief Deallocate the memory used by the hashtable.
 * 
 * @param ht A pointer to the hashtable.
 * 
 */
void hashtable_destroy(
    hashtable *ht
);

/**
 * @brief Deallocates all hashtable entries in a bucket.
 * 
 * @param ht_entry The first entry in a bucket.
 * @param aux_funcs A struct fspecifying the deallocation functions.
 * 
 */
static void hashtable_destory_bucket(
    hashtable_entry *ht_entry,
    ht_auxillary_functions aux_funcs
);


/**
 * @brief Insert a key-value pair into the hashtable.
 * @note If the key already exists, the value is updated.
 * 
 * @param ht A pointer to the hashtable.
 * @param key A dynamically allocated pointer to the key.
 * @param value A dynamically allocated pointer to the value.
 * 
 * @return `int` 1 if successful, otherwise 0.
 */
int hashtable_insert(
    hashtable *ht,
    const void *key,
    const void *value
);


/**
 * @brief Insert a key-value pair into a hashtable bucket.
 * @note if the key already exists, the value is updated.
 * 
 * @param ht A pointer to the hashtable.
 * @param key A dynamically allocated pointer to the key.
 * @param value A dynamically allocated pointer to the value.
 * @param bucket_index The index of the bucket.
 * 
 * @return `int` 1 if successful, otherwise 0. 
 */
static int bucket_insert(
    hashtable *ht,
    const void *key,
    const void *value,
    unsigned int bucket_index
);

/**
 * @brief Replace the value of a hashtable entry.
 * 
 * @param ht A pointer to the hashtable.
 * @param ht_entry A pointer to the hashtable entry.
 * @param new_value A pointer to the new value.
 * 
 * @return `int` 1 if successful, otherwise 0.
 * 
 */
static int replace_value(
    hashtable* ht,
    hashtable_entry *ht_entry,
    const void *new_value
);


/**
 * @brief Initialise a hashtable entry.
 * @note The hashtable entry is dynamically allocated.
 * 
 * @param key 
 * @param value 
 * @return `hashtable_entry*` A pointer to the hashtable entry. 
 */
static hashtable_entry *entry_init(
    hashtable *ht,
    const void *key,
    const void *value
);


/**
 * @brief Remove a key-value pair from the hashtable.
 * 
 * @param ht A pointer to the hashtable.
 * @param key A pointer to the key.
 * 
 * @return `int` 1 if successful, otherwise 0. 
 */
int hashtable_remove(
    hashtable *ht,
    const void *rm_key
);

/**
 * @brief Remove a key-value pair from a hashtable bucket.
 * 
 * @param ht A pointer to the hashtable.
 * @param key A pointer to the key.
 * @param bucket_index Index of the bucket that holds the key
 * @return `int` 1 if successful, otherwise 0. 
 */
static int entry_remove(
    hashtable *ht,
    const void *key,
    unsigned int bucket_index
);


/**
 * @brief Get the value of a key in the hashtable.
 * 
 * @param ht A pointer to the hashtable.
 * @param key A pointer to the key.
 * @return `void*` A pointer  
 */
const void *hashtable_get(hashtable *ht, const void *key);


/**
 * @brief Get the value of a key from a bucket linked list.
 * 
 * @param ht A pointer to the hashtable.
 * @param bucket_index Index of the bucket that holds the key
 * @param key The key to search for.
 * @return const void* A pointer to the value.
 */
static const void *bucket_get(
    hashtable *ht,
    unsigned int bucket_index,
    const void *key
);


/**
 * @todo
 * @brief Check if a key exists in the hashtable.
 * 
 * @param ht A pointer to the hashtable.
 * @param key A pointer to the key.
 * @return `int` 1 if the key exists, otherwise 0. 
 */
int hashtable_contains(hashtable *ht, const void *key);


/**
 * @todo
 * @brief Gets the keys of a hashtable.
 * @note The keys are dynamically allocated and should be freed after use.
 * 
 * @param ht The hashtable to get the keys from.
 * @return `void**` A dynamically allocated array of pointers to keys.
 */
void **hashtable_keys(hashtable *ht);


#endif