#ifndef PRIORITYQUEUE_LIBRARY_H
#define PRIORITYQUEUE_LIBRARY_H

#include <stdbool.h>

typedef void (*CleanupElemFn)(void *addr);
typedef bool (*Cmp)(void* a, void* b);

typedef struct CPriorityQueueImplementation CPQueue;

#endif // PRIORITYQUEUE_LIBRARY_H
