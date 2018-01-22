
#include "CPriorityQueue.h"
#include <stdlib.h>

struct CPriorityQueueImplementation {
  int nelems;
  int capacity;
  size_t elemsz;
  CleanupElemFn cleanup;
  Cmp cmp;
};

CPriorityQueue* pqueue_create(size_t elemsz, size_t capacity_hint, CleanupElemFn fn) {
  CPriorityQueue* pq = malloc(sizeof(struct CPriorityQueue));

  return pq;
}

void pqueue_destroy(CPriorityQueue*) {

}

