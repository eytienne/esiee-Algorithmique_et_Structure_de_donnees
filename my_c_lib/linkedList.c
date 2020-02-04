#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

LinkedList *newLinkedList() {
	LinkedList *newList = (LinkedList *)malloc(sizeof(LinkedList));
	assert(newList != NULL);
	newList->value = NULL;
	newList->previous = NULL;
	newList->next = NULL;
	return newList;
}

void ajouterAListe(LinkedList **list, Element *e) {
	assert(list != NULL);

	Element *newElement = (Element *)malloc(sizeof(Element));
	assert(newElement != NULL);
	memcpy(newElement, e, sizeof(Element));

	if ((*list)->value == NULL) {
		(*list)->value = newElement;
		return;
	}
	LinkedList *newLink = newLinkedList();
	newLink->value = newElement;
    newLink->previous = NULL;
	newLink->next = *list;
    (*list)->previous = newLink;
    
	*list = newLink;
}
