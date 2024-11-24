#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stddef.h>  // For size_t

// Hashtable entry structure.
typedef struct hashtable_entry {
    long long unsigned int key;  // Numeric key (e.g., line_addr)
    void *value;  // Value associated with the key.
    struct hashtable_entry *next;  // Linked list for collision handling.
} hashtable_entry_t;

// Hashtable structure.
typedef struct {
    hashtable_entry_t **buckets;  // Array of bucket pointers (chaining).
    size_t num_buckets;           // Number of buckets in the table.
} hashtable_t;

// Function declarations.
void hashtable_me_init(hashtable_t *table, size_t num_buckets);
void hashtable_me_add(hashtable_t *table, long long unsigned int key, void *value);
void *hashtable_me_lookup(hashtable_t *table, long long unsigned int key);
void hashtable_me_remove(hashtable_t *table, long long unsigned int key);
void hashtable_me_destroy(hashtable_t *table);

#endif  // HASHTABLE_H
