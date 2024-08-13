#include <stdlib.h>
#include <string.h>

#include "map.h"

static map_item* map_new_item(const char*, const char*);
map* map_new();
static void map_del_item(map_item*);
void map_del(map*);
static int map_hash(const char*, const int, const int);
static int map_get_hash(const char*, const int, const int);
void map_insert(map*, const char*, const char*);

static map_item MAP_DELETED_ITEM = {NULL, NULL};
/*
typedef struct {
    char* key;
    char* value;
} map_item;

typedef struct {
    int size;
    int count;
    map_item** items; // array of pointers to map_item
} map;
*/


// Allocate memory for a new map_item and copy the key and value into it
static map_item* map_new_item(const char* k, const char* v) {
    map_item* i;
    i = malloc(sizeof(map_item));
    i->key = strdup(k);
    i->value = strdup(v);
    return i;
}

// Create a new map and allocate memory for the items array
map* map_new() {
    map* mp;

    mp = malloc(sizeof(map));
    mp->size = 53;
    mp->count = 0;
    mp->items = calloc((size_t)mp->size, sizeof(map_item*));
    return mp;
}

// Free the memory for the map and all its items
void map_del(map* mp) {
    int i;
    map_item* item;

    for (i = 0; i < mp->size; i++) {
        item = mp->items[i];
        if (item != NULL) {
            map_del_item(item);
        }
    }
    free(mp->items);
    free(mp);
}

// Free the memory for a map_item
static void map_del_item(map_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}

// Hash function
// s: string to hash, a: prime number, m: bucket size
static int map_hash(const char* s, const int a, const int m) {
    long hash;
    int i;
    const int len_s = strlen(s);

    hash = 0;
    for (i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i+1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}

// Get the index of the key in the map using Double Hashing for handling collisions
static int map_get_hash(const char* s, const int num_buckets, const int attempt) {
    const int hash_a = map_hash(s, 151, num_buckets);
    const int hash_b = map_hash(s, 163, num_buckets);

    // hash_b + 1 to avoid loop with hash_b returning 0
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

// Insert a key-value pair into the map
void map_insert(map* mp, const char* key, const char* value) {
    map_item *item, *curr_item;
    int index, i;

    item = map_new_item(key, value);
    index = map_get_hash(item->key, mp->size, 0);
    curr_item = mp->items[index];
    i = 1;

    // calcualte hash index until an empty bucket is found
    while (curr_item != NULL && curr_item != &MAP_DELETED_ITEM) {
        // if the key already exists, update the value
        if (curr_item != &MAP_DELETED_ITEM) {
            if (strcmp(curr_item->key, key) == 0) {
                map_del_item(curr_item);
                mp->items[index] = item;
                return;
            }
        }

        index = map_get_hash(item->key, mp->size, i);
        curr_item = mp->items[index];
        i++;
    } 
    mp->items[index] = item;
    mp->count++;
}

// Search for a key in the map and return the value
char* map_search(map* mp, const char* key) {
    int index, i;
    map_item* item;

    index = map_get_hash(key, mp->size, 0);
    item = mp->items[index];
    i = 1;
    
    // calculate hash index until the key is found
    while (item != NULL) {
        if (item != &MAP_DELETED_ITEM) { 
            if (strcmp(item->key, key) == 0) {
                return item->value;
            }
        }
        index = map_get_hash(key, mp->size, i);
        item = mp->items[index];
        i++;
    } 
    return NULL;
}

// Delete a key-value pair from the map
// using MAP_DELETED_ITEM as separate chaining may be used to maintain linked list.
void map_delete(map* mp, const char* key) {
    int index, i;
    map_item* item;

    index = map_get_hash(key, mp->size, 0);
    item = mp->items[index];
    i = 1;
    
    // calculate hash index until the key is found
    while (item != NULL) {
        if (item != &MAP_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) {
                map_del_item(item);
                mp->items[index] = &MAP_DELETED_ITEM;
            }
        }
        index = map_get_hash(key, mp->size, i);
        item = mp->items[index];
        i++;
    } 
    mp->count--;
}
