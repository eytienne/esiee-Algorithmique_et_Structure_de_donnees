#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

typedef struct LLCell {
	void *value;
	struct LLCell *previous, *next;
} LLCell;

typedef struct LinkedList {
    LLCell* first;
    LLCell *last;
    size_t sizeofEach;
} LinkedList;

LinkedList *newLinkedList(size_t sizeofEach);

void freeLinkedList(LinkedList *l, void (*freeValue)(void *value));

void freeLinkedListWithBuffer(LinkedList *l, void (*freeValue)(void *value, void *buffer), void *buffer);

void addToLinkedList(LinkedList *l, void *e);

int isLLEmpty(const LinkedList *l);

#endif