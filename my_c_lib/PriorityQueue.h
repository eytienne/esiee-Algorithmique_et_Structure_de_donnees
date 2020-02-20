
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Queue.h"
#include "LinkedList.h"

typedef struct PriorityQueue {
	Queue* parent;
	size_t sizeofEach;
} PriorityQueue;

typedef struct PQCell {
	int priority;
	void *value;
} PQCell;

PriorityQueue *newPriorityQueue(size_t sizeofEach);

void freePriorityQueue(PriorityQueue *pq, void (*freeValue)(void *value));

int isPQEmpty(const PriorityQueue *pq);

void addToPriorityQueue(PriorityQueue *pq, const void *e, int priority);

void *shiftFromPriorityQueue(PriorityQueue *pq);

#endif
