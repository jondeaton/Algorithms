#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include "assert.h"

#include "cmap.h"
#include "hash.h"

#define unused __attribute__ ((unused))

void functionality_test() {
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

}

int main (int argc unused, char* argv[] unused) {
  functionality_test();
  return 0;
}
