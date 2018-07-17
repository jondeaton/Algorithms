/**
 * @file cmap.h
 * @breif Defines the interface for the CMap type.
 */

#ifndef _cmap_h
#define _cmap_h

#include <stddef.h>
#include <stdbool.h>

typedef void (*CleanupValueFn)(void *addr);
typedef unsigned int (*CMapHashFn)(const void *key, size_t keysize);
typedef int (*CMapCmpFn)(const void *keyA, const void *keyB, size_t keysize);
typedef struct CMapImplementation CMap;


CMap *cmap_create(size_t key_size, size_t value_size,
                  CMapHashFn hash, CMapCmpFn cmp,
                  CleanupValueFn fn,
                  unsigned int capacity_hint);

void cmap_dispose(CMap *cm);
unsigned int cmap_count(const CMap *cm);
void *cmap_insert(CMap *cm, const void *key, const void *value);
void *cmap_lookup(const CMap *cm, const void *key);
void cmap_remove(CMap *cm, const void *key);
void cmap_clear(CMap *cm);
const void * cmap_first(const CMap *cm);
const void * cmap_next(const CMap *cm, const void *prevkey);

#endif
