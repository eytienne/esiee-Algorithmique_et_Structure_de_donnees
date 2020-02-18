#include "PriorityQueue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pq_cell_cmp(const PQCell *pq1, const PQCell *pq2) {
	assert(pq1 && pq2 && "Null pointers not allowed for PQCell comparison.");
	return pq1->priority - pq2->priority;
}

PQCell *newPQCell(const void *e, size_t size, int priority) {
	PQCell *newOne = malloc(sizeof(PQCell));
	newOne->value = malloc(size);
	memcpy(newOne->value, e, size);
	newOne->priority = priority;
	return newOne;
}

PriorityQueue *newPriorityQueue(size_t sizeofEach) {
	return newLinkedList(sizeof(PQCell));
}

void freePQCell(void *value, void *buffer) {
	PQCell *cvalue = (PQCell *)value;
	void (*realFreeValue)(void *value) = (void (*)(void *))buffer;
	realFreeValue(cvalue->value);
	free(cvalue);
}

void freePriorityQueue(PriorityQueue *pq, void (*freeValue)(void *value)) {
	freeLinkedListWithBuffer(pq, freePQCell, freeValue);
}

void addToPriorityQueue(PriorityQueue *pq, const void *e, int priority) {
	LLCell *newOne = malloc(sizeof(LLCell));
	newOne->value = newPQCell(e, pq->sizeofEach, priority);

	if (pq->first == NULL) {
		newOne->previous = NULL;
		newOne->next = NULL;
		pq->first = pq->last = newOne;
		// printf("first first!\n");
		return;
	}
	LLCell *cur = pq->first;
	// tant que le nouveau est supérieur ou égal alors on passe
	while (cur != NULL && pq_cell_cmp((const PQCell *)newOne->value,
									  (const PQCell *)cur->value) >= 0) {
		cur = cur->next;
	}
	if (cur == pq->first) { // insert as new first
		newOne->next = pq->first;
		pq->first->previous = newOne;
		pq->first = newOne;
		// printf("new first!\n");
	} else if (cur == NULL) { // insert as new last
		newOne->previous = pq->last;
		newOne->next = NULL;
		pq->last->next = newOne;
		pq->last = newOne;
		// printf("last!\n");
	} else { // insert in the middle
		newOne->previous = cur->previous;
		cur->previous->next = newOne;
		newOne->next = cur;
		cur->previous = newOne;
		// printf("boom\n");
	}
}

void *shiftFromPriorityQueue(PriorityQueue *pq) {
	PQCell *toFree = shift(pq);
	void *ret = toFree->value;
	free(toFree);
	return ret;
}