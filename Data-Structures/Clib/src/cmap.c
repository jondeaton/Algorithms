/**
 * @file cmap.c
 * @brief Defines the implementation of a HashMap in C
 */

#include "cmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// a suggested value to use when given capacity_hint is 0
#define DEFAULT_CAPACITY 1023

/**
 * @struct CMapImplementation
 * @brief Definition of HashTable implementation
 */
struct CMapImplementation {
  void *buckets;            // Pointer to key-value pair array
  int capacity;             // maximum number of values that can be stored
  int size;                 // The number of elements stored in the hash table

  size_t value_size;        // The size of the value
  size_t key_size;

  CleanupValueFn cleanup;   // A callback function for cleaning up a value in the map.
  CMapHashFn hash;          // hash function callback
  CMapCmpFn cmp;            // key comparison funciton
};

/**
 * @struct entry
 * Stores metadata about a single key-value pair
 */
struct entry {
  int origin;               // The origin
  int hash;                 // The hash of the key
  uint8_t info;             //
  char kv[];                // Key/Value pair
};

bool is_free(const struct entry* e) {
    return (bool) (e->info & 1);
}

// Static function prototypes
static void* get_value_ptr(void* node, const char* key);
static bool is_node_of(const void* node, const void* key);
static void* get_bucket(const CMap* cm, const void* key);
static void* get_node(const CMap* cm, const char* key);

/**
 * @breif Default hash function
 * @detail This function adapted from Eric Roberts' _The Art and Science of C_
 * The hash code is computed using a method called "linear congruence."
 * A similar function using this method is described on page 144 of Kernighan
 * and Ritchie. The choice of the value for the multiplier can have a significant
 * effort on the performance of the algorithm, but not on its correctness.
 * The computed hash value is stable, e.g. passing the same string and
 * nbuckets to function again will always return the same code.
 */
static int default_hash(const void *key, size_t keysize) {
    const unsigned long MULTIPLIER = 2630849305L; // magic number
    unsigned long hashcode = 0;
    for (int i = 0; i < keysize; i++)
        hashcode = hashcode * MULTIPLIER + ((const char*) key)[i];
    return (int) hashcode;
}

static int string_hash(const void *key, size_t keysize) {
    size_t keylen = strlen((const char*) key);
    return default_hash(key, keylen);
}

/**
 * @breif Instantiate a CMap struct in a dynamically allocated region of memory.
 * This function will also fill in the relevant elements of the CMap
 * @param value_size
 * @param capacity
 * @param fn
 * @return
 */
CMap *cmap_create(size_t key_size, size_t value_size,
                  CMapHashFn hash, CMapCmpFn cmp, CleanupValueFn fn, int capacity) {
    if (key_size <= 0 || value_size <= 0) return NULL;

    CMap* map = malloc(sizeof(CMap));
    if (map == NULL) return NULL;

    size_t entry_size = sizeof(struct entry) + value_size;
    map->capacity = capacity > 0 ? capacity : DEFAULT_CAPACITY;
    map->buckets = malloc(map->capacity * entry_size);
    if (map->buckets == NULL) return NULL;

    map->size = 0;

    map->cleanup = fn;
    map->hash = hash == NULL ? default_hash : hash;
    map->cmp = cmp == NULL ? memcmp : cmp;

    return map;
}

/**
 * @brief Returns the number of key value pairs currently
 * stored in the table
 */
int cmap_count(const CMap* cm) {
    return cm->size;
}

/**
 * @breif Returns the maximum capacity of the hash table
 */
int cmap_capacity(const CMap* cm) {
    return cm->capacity;
}

/**
 * @breif Finds the entry for this key
 * @param cm The CMap to lookup the key in
 * @param key the key to lookup in the CMap
 * @return
 */
struct entry *lookup_key(const CMap *cm, const void *key) {
    int hash = cm->hash(key, cm->key_size);
    struct entry *e;
    int offset = 0;
    for () {
        if (is_free(e)) return NULL;
        
    }
}

/**
 * @breif Inserts a key-value pair into the hash table
 * @param cm The CMap to insert a value into
 * @param key The key to insert
 * @param keysize The size of the key to insert
 * @param value The value to insert
 * @param valuesize The size of the value to insert
 * @return Pointer to the inserted key, if successfully inserted, othersie NULL.
 */
