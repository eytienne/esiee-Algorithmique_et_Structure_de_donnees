#include "simpleLinkedList.h"
#include "element.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SimpleLinkedList *newSimpleLinkedList() {
	SimpleLinkedList *newList =
		(SimpleLinkedList *)malloc(sizeof(SimpleLinkedList));
	assert(newList != NULL);
	newList->value = NULL;
	newList->next = NULL;
	return newList;
}

void ajouterAListe(SimpleLinkedList **list, Element *e) {
	assert(list != NULL);

	Element *newElement = (Element *)malloc(sizeof(Element));
	assert(newElement != NULL);
	memcpy(newElement, e, sizeof(Element));

	if ((*list)->value == NULL) {
		(*list)->value = newElement;
		return;
	}
	SimpleLinkedList *newLink = newSimpleLinkedList();
	newLink->value = newElement;
	newLink->next = *list;
	*list = newLink;
}