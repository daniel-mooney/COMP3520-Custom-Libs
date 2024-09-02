#include "hashtable.h"
#include "array.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//----------
hashtable *hashtable_init(
    size_t key_size,
    size_t value_size,
    size_t n_buckets,
    ht_hashing_function hash_func,
    ht_equality_function key_eq_func,
    ht_auxillary_functions aux_funcs
) {

    // Use free() as default deallocator
    if (aux_funcs.key_free == NULL) {
        aux_funcs.key_free = free;
    }

    if (aux_funcs.value_free == NULL) {
        aux_funcs.value_free = free;
    }

    hashtable *ht = malloc(sizeof(hashtable));

    // Assign values if successful memory allocation
    if (ht) {
        ht->table = calloc(n_buckets, sizeof(hashtable_entry *));

        if (ht->table) {
            ht->key_size = key_size;
            ht->value_size = value_size;
            ht->n_buckets = n_buckets;
            ht->hash = hash_func;
            ht->key_eq_func = key_eq_func;
            ht->aux_funcs = aux_funcs;
        } else {
            // If table alloc failed, destroy hashtable
            free(ht);
            ht = NULL;
        }
    }

    return ht;
}


//----------
void hashtable_destroy(
    hashtable *ht
) {
    // Free each bucket
    for (int i = 0; i < ht->n_buckets; i++) {
        hashtable_destory_bucket(
            ht->table[i],
            ht->aux_funcs
        );
    }

    free(ht->table);
    free(ht);
    return;
}


//----------
void hashtable_destory_bucket(
    hashtable_entry *ht_entry,
    ht_auxillary_functions aux_funcs
) {
    if (ht_entry == NULL) return;

    // post-order traversal
    hashtable_destory_bucket(
        ht_entry->next,
        aux_funcs
    );

    aux_funcs.key_free(ht_entry->key);
    aux_funcs.value_free(ht_entry->value);

    free(ht_entry);
    return;
}


//----------
int hashtable_insert(
    hashtable *ht,
    const void *key,
    const void *value
) {
    unsigned int bucket_index = ht->hash(key, ht->n_buckets);
    return bucket_insert(ht, key, value, bucket_index);
}


//----------
int bucket_insert(
    hashtable *ht,
    const void *key,
    const void *value,
    unsigned int bucket_index
) {
    hashtable_entry *bucket_head = ht->table[bucket_index];
    hashtable_entry *new_entry = NULL;

    // If bucket is empty, create new entry at head
    if (bucket_head == NULL) {
        new_entry = entry_init(ht, key, value);
        ht->table[bucket_index] = new_entry;

        return new_entry != NULL;
    }

    // Update value if equal
    if (ht->key_eq_func(bucket_head->key, key)) {
        return replace_value(ht, bucket_head, value);
    }

    // Iterate through the linked list
    hashtable_entry *curr_entry = bucket_head;

    while (curr_entry->next != NULL) {

        // Update value if key is equal
        if (ht->key_eq_func(curr_entry->next->key, key)) {
            return replace_value(ht, curr_entry->next, value);
        }

        curr_entry = curr_entry->next;
    }

    // Append to the end of the linked list
    new_entry = entry_init(ht, key, value);
    curr_entry->next = new_entry;

    return new_entry != NULL;
}


int replace_value(
    hashtable* ht,
    hashtable_entry *ht_entry,
    const void *new_value
) {
    void *new_value_dyn = NULL;             // new value on the heap

    // Copy new_value, use memcpy if no value_copy function
    if (ht->aux_funcs.value_copy) {
        new_value_dyn = ht->aux_funcs.value_copy(new_value);
    } else {
        if ((new_value_dyn = malloc(ht->value_size))) {
            memcpy(new_value_dyn, new_value, ht->value_size);
        }
    }

    // Memory allocation failed
    if (!new_value_dyn) {
        return HT_FAIL;
    }

    ht->aux_funcs.value_free(ht_entry->value);
    ht_entry->value = new_value_dyn;

    return HT_SUCCESS;
}


