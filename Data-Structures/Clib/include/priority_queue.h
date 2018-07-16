/**
 * @file priority_queue.h
 * @brief A priority queue using a min heap
 */

#ifndef PRIORITYQUEUE_LIBRARY_H
#define PRIORITYQUEUE_LIBRARY_H

#include <stdlib.h>
#include <stdbool.h>

typedef void (*CleanupElemFn)(void *addr);
typedef bool (*Cmp)(const void* a, const void* b);

typedef struct PriorityQueueImplementation PriorityQueue;

/**
 * @fn pqueue_create
 * @brief Create a priority queue object
 * @param elemsz Size of the element stored in the priority queue
 * @param capacity_hint Hint for initial capacity of priority queue
 * @param cmp Function for comparing two elements (may not be NULL). Elements with the least value, using
 * this comparison function will be ranked first in the priority queue
 * @param cleanup Function for disposing of a single element (may be null)
 * @return A pointer to a newly allocated priority queue object
 */
PriorityQueue *pqueue_create(size_t elemsz, unsigned int capacity_hint, Cmp cmp, CleanupElemFn cleanup);

/**
 * @fn pqueue_dispose
 * @param pq: Pointer ot a priority queue to dispose of
 */
void pqueue_dispose(PriorityQueue *pq);

/**
 * @fn pqueue_top
 * @param pq Pointer to a priority queue
 * @return The element on the top of the priority queue
 */
void* pqueue_top(const PriorityQueue *pq);

/**
 * @fn pqueue_pop
 * @brief Pops the top element off the priority queue
 * @param pq Pointer to a priority queue
 */
void pqueue_pop(PriorityQueue* pq);

/**
 * @fn pqueue_push
 * @param pq Pointer to a priority queue
 * @param source Pointer to an element to copy into the queue
 */
void pqueue_push(PriorityQueue *pq, const void *source);

/**
 * @fn pqueue_clear
 * @brief Clear all elements from the priority queue
 * @param pq A pointer to a priority queue
 */
void pqueue_clear(PriorityQueue* pq);

/**
 * @fn pqueue_empty
 * @param pq A pointer to a priority queue
 * @return True if the queue is empty, false otherwise
 */
bool pqueue_empty(const PriorityQueue *pq);

/**
 * @fn pqueue_size
 * @param pq A pointer to a priority queue
 * @return The number of elements in the queue
 */
int pqueue_size(const PriorityQueue *pq);

#endif // PRIORITYQUEUE_LIBRARY_H