void * cmap_insert(CMap *cm, const void *key, size_t keysize, const void *value,
                   size_t valuesize) {

    if (cm == NULL || key == NULL || value == NULL) return NULL;
    if (keysize == 0 || valuesize == 0) return NULL;

    struct entry *entry =

    void* bucket = get_bucket(cm, key);


    // Loop through linked list of nodes to see if the key
    // already exists in the map and replace if present.
    void* next_node = bucket;
    while (*(void**) next_node != NULL)
    {
        next_node = *(void**) next_node;

        // Check to see if this next node actually contains the key already
        if (is_node_of(next_node, key))
        {
            // If this key is already in the map, then cleanup
            // the old value and replace it with the new one
            void* value_loc = get_value_ptr(next_node, key);
            if (cm->cleanup != NULL)
                (*cm).cleanup(value_loc);
            memcpy(value_loc, value, cm->valsz);
            return;
        }
    }

    // Key wasn't already present so allocate space for a new node and put
    // it at the end of the linked list.
    size_t node_size = sizeof(void*) + strlen(key) + 1 + cm->valsz;
    void* new_node = malloc(node_size);

    // Assert node allocation success
    assert(new_node != NULL);

    // Set the beginning of the node to not point to any next node
    *(void**) new_node = NULL;

    // Set the last node (or bucket) to point to the beginning of this new node
    *(void**) next_node = new_node;

    // Copy the key into the node
    strcpy((char*) new_node + sizeof(void*), key);

    // Copy the element into the node
    void* value_dest = get_value_ptr(new_node, key);
    memcpy(value_dest, value,  cm->valsz);

    cm->numvals++;
}

/* Function: cmap_get
 * ------------------
 *  This function gets the a pointer to the value that is associated with 
 *  the key. It does do by hashing the key and then looping through the linked
 *  list of nodes using strcmp to confirm that a given node contains the key.
 */
void* cmap_get(const CMap* cm, const char* key)
{
    void* node = get_node(cm, key);
    return node == NULL ? NULL : get_value_ptr(node, key);
}

/* Function: cmap_remove
 * ---------------------
 * This function removes a key value pair from the map. Thsi function
 * will do nothing if a key is provided that is not in the map. This function
 * hashes the key to get the bucket for the key, and then follows the linked list
 * of nodes. When the key is located (using strcmp) then the node is free'd and the 
 * value is cleaned up is necessary. The previosu node (or bucket) is then set to point 
 * to the next node (or null if no next node is present).
 */
void cmap_remove(CMap* cm, const char* key)
{
    // Get the bucket corresponding to this key
    void* bucket = get_bucket(cm, key);
    // If the bucket is empty, then the key isn't in the map
    if (*(void**) bucket == NULL) return;

    // Iterate through the linked list of nodes pointed to by the
    // bucket, keeping track of the last node visited
    void* previous_node = bucket;
    void* next_node = *(void**) bucket;
    while (true)
    {
        // If this node is the one that contains the key
        if (is_node_of(next_node, key))
        {
            // Make the previous node point to the next node
            *(void**) previous_node = *(void**) next_node;
            // Cleanup the value stored at this node (if needed)
            if(cm->cleanup != NULL)
                (*cm).cleanup(get_value_ptr(next_node, key));
            // Free the space used for the node
            free(next_node);
            // Decrement number of key-value pairs
            cm->numvals--;
            return;
        }
        else
        {
            // This node didn't contain the key we were searching for
            // so move onto the next node.
            previous_node = next_node;
            next_node = *(void**) next_node;
            // If we've hit the last node in the linked
            // list, then this key isn't in the map, so return
            if (next_node == NULL) return;
        }
    }
}


/* Function: cmap_dispose
 * ----------------------
 * This function disposes of a CMap and all it's contents. This
 * function gathers a list of keys through the use of cvec_first/cvec_next and stores
 * them in an array on the stack, then loops through the key array freeing and cleaning up
 * the nodes that each of the keys point to. If there is a provided callback function
 * for cleaning up elements, then this function will call that function on
 * the value memory address stored in the node.
 */
void cmap_dispose(CMap* cm) {
    cmap_clear(cm);
    free(cm->buckets);
    free(cm);
}

void cmap_clear(CMap *cm) {
    // Loop through and store all keys on the stack.
    const void* keys[cm->numvals];


    int i = 0;
    for (const void* key = cmap_first(cm); key != NULL; key = cmap_next(cm, key)) {
        keys[i] = key;
        i++;
    }
    // Loop through keys freeing nodes and values
    void* node;
    for (i = 0; i < cm->numvals; i++) {
        node = (char*) keys[i] - sizeof(void*);
        if (cm->cleanup != NULL)
            cm->cleanup(get_value_ptr(node, keys[i]));
        free(node);
    }
}

/* Function: cmap_first
 * --------------------
 * This function gets the first element of the CMap by looping through 
 * the buckets and returning a pointer to the key contains in the 
 * node pointed to by the first bucket that does not contain NULL. If all 
 * buckets contain NULL then there are no key-value pairs in the map,
 * this function will return NULL. 
 */
