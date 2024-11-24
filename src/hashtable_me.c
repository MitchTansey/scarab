#include <stdio.h>
#include <stdlib.h>
#include "hashtable_me.h"

// Hash function for numeric keys.
static size_t hash(long long unsigned int key, size_t num_buckets) {
    return key % num_buckets;  // Simple modulus-based hash.
}

// Initialize the hashtable with a given number of buckets.
void hashtable_me_init(hashtable_t *table, size_t num_buckets) {
    table->buckets = calloc(num_buckets, sizeof(hashtable_entry_t *));
    if (!table->buckets) {
        fprintf(stderr, "Failed to allocate memory for hashtable buckets.\n");
        exit(EXIT_FAILURE);
    }
    table->num_buckets = num_buckets;
}

// Add a key-value pair to the hashtable (with overwrite handling).
void hashtable_me_add(hashtable_t *table, long long unsigned int key, void *value) {
    size_t index = hash(key, table->num_buckets);
    hashtable_entry_t *entry = table->buckets[index];

    // Check if the key already exists and overwrite if found.
    while (entry) {
        if (entry->key == key) {
            entry->value = value;  // Overwrite value.
            return;
        }
        entry = entry->next;
    }

    // If the key doesn't exist, create a new entry.
    entry = malloc(sizeof(hashtable_entry_t));
    if (!entry) {
        fprintf(stderr, "Failed to allocate memory for hashtable entry.\n");
        exit(EXIT_FAILURE);
    }

    entry->key = key;
    entry->value = value;
    entry->next = table->buckets[index];  // Insert at the head of the list.
    table->buckets[index] = entry;
}

// Look up a value by its numeric key.
void *hashtable_me_lookup(hashtable_t *table, long long unsigned int key) {
    size_t index = hash(key, table->num_buckets);
    hashtable_entry_t *entry = table->buckets[index];

    while (entry) {
        if (entry->key == key) {
            return entry->value;  // Return the value if the key matches.
        }
        entry = entry->next;
    }

    return NULL;  // Key not found.
}

// Remove a key-value pair from the hashtable.
void hashtable_me_remove(hashtable_t *table, long long unsigned int key) {
    size_t index = hash(key, table->num_buckets);
    hashtable_entry_t *entry = table->buckets[index];
    hashtable_entry_t *prev = NULL;

    while (entry) {
        if (entry->key == key) {
            if (prev) {
                prev->next = entry->next;
            } else {
                table->buckets[index] = entry->next;
            }
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

// Destroy the hashtable and free all memory.
void hashtable_me_destroy(hashtable_t *table) {
    for (size_t i = 0; i < table->num_buckets; i++) {
        hashtable_entry_t *entry = table->buckets[i];
        while (entry) {
            hashtable_entry_t *next = entry->next;
            free(entry);
            entry = next;
        }
    }
    free(table->buckets);
}
