#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "element.h"

typedef struct LinkedList {
    Element *value;
    struct LinkedList *previous;
    struct LinkedList *next;
} LinkedList;

LinkedList *newLinkedList();

void ajouterAListe(LinkedList **list, Element *e);

#endif