hashtable_entry *entry_init(
    hashtable *ht,
    const void *key,
    const void *value
) {
    hashtable_entry *ht_entry = malloc(sizeof(hashtable_entry));

    if (ht_entry) {
        // Copy key, use memcpy if no key_copy function
        if (ht->aux_funcs.key_copy) {
            ht_entry->key = ht->aux_funcs.key_copy(key);
        } else {
            if ((ht_entry->key = malloc(ht->key_size))) {
                memcpy(ht_entry->key, key, ht->key_size);
            }
        }
        
        // Copy value, use memcpy if no value_copy function
        if (ht->aux_funcs.value_copy) {
            ht_entry->value = ht->aux_funcs.value_copy(value);
        } else {
            if ((ht_entry->value = malloc(ht->value_size))) {
                memcpy(ht_entry->value, value, ht->value_size);
            }
        }

        ht_entry->next = NULL;
    }

    // Free memory if failed key or value allocation
    if (!ht_entry->key || !ht_entry->value) {
        free(ht_entry->key);
        free(ht_entry->value);
        free(ht_entry);
        return NULL;
    }

    return ht_entry;
}

//----------
int hashtable_remove(hashtable *ht, const void *key) {
    unsigned int bucket_index = ht->hash(key, ht->n_buckets);
    return entry_remove(ht, key, bucket_index);
}

//----------
int entry_remove(
    hashtable *ht,
    const void *rm_key,
    unsigned int bucket_index
) {
    hashtable_entry *bucket_head = ht->table[bucket_index];

    if (bucket_head == NULL) return HT_FAIL;

    if (ht->key_eq_func(bucket_head->key, rm_key)) {
        ht->table[bucket_index] = bucket_head->next;

        ht->aux_funcs.key_free(bucket_head->key);
        ht->aux_funcs.value_free(bucket_head->value);
        free(bucket_head);

        return HT_SUCCESS;
    }

    // Iterate through the linked list, remove if key is equal
    hashtable_entry *curr_entry = bucket_head;

    while (curr_entry->next != NULL) {
        if (ht->key_eq_func(curr_entry->next->key, rm_key)) {
            // Disconnect from linked list
            hashtable_entry *temp = curr_entry->next;
            curr_entry->next = curr_entry->next->next;

            // Free memory
            ht->aux_funcs.key_free(temp->key);
            ht->aux_funcs.value_free(temp->value);
            free(temp);

            return HT_SUCCESS;
        }

        curr_entry = curr_entry->next;
    }

    // Key is not found
    return HT_FAIL;
}


const void *hashtable_get(hashtable *ht, const void *key) {
    unsigned int bucket_index = ht->hash(key, ht->n_buckets);
    return bucket_get(ht, bucket_index, key);
}


const void *bucket_get(
    hashtable *ht,
    unsigned int bucket_index,
    const void *key
) {
    hashtable_entry *bucket_head = ht->table[bucket_index];

    if (bucket_head == NULL) return NULL;

    if (ht->key_eq_func(bucket_head->key, key)) {
        return bucket_head->value;
    }

    // Iterate through the linked list
    hashtable_entry *curr_entry = bucket_head;

    while (curr_entry->next != NULL) {
        if (ht->key_eq_func(curr_entry->next->key, key)) {
            return curr_entry->next->value;
        }

        curr_entry = curr_entry->next;
    }

    // Key is not found
    return NULL;

}


int hashtable_contains(hashtable *ht, const void *key) {
    unsigned int bucket_index = ht->hash(key, ht->n_buckets);
    hashtable_entry *bucket_head = ht->table[bucket_index];

    if (bucket_head == NULL) return false;
    if (ht->key_eq_func(bucket_head->key, key)) return true;

    // Iterate through linked list
    hashtable_entry *curr_entry = bucket_head;

    while (curr_entry->next != NULL) {
        if (ht->key_eq_func(curr_entry->next->key, key)) return true;

        curr_entry = curr_entry->next;
    }

    return false;
}


// void **hashtable_keys(hashtable *ht) {
    
// }