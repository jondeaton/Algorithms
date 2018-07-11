/**
 * @file priority_queue.c
 * @brief Implementation of priority queue
 */

#include "priority_queue.h"
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include <stdio.h>

#define DEFAULT_CAPACITY 16

static inline void* el_at(const PriorityQueue *pq, int i);
static inline void* last_element(const PriorityQueue *pq);
static inline void* heap_end(const PriorityQueue* pq);
static inline void swap(PriorityQueue *pq, int i, int j);
static inline int parent_of(int index);
static inline int left_of(int index);
static inline int right_of(int index);
static void swap_down(PriorityQueue *pq, int index);
static void swap_up(PriorityQueue *pq, int index);
static void double_size(PriorityQueue *pq);
static inline bool cmp(const PriorityQueue* pq, int i, int j);

struct PriorityQueueImplementation {
  void* heap;
  unsigned int nelems;
  unsigned int capacity;
  size_t elemsz;
  CleanupElemFn cleanup;
  Cmp cmp;
};

PriorityQueue *pqueue_create(size_t elemsz, unsigned int capacity_hint, Cmp cmp, CleanupElemFn cleanup) {
  PriorityQueue* pq = malloc(sizeof(struct PriorityQueueImplementation));
  if (!pq) {
    perror(__func__);
    exit(EXIT_FAILURE);
  }

  pq->elemsz = elemsz;
  pq->cleanup = cleanup;
  pq->cmp = cmp;

  pq->capacity = capacity_hint ? capacity_hint : DEFAULT_CAPACITY;
  pq->heap = malloc(elemsz * pq->capacity);
  if (!pq->heap) {
    perror(__func__);
    exit(EXIT_FAILURE);
  }

  return pq;
}

void pqueue_dispose(PriorityQueue *pq) {
  pqueue_clear(pq);
  free(pq->heap);
  free(pq);
}

void* pqueue_top(const PriorityQueue *pq) {
  if (pq->nelems) return pq->heap;
  else return NULL;
}

void pqueue_pop(PriorityQueue* pq) {
  assert(pq->nelems);
  if (pq->cleanup) pq->cleanup(pq->heap);
  memcpy(pq->heap, last_element(pq), pq->elemsz);
  pq->nelems--;
  swap_down(pq, 0);
}

void pqueue_push(PriorityQueue *pq, const void *source) {
  if (pq->nelems == pq->capacity) double_size(pq);
  memcpy(heap_end(pq), source, pq->elemsz);
  pq->nelems++;
  swap_up(pq, pq->nelems - 1);
}

bool pqueue_empty(const PriorityQueue *pq) {
  return pq->nelems == 0;
}

unsigned int pqueue_size(const PriorityQueue* pq) {
  return pq->nelems;
}

static void delete_element(PriorityQueue *pq, int index) {
  if (index == pq->nelems - 1) {
    pq->nelems--;
    return;
  }
  int left = left_of(index);
  int right = right_of(index);

  int swap_index;
  if (right >= pq->nelems)
    swap_index = pq->nelems - 1;
  else if (cmp(pq, left, right))
    swap_index = left;
  else
    swap_index = right;

  swap(pq, index, swap_index);
  delete_element(pq, swap_index);
}

static void swap_down(PriorityQueue *pq, int index) {
  int left = left_of(index);
  int right = right_of(index);

  if (left >= pq->nelems) return; // has no children
  bool has_right = right < pq->nelems;

  if (cmp(pq, left, index) && has_right && cmp(pq, left, right)) {
    swap(pq, left, index);
    swap_down(pq, left);
  } else if (has_right && cmp(pq, right, index) && cmp(pq, right, left)) {
    swap(pq, right, index);
    swap_down(pq, right);
  }
}

static void swap_up(PriorityQueue *pq, int index) {
  if (index == 0) return;
  int parent = parent_of(index);
  if (cmp(pq, index, parent)) {
    swap(pq, parent, index);
    swap_up(pq, parent);
  }
}

static inline void swap(PriorityQueue *pq, int i, int j) {
  char tmp[pq->elemsz];
  memcpy(tmp, el_at(pq, i), pq->elemsz);
  memcpy(el_at(pq, i), el_at(pq, j), pq->elemsz);
  memcpy(el_at(pq, j), tmp, pq->elemsz);
}

static void double_size(PriorityQueue *pq) {
  pq->capacity *= 2;
  pq->heap = realloc(pq->heap, pq->capacity * pq->elemsz);
  if (!pq->heap) {
    perror(__func__);
    exit(EXIT_FAILURE);
  }
}

static inline void* last_element(const PriorityQueue *pq) {
  return el_at(pq, pq->nelems - 1);
}

static inline void* heap_end(const PriorityQueue* pq) {
  return el_at(pq, pq->nelems);
}

static inline bool cmp(const PriorityQueue* pq, int i, int j) {
  return pq->cmp(el_at(pq, i), el_at(pq, j));
}

void pqueue_clear(PriorityQueue* pq) {
  if (pq->cleanup) {
    for (int i = 0; i < pq->nelems; ++i) {
      void* el = el_at(pq, i);
      pq->cleanup(el);
    }
  }
  pq->nelems = 0;
}

static inline void* el_at(const PriorityQueue *pq, int i) {
  return (char*) pq->heap + i * pq->elemsz;
}

static inline int parent_of(int index) {
  return (index + 1) / 2 - 1;
}
static inline int left_of(int index) {
  return 2 * (index + 1) - 1;
}
static inline int right_of(int index) {
  return 1 + left_of(index);
}
