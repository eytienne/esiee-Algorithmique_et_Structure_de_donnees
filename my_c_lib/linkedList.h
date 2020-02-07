#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

typedef struct LLCell {
	void *value;
	struct LLCell *previous, *next;
} LLCell;

typedef struct LinkedList {
    LLCell* first;
    LLCell *last;
    size_t sizeofEach;
} LinkedList;

LinkedList *newLinkedList(size_t size);

void freeLinkedList(LinkedList *f);

void addToLinkedList(LinkedList *list, void *e);

#endif