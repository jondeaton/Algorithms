
#include "CPriorityQueue.h"
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

#define DEFAULT_CAPACITY 16

static inline void* pqueue_element(const CPQueue *pq, unsigned int i);
static void pqueue_clear(CPQueue* pq);
static inline void* pqueue_last(const CPQueue* pq);

  struct CPriorityQueueImplementation {
  void* elements;
  unsigned int nelems;
  unsigned int capacity;
  size_t elemsz;
  CleanupElemFn cleanup;
  Cmp cmp;
};

CPQueue* pqueue_create(size_t elemsz, unsigned int capacity_hint, CleanupElemFn fn, Cmp cmp) {
  CPQueue* pq = malloc(sizeof(struct CPriorityQueue));
  pq->elemsz = elemsz;
  pq->cleanup = fn;
  pq->cmp = cmp;

  pq->capacity = capacity_hint ? capacity_hint : DEFAULT_CAPACITY;
  pq->elements = malloc(elemsz * pq->capacity);

  return pq;
}

void pqueue_destroy(CPQueue* pq) {
  pqueue_clear(pq);
  free(pq->elements);
  free(pq);
}

void* pqueue_top(CPQueue* pq) {
  if (pq->nelems) return pq->elements;
  else return NULL;
}

void pqueue_pop(CPQueue* pq) {
  assert(pq->nelems);
  memcpy(pq->elements, pqueue_last(pq), pq->elemsz);
  pq->nelems--;
  push_down(pq->elements);
}


static inline void* pqueue_last(const CPQueue* pq) {
  return pqueue_element(pq, pq->nelems - 1);
}

static void pqueue_clear(CPQueue* pq) {
  if (pq->cleanup){

    for (unsigned int i = 0; i < pq->nelems; ++i) {
      void* el = pqueue_element(pq, i);
      pq->cleanup(el);
    }
  }
  pq->nelems = 0;
}

static inline void* pqueue_element(const CPQueue *pq, unsigned int i) {
  return (char*) pq->elements + i;
}

