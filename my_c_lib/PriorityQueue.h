
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Queue.h"

typedef Queue PriorityQueue;

typedef struct PQCell {
	int priority;
	void *value;
} PQCell;

PQCell *newPQCell(const void *e, size_t size, int priority);

PriorityQueue *newPriorityQueue(size_t sizeofEach);

void freePriorityQueue(PriorityQueue *pq, void (*freeValue)(void *value));

void addToPriorityQueue(PriorityQueue *pq, const void *e, int priority);

void *shiftFromPriorityQueue(PriorityQueue *pq);

#endif
