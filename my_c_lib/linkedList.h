#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "element.h"

typedef struct LinkedList {
    Element *value;
    struct LinkedList *previous;
    struct LinkedList *next;
} LinkedList;

LinkedList *newLinkedList(size_t sizeofEach);

void freeLinkedList(LinkedList *l);

void addToLinkedList(LinkedList *l, void *e);

int isEmpty(const LinkedList *l);

#endif