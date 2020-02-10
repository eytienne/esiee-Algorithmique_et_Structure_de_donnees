#include "linkedList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList *newLinkedList(size_t size) {
	LinkedList *newList = (LinkedList *)malloc(sizeof(LinkedList));
	assert(newList != NULL);
	newList->sizeofEach = size;
	newList->first = newList->last = NULL;
	return newList;
}

void freeLinkedList(LinkedList *f) {
	assert(f != NULL);
	LLCell *cur = f->first;
	while (cur != NULL) {
		LLCell *next = cur->next;
		free(cur);
		cur = next;
	}
	f->first = f->last = NULL;
	free(f);
}

void addToLinkedList(LinkedList *list, void *e) {
	assert(list != NULL);
	void *newElement = malloc(sizeof(list->sizeofEach));
	assert(newElement != NULL);
	memcpy(newElement, e, list->sizeofEach);

	LLCell *newLink = malloc(sizeof(LLCell));
	assert(newLink != NULL);
	newLink->value = newElement;
	newLink->next = NULL;

	if (list->first == NULL) {
		newLink->previous = NULL;
		list->first = newLink;
	} else {
		list->last->next = newLink;
		newLink->previous = list->last;
	}
	list->last = newLink;
}

int isEmpty(const LinkedList *l) { return l->first == NULL; }