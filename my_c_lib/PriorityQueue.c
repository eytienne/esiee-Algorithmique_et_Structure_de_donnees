#include "PriorityQueue.h"
#include <string.h>

typedef struct PQCell {
	int priority;
	void *value;
} PQCell;

int pq_cell_cmp(const void *c1, const void *c2) {
	return ((PQCell *)c1)->priority - ((PQCell *)c2)->priority;
}

PQCell *newPQCell(void *e, size_t size, int priority) {
	PQCell *newOne = malloc(sizeof(PQCell));
	newOne->value = malloc(size);
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

void addToPriorityQueue(PriorityQueue *pq, void *e, int priority) {
	LLCell *newOne = malloc(sizeof(LLCell));
	newOne->value = newPQCell(e, pq->sizeofEach, priority);

	if (pq->first == NULL) {
		newOne->previous = NULL;
		newOne->next = NULL;
		pq->first = pq->last = newOne;
		return;
	}
	
	LLCell *cur = pq->first;
	while (cur->next != NULL && pq_cell_cmp(cur->value, newOne->value) <= 0)
		cur = cur->next;
	newOne->previous = cur;
	newOne->next = cur->next;
	if(cur == pq->last)
		pq->last = newOne;
	newOne->next = cur->next;
}