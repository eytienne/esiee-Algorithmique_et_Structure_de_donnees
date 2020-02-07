#ifndef QUEUE_H
#define QUEUE_H

#include "linkedList.h"

typedef LinkedList Queue;

Queue *newQueue(size_t sizeofEach);

void freeQueue(Queue *f);

void addToQueue(Queue *q, void *e);

void *shift(Queue *q);

#endif