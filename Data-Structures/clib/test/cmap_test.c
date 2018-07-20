#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include "assert.h"

#include "cmap.h"
#include "hash.h"

#define unused __attribute__ ((unused))

#define NUM_LETTERS 26
const char *const alphabet[] = { "a", "b", "c", "d", "e", "f", "g",
                                 "h", "i", "j", "k", "l", "m", "n",
                                 "o", "p", "q", "r", "s", "t", "u",
                                 "v", "w", "x", "y", "z"};

// Testing to make sure that you can use all kinds
// of key and value sizes
static bool test_creation() {
  for (size_t keysize = 1; keysize <= 32; keysize++) {
    for (size_t valuesize = 1; valuesize <= 32; valuesize++) {

      CMap *map = cmap_create(keysize, valuesize,
                              NULL, NULL, NULL, NULL, (unsigned int) (keysize * valuesize));

      if (map == NULL) return false;
      if (cmap_count(map) != 0) return false;

      cmap_dispose(map);
    }
  }
 return true;
}

static bool test_insertion(unsigned int capacity) {
  CMap *map = cmap_create(sizeof(char *), sizeof(int),
                          string_hash, string_cmp,
                          NULL, NULL, capacity);

  if (map == NULL)
    return false;

  if (cmap_count(map) != 0)
    return false;

  for (int i = 0; i < NUM_LETTERS; ++i) {
    const char *const letter = alphabet[i];
    cmap_insert(map, &letter, &i);
  }

  if (cmap_count(map) != NUM_LETTERS)
    return false;

  // Make sure they're all in there
  for (int i = 0; i < NUM_LETTERS; ++i) {
    const char *const letter = alphabet[i];
    const void *l = cmap_lookup(map, &letter);

    if (l == NULL)
      return false;

    if (*(int*) l != i)
      return false;
  }

  return true;
}

static bool test_deletion(unsigned int capacity) {
  CMap *map = cmap_create(sizeof(char *), sizeof(int),
                          string_hash, string_cmp,
                          NULL, NULL, capacity);

  if (map == NULL)
    return false;
  if (cmap_count(map) != 0)
    return false;

  for (int i = 0; i < NUM_LETTERS; ++i) {
    const char *const letter = alphabet[i];
    cmap_insert(map, &letter, &i);
  }

  if (cmap_count(map) != NUM_LETTERS) return false;

  // Make sure they're all in there
  for (int i = 0; i < NUM_LETTERS; ++i) {
    const char * letter = alphabet[i];
    const void *l = cmap_lookup(map, &letter);
    if (l == NULL)
      return false;
    if (*(int*) l != i)
      return false;
  }

  // Make sure that you can remove things, and that they go away
  for (int i = 0; i < NUM_LETTERS; ++i) {
    const char * letter = alphabet[i];
    cmap_remove(map, &letter);

    // Make sure it's gone
    const void *value = cmap_lookup(map, &letter);
    if (value != NULL)
      return false;

    // Make sure count reflects deletion
    if (cmap_count(map) != (unsigned int) (NUM_LETTERS - (i + 1)))
      return false;

    // Make sure all the *others* are still in there
    for (int j = i + 1; i < NUM_LETTERS; ++i) {
      letter = alphabet[j];
      value = cmap_lookup(map, &letter);
      if (value == NULL)
        return false;
      if (*(int*) value != j)
        return false;
    }
  }

  cmap_dispose(map);
  return true;
}

int main (int argc unused, char* argv[] unused) {

  printf("Testing creation of Hash Table... ");
  bool success = test_creation();
  printf("%s\n", success ? "success" : "failure");

  printf("Testing insertion into Hash Table... ");
  for (unsigned int capacity = 30; capacity < 200; capacity += 10) {
    success = test_insertion(capacity);
    if (!success) break;
  }
  printf("%s\n", success ? "success" : "failure");

  printf("Testing deletion from Hash Table... ");
  for (unsigned int capacity = 30; capacity < 200; capacity += 10) {
    success = test_deletion(capacity);
    if (!success) break;
  }
  printf("%s\n", success ? "success" : "failure");

  return 0;
}
