
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Queue.h"

typedef Queue PriorityQueue;

PriorityQueue *newPriorityQueue(size_t sizeofEach);

void freePriorityQueue(PriorityQueue *pq, void (*freeValue)(void *value));

void addToPriorityQueue(PriorityQueue *pq, void *e, int priority);

#endif
