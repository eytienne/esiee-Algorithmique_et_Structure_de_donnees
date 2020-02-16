#include "PriorityQueue.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pq_cell_cmp(const void *c1, const void *c2) {
	assert(c1 && c2 && "Arguments must not be null pointers.");
	const PQCell *pq1 = *(const PQCell **)c1;
	const PQCell *pq2 = *(const PQCell **)c2;
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
	PriorityQueue *newOne = newLinkedList(sizeof(PQCell));
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
		return;
	}

	LLCell *cur = pq->first;
	while (cur->next != NULL && pq_cell_cmp(&cur->value, &newOne->value) <= 0)
		cur = cur->next;
	newOne->previous = cur;
	newOne->next = cur->next;
	if (cur == pq->last)
		pq->last = newOne;
	newOne->next = cur->next;
}