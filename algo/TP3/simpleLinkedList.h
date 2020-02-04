#ifndef SIMPLELINKEDLIST_H
#define SIMPLELINKEDLIST_H

#include "element.h"

typedef struct SimpleLinkedList {
    Element *value;
    struct SimpleLinkedList *next;
} SimpleLinkedList;

SimpleLinkedList *newSimpleLinkedList();

void ajouterAListe(SimpleLinkedList **list, Element *e);

#endif