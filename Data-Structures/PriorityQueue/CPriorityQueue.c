
#include "CPriorityQueue.h"
#include <stdlib.h>
#include <assert.h>
#include <memory.h>

#define DEFAULT_CAPACITY 16

static inline void* pqueue_element(const CPQueue *pq, unsigned int i);
static void pqueue_clear(CPQueue* pq);
static inline void* pqueue_last(const CPQueue* pq);
static inline void swap(CPQueue* pq, unsigned int i, unsigned int j);

static inline int parent(int i) {
  if (i == 0) return -1;
  return i / 2;
}
static inline int left_of(int i) {
  return 2 * (i + 1) - 1;
}

static inline int right_of(int i) {
  return left_of(i + 1);
}

struct CPriorityQueueImplementation {
  void* heap;
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
  pq->heap = malloc(elemsz * pq->capacity);

  return pq;
}

void pqueue_destroy(CPQueue* pq) {
  pqueue_clear(pq);
  free(pq->heap);
  free(pq);
}

void* pqueue_top(CPQueue* pq) {
  if (pq->nelems) return pq->heap;
  else return NULL;
}

void pqueue_pop(CPQueue* pq) {
  assert(pq->nelems);
  memcpy(pq->heap, pqueue_last(pq), pq->elemsz);
  pq->nelems--;
  if (pq->nelems) push_down(pq->heap, 0);
}

void pqueue_push(CPQueue* pq) {



  pq->nelems++;
  bubble_up(pq->heap, pq->nelems - 1);
}

static void push_down(CPQueue* pq, unsigned int i) {
  unsigned int left = left_of(i);
  unsigned int right = right_of(i);

  if (pq->cmp(pqueue_element(pq, left), pqueue_element(pq, i))) {
    swap(pq, i, left);
    push_down(pq, left);
  } else if (pq->cmp(pqueue_element(pq, right), pqueue_element(pq, i))) {
    swap(pq, i, right);
    push_down(pq, right);
  }
}

static void bubble_up(CPQueue* pq, unsigned int i) {
  if (i == 0) return;
  unsigned int left = left_of(i);
  unsigned int right = right_of(i);


}

static inline void swap(CPQueue* pq, unsigned int i, unsigned int j) {
  char tmp[pq->elemsz];
  memcpy(tmp, pqueue_element(pq, i));
  memcpy(pqueue_element(pq, j), pqueue_element(pq, i));
  memcpy(pqueue_element(pq, i), tmp);
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
  return (char*) pq->heap + i;
}

