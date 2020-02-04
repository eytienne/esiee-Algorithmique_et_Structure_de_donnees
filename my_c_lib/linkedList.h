#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "element.h"

typedef struct LinkedList {
    Element *value;
    struct LinkedList *previous;
    struct LinkedList *next;
} LinkedList;

LinkedList *newLinkedList();

LinkedList *freeLinkedList();

void ajouterAListe(LinkedList **list, Element *e);

#endif