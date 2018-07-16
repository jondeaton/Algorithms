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
  void *entries;            // Pointer to key-value pair array
  void *end;                // End of buckets array
  int capacity;             // maximum number of values that can be stored
  int size;                 // The number of elements stored in the hash table

  size_t key_size;          // The size of each key
  size_t value_size;        // The size of each value

  CleanupValueFn cleanup;   // A callback function for cleaning up a value in the map.
  CMapHashFn hash;        // hash function callback
  CMapCmpFn cmp;            // key comparison funciton
};

/**
 * @struct entry
 * Stores metadata about a single key-value pair
 */
struct entry {
  int origin;               // The origin
  int hash;                 // The hash of the key
  uint8_t status;             //
  char kv[];                // Key/Value pair
};

#define FREE_MASK ((uint8_t) 1)

static inline bool is_free(const struct entry* e) {
  return (bool) (e->status & FREE_MASK);
}

static inline void set_free(struct entry *e, bool free) {
  if (free) e->status |= FREE_MASK;
  else e->status &= ~FREE_MASK;
}

// static function declarations
static inline size_t entry_size(const CMap *cm);
static inline struct entry *get_entry(const CMap *cm, int index);

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
  for (int i = 0; i < (int) keysize; i++)
    hashcode = hashcode * MULTIPLIER + ((const char*) key)[i];
  return (int) hashcode;
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
  map->entries = malloc(map->capacity * entry_size);
  if (map->entries == NULL) return NULL;

  map->size = 0;

  for (int i = 0; i < map->capacity; ++i) {
    struct entry *e = get_entry(map, i);
    set_free(e, true);
  }

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
 * @breif Gets the size of each entry in the Hash Table
 * @param cm
 * @return
 */
static inline size_t entry_size(const CMap *cm) {
  return sizeof(struct entry) + cm->key_size + cm->value_size;
}

static inline struct entry *get_entry(const CMap *cm, int index) {
  if (cm == NULL || index < 0 || index >= cm->capacity) return NULL;
  void *entry = (char *) cm->entries + index * entry_size(cm);
  return (struct entry *) entry;
}

/**
 * @breif Finds the entry for this key
 * @param cm The CMap to lookup the key in
 * @param key the key to lookup in the CMap
 * @return Pointer
 */
static struct entry *lookup_key(const CMap *cm, const void *key) {
  int hash = cm->hash(key, cm->key_size);
  int start = hash % cm->capacity;

  for (int i = 0; i < cm->capacity; ++i) {
    struct entry *e = get_entry(cm, (start + i) % cm->capacity);
    if (e == NULL || is_free(e)) return NULL;

    // Use cached hash value to do an easy/cache-friendly comparison
    if (e->hash != hash) continue;

    // Only dereference to compare full keys if you have to
    if (cm->cmp(&e->kv, key, cm->key_size) == 0)
      return e;
  }
  return NULL; // Went all the way around
}

static struct entry *find_free(const CMap *cm, const void *key) {
  if (cm == NULL || key == NULL) return NULL;

  int hash = cm->hash(key, cm->key_size);
  int start = hash % cm->capacity;

  // There is no vacancy
  if (cm->size == cm->capacity)
    return NULL;

  for (int i = 0; i < cm->capacity; ++i) {
    struct entry *e = get_entry(cm, (start + i) % cm->capacity);
    if (e == NULL) return NULL;
    if (is_free(e)) return e;
  }
  return NULL; // Went all the way around (should never happen)
}

static inline void *value_of(const CMap *cm, const struct entry *entry) {
  return (char *) &entry->kv + cm->key_size;
}

