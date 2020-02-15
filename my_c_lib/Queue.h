#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

typedef LinkedList Queue;

Queue *newQueue(size_t sizeofEach);

void freeQueue(Queue *q, void (*freeValue)(void *value));

void addToQueue(Queue *q, void *e);

void *shift(Queue *q);

#endif