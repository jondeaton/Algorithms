
#include "CPriorityQueue.h"

bool cmp(const int a, const int b) {
  return a < b;
}

int main() {
  CPQueue* pq = pqueue_create(sizeof(int), 0, NULL, &cmp);

  for (int i = 0; i < 100; i++)
    pqueue_push(&i);

  pqueue_dispose(pq);
  return 0;
}