static inline void *key_of(const struct entry *entry) {
  return (void *) (&entry->kv);
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
void *cmap_insert(CMap *cm, const void *key, const void *value) {

  if (cm == NULL || key == NULL || value == NULL) return NULL;

  struct entry *entry = find_free(cm, key);
  if (entry == NULL) return NULL;

  memcpy(&entry->kv, key, cm->key_size);
  memcpy(value_of(cm, entry), value, cm->value_size);

  cm->size++;
  return entry;
}

/**
 * @breif looks up a key-value pair in in the hash table
 * @param cm The hash map to lookup the value in
 * @param key The key to lookup
 * @return Pointer to the value stored in the hash table. If there
 * is no such key in the hash table then NULL.
 */
void *cmap_lookup(const CMap *cm, const void *key) {
  if (cm == NULL || key == NULL) return NULL;
  struct entry *entry = lookup_key(cm, key);
  if (entry == NULL) return NULL;
  return value_of(cm, entry);
}

static inline void move(CMap *cm, struct entry *entry1, struct entry *entry2) {
  memcpy(entry1, entry2, entry_size(cm));
}

static void delete(CMap *cm, int start, int stop) {

  // The entry to delete
  struct entry *entry = get_entry(cm, start);

  int j = start;
  for (int i = 0; i < cm->capacity; ++i) {
    j = (j + 1) % cm->capacity;
    if (j == stop) return;

    struct entry *next = get_entry(cm, j);
    if (is_free(next)) return; // reached the end

    // Found one that can replace
    if (next->origin >= start) {
      move(cm, entry, next);
      set_free(next, true);
      break;
    }
  }
  delete(cm, j, stop); // Tail recursion
}

static int lookup_index(const CMap *cm, const void *key) {
  int hash = cm->hash(key, cm->key_size);
  int start = hash % cm->capacity;

  for (int i = 0; i < cm->capacity; ++i) {
    struct entry *e = get_entry(cm, (start + i) % cm->capacity);
    if (e == NULL || is_free(e)) return -1;

    // Use cached hash value to do an easy/cache-friendly comparison
    if (e->hash != hash) continue;

    // Only dereference to compare full keys if you have to
    if (cm->cmp(&e->kv, key, cm->key_size) == 0)
      return (start + i) % cm->capacity;
  }
  return -1;
}

/**
 * @breif Removes a key-value pair from the hash table
 * @param cm Hash table to remove the key value pair from
 * @param key The key to remove
 */
void cmap_remove(CMap *cm, const void *key) {
  if (cm == NULL || key == NULL) return;

  int start = lookup_index(cm, key);
  struct entry *e = get_entry(cm, start);
  delete(cm, start, e->origin);
}

void cmap_dispose(CMap* cm) {
  cmap_clear(cm);
  free(cm->entries);
  free(cm);
}

/**
 * @breif Removes all of the elements from the hash tabls
 * @param cm The CMap to remove all the elements from
 */
void cmap_clear(CMap *cm) {
  if (cm == NULL) return;

  int num_cleared = 0;
  for (int i = 0; i < cm->capacity; ++i) {
    struct entry *e = get_entry(cm, i);
    if (is_free(e)) continue;

    cm->cleanup(value_of(cm, e));
    set_free(e, true);
    num_cleared++;

    // If we've deleted them all, stop and save a bit of searching
    if (num_cleared == cm->size) break;
  }
  cm->size = 0;
}


const void *cmap_first(const CMap *cm) {
  if (cm == NULL) return NULL;
  if (cm->size == 0) return NULL;

  for (int i = 0; i < cm->capacity; ++i) {
    struct entry *e = get_entry(cm, i);
    if (!is_free(e)) return key_of(e);
  }
  return NULL;
}

/**
 * @breif Gets a pointer to the next key
 * @param cm The hash table
 * @param prevkey The previous key
 * @return pointer to the next key, if there is one.
 */
const void *cmap_next(const CMap *cm, const void *prevkey) {
  if (cm == NULL || prevkey == NULL) return NULL;

  const struct entry *e = (struct entry *) ((char *) prevkey - offsetof(struct entry, kv));
  while (e != cm->end) {
    e = (struct entry *) ((char *) e + entry_size(cm));
    if (!is_free(e)) return key_of(e);
  }
  return NULL;
}
