
#include "priority_queue.h"
#include <stdio.h>
#include <assert.h>

#define SMALL 20
#define BIG 10000

#define FOR(N) for (int i = 0; i < N; ++i)

static bool cmp_int(const void *a, const void *b) {
  return *(int*)a < *(int*)b;
}

static bool leq(const void* a, const void* b) {
  return *(int*)a <= *(int*)b;
}

static void assert_ordering(PriorityQueue* pq) {
  int* last = pqueue_top(pq);
  while (!pqueue_empty(pq)){
    assert(leq(last, pqueue_top(pq)));
    last = pqueue_top(pq);
    pqueue_pop(pq);
  }
}

static void assert_size(const PriorityQueue* pq, int expected) {
  assert(pqueue_size(pq) == expected);
}

static void print_heap(PriorityQueue* pq) {
  printf("heap: ");
  while (!pqueue_empty(pq)) {
    int el = *(int*) pqueue_top(pq);
    printf("%d, ", el);
    pqueue_pop(pq);
  }
  printf("\n");
}

int main() {
  PriorityQueue* pq = pqueue_create(sizeof(int), 0, cmp_int, NULL);

  FOR(SMALL) pqueue_push(pq, &i);

  assert_size(pq, SMALL);
  print_heap(pq);

  pqueue_clear(pq);
  assert_size(pq, 0);
  FOR(BIG) {
    int x = rand();
    pqueue_push(pq, &x);

    x = rand();
    pqueue_push(pq, &x);

    pqueue_pop(pq);
  }
  assert_size(pq, BIG);
  assert_ordering(pq);

  pqueue_clear(pq);
  assert_size(pq, 0);
  FOR(BIG) pqueue_push(pq, &i);
  assert_size(pq, BIG);
  assert_ordering(pq);

  pqueue_dispose(pq);
  return 0;
}