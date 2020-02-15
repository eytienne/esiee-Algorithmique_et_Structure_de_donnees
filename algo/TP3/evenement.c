#include "evenement.h"
#include "../../my_c_lib/LinkedList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printEvenement(const Evenement *toPrint);

int ajouterEvenementListe(LinkedList *evts, time_t eventDate,
						  const char *eventValue) {
	Evenement *e = malloc(sizeof(Evenement));
	assert(e != NULL);
	e->dateEvenement = eventDate;
	size_t strLen = strlen(eventValue);
	e->valeurEvenement = (char *)malloc(strLen);
	assert(e->valeurEvenement != NULL);
	strncpy(e->valeurEvenement, eventValue, strLen);
	// printf("copied (%ld): %s\n", strLen, e->valeurEvenement);
	addToLinkedList(evts, e);
}

void afficheListeEvenement(const LinkedList *evts) {
	assert(evts != NULL);
	LLCell *cur = evts->first;
	while (cur != NULL) {
		printEvenement(cur->value);
		cur = cur->next;
	}
}

void afficheEvenement(const LinkedList *evts, time_t dateEvenement) {
	afficheEvenementAutour(evts, dateEvenement, 0);
}

void afficheEvenementAutour(const LinkedList *evts, time_t dateEvenement,
							int beforeAfter) {
	assert(evts != NULL);
	const LLCell *cur = evts->first;
	const LLCell *toPrint = NULL;
	while (cur != NULL) {
		if (((Evenement *)cur->value)->dateEvenement == dateEvenement) {
			toPrint = cur;
			break;
		}
		cur = cur->next;
	}
	if (toPrint != NULL) {
		for (int i = 0; i < beforeAfter && cur->previous != NULL; i++)
			cur = cur->previous;
		while (cur != toPrint) {
			printEvenement(cur->value);
			cur = cur->next;
		}
		for (int i = 0;
			 i < (beforeAfter + 1) && cur != NULL && cur->value != NULL; i++) {
			printEvenement(cur->value);
			cur = cur->next;
		}
	}
}

void printEvenement(const Evenement *toPrint) {
	assert(toPrint != NULL);
	assert(toPrint->valeurEvenement != NULL);
	printf("[%ld] : %s\n", toPrint->dateEvenement, toPrint->valeurEvenement);
}