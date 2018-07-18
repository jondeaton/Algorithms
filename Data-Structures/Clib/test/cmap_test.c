
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include "assert.h"

#include "cmap.h"

static int default_hash(const void *key, size_t keysize) {
  const unsigned long MULTIPLIER = 2630849305L; // magic number
  unsigned long hashcode = 0;
  for (int i = 0; i < (int) keysize; i++)
    hashcode = hashcode * MULTIPLIER + ((const char*) key)[i];
  return (int) hashcode;
}

// example of a string hash function that could be used for strings
static unsigned int string_hash(const void *key, size_t keysize) {
  (void) keysize;
  size_t keylen = strlen((const char*) key);
  return default_hash(key, keylen);
}

static int string_cmp(const void *a, const void *b, size_t keysize) {
  (void) keysize;
  return strcmp(*(const char **) a, *(const char **) b);
}

int main (int argc, char* argv[]) {
  (void) argc;
  (void) argv;
  
  CMap *map = cmap_create(sizeof(char *), sizeof(int),
                          string_hash, string_cmp, 
                          NULL, NULL, 0);

  assert(map != NULL);
  assert(cmap_count(map) == 0);

  const char *a = "a";
  const char *b = "b";

  cmap_insert(map, &a, &(int){1});
  cmap_insert(map, &b, &(int){2});

  assert(cmap_count(map) == 2);

  // Check to make sure we can get values
  const int *value = cmap_lookup(map, &a);
  assert(*value == 1);

  cmap_remove(map, &b);
  assert(cmap_count(map) == 1);

  value = cmap_lookup(map, &a);
  assert(*value == 1);

  value = cmap_lookup(map, &b);
  assert(value == NULL);

  cmap_clear(map);
  assert(cmap_count(map) == 0);

  assert(cmap_lookup(map, &a) == NULL);
  cmap_dispose(map);

  return 0;
}
