#include "LinkedList.h"
#include "compressionTree.h"
#include <stdio.h>
#include <stdlib.h>

LinkedList *newLinkedList() {
	LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
	if (list == NULL) {
		printf("Erreur allocation Liste\n");
		exit(EXIT_FAILURE);
	}
	list->premier = NULL;
	list->dernier = NULL;
	return list;
}

void ajouterListe(LinkedList *l, Tree *arbre) {
	Element *element = (Element *)malloc(sizeof(Element));

	element->arbre = arbre;
	Element *temp = l->premier;
	if (arbre->value == (char)0) {
		while ((temp != NULL) && (temp->arbre->encountered <= arbre->encountered)) {

			temp = temp->suivant;
		}

	} else {
		while ((temp != NULL) && (temp->arbre->encountered < arbre->encountered)) {

			temp = temp->suivant;
		}

		while ((temp != NULL) && (temp->arbre->encountered == arbre->encountered) &&
			   (temp->arbre->value < arbre->value)) {
			temp = temp->suivant;
		}
	}
	element->suivant = temp;
	if (temp != NULL && temp->precedent != NULL) {
		temp->precedent->suivant = element;
		element->precedent = temp->precedent;
	} else {
		element->precedent = NULL;
	}
	if (temp != NULL) {
		temp->precedent = element;
	}
	if (temp == l->premier) {
		l->premier = element;
	}

	if (temp == NULL) {
		element->precedent = l->dernier;
		l->dernier = element;
	}
}