const char* cmap_first(const CMap* cm)
{
    for (int i = 0; i < cm->nbuckets; i++)
    {
        void* bucket = (char*) cm->buckets + i * sizeof(void*);

        // If bucket contains NULL, skip it
        if (*(void**) bucket == NULL) continue;
        else
        {
            // Dereference to get to the node
            void* node = *(void**) bucket;
            // Jump to the start of the key
            return (char*) node + sizeof(void*);
        }
    }
    // All buckets were NULL
    return NULL;
}

/* Function: cmap_next
 * -------------------
 *  This function gets the next element after the first one. This function
 *  will first check to see if the pointer stored in 
 *
 */
const char* cmap_next(const CMap* cm, const char* prevkey)
{
    // Since we can expect the prevkey to have come from cmap_first
    // then we can assume that the prevkey points to a key that is actually
    // inside of a node, and therefore we can use pointer arithmetic
    // to get a pointer to beginnign of the node.
    void* node = (char*) prevkey - sizeof(void*);

    // If the key is not in the map, then return NULL
    if (node == NULL) return NULL;

    // If the next node is pointed to by the pointer
    // in the beginning of this node, then just return that pointer
    if (*(void**) node != NULL)
    {
        void* next_node = *(void**) node;
        return (char*) next_node + sizeof(void*);
    }

    // If this node was the last one in the linked list, then go back
    // and iterate through the buckets. 
    for (int i = hash(prevkey, cm->nbuckets) + 1; i < cm->nbuckets; i++)
    {
        // Get the next bucket
        void* bucket = (char*) cm->buckets + i * sizeof(void*);
        // If bucket contents are not NULL, return the key in the node
        if (*(void**) bucket != NULL)
        {
            void* next_node = *(void**) bucket;
            return (char*) next_node + sizeof(void*);
        }
    }
    // Prevkey was the last key
    return NULL;
}

/* Function: get_bucket
 * --------------------
 * This function is for getting a pointer to the bucket that the provided
 * key would be or is already stored in. This function works by hashing the key
 * to get the bucket index of the key, and then using pointer arithmetic to 
 * jump to the memory address of that bucket. This bucket may contain NULL
 * if the key is not already in the map and no other keys with the same hash 
 * are currently contained in the bucket.
 */
static void* get_bucket(const CMap* cm, const void* key)
{
    return (char*) cm->buckets + hash(key, cm->nbuckets) * sizeof(void*);
}

/* Function: get_value_ptr
 * -----------------------
 * This function is for getting a pointer to the part of the node
 * that contains the value. This function will use pointer arithmetic
 * to jump ahead in memory past the pointer and key contained in the node. Since
 * the key is simply used to get the length of bytes of the key, the pointer to key
 * need not be pointing to the key that is actually stored inside of the node, but
 * it does need to have the correct length so that the correct memory address is calculated.
 *
 * Assumes: The key value stored in the node is the same as that pointed to by key
 */
static void* get_value_ptr(void* node, const char* key)
{
    return (char*) node + sizeof(void*) + strlen(key) + 1;
}

/* Function: is_node_of
 * --------------------
 * This function returns a bool indicating that the node pointed to by the 
 * first argument contains the key pointed to by the second argument. This
 * is confirmed using strcmp to compare the two key strings. Since string
 * comparison is used, the key pointed to by the second argumet need not be actually
 * contained in the node pointed to the first argument. A true value returned means
 * that the node contains a string equal to that pointed to by key. 
 */
static bool is_node_of(const void* node, const void* key)
{
    char* string_start = (char*) node + sizeof(void*);
    return strcmp(string_start, key) == 0;
}

/* Function: get_node
 * ------------------
 * This function is for getting a pointer to the node that contains the key-value 
 * pair of the key pointed to by the second argument. This function will hash the key
 * and then follow the linked list pointed to by the key's bucket. Each node in the linked
 * list will be examined using is_node_of to see if it has the correct key. If a key match is 
 * found then a pointer to the beginning of the node will be returned. If no matching keys were found 
 * in the linked list of nodes, then NULL will be returned indicating that the key is not in the map.
 * Since this function uses strcmp to look for strings, the key pointed to by the second argument
 * need not be pointing to a key that is actually stored in the node, but only need to be equal 
 * by string comparison.
 */
static void* get_node(const CMap* cm, const char* key)
{
    // Hash key to get the bucket
    void* bucket = get_bucket(cm, key);

    // Bucket contains no nodes so no key found -> return null
    if (*(void**) bucket == NULL) return NULL;

    // Start at the first
    void* next_node = *(void**) bucket;
    while (true)
    {
        // If string matches return this node
        if (is_node_of(next_node, key)) return next_node;

            // keys didin't match, and this is the last node in the list. No key found.
        else if (*(void**) next_node == NULL) return NULL;

        // Jump to next node
        next_node = *(void**) next_node;
    }
}
