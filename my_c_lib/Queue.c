#include "Queue.h"
#include <assert.h>

Queue *newQueue(size_t sizeofEach) {
	return (Queue *)newLinkedList(sizeofEach);
}

void freeQueue(Queue *q, void (*freeValue)(void *value)) {
	freeLinkedList(q, freeValue);
}

void addToQueue(Queue *q, void *e) { addToLinkedList(q, e); }

void *shift(Queue *q) {
	assert(q != NULL);
	assert(!isEmpty(q));
	void *ret = q->first->value;
	LLCell *toFree = q->first;
	q->first = q->first->next;
	free(toFree);
	if (q->first != NULL)
		q->first->previous = NULL;
	return ret;
}