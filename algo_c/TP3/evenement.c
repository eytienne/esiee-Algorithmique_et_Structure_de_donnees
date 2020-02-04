#include "evenement.h"
#include "linkedList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printEvenement(const Evenement *toPrint);

int ajouterEvenementListe(LinkedList **evts, time_t eventDate,
						  const char *eventValue) {
	Element e;
	e.e.dateEvenement = eventDate;
	size_t strLen = strlen(eventValue);
	e.e.valeurEvenement = (char *)malloc(strLen);
	strncpy(e.e.valeurEvenement, eventValue, strLen);
	ajouterAListe(evts, &e);
}

void afficheListeEvenement(const LinkedList *evts) {
	assert(evts != NULL);
	int i = 0;
	while (evts != NULL && evts->value != NULL) {
		printEvenement(&evts->value->e);
		evts = evts->next;
	}
}

void afficheEvenement(const LinkedList *evts, time_t dateEvenement) {
	afficheEvenementAutour(evts, dateEvenement, 0);
}

void afficheEvenementAutour(const LinkedList *evts, time_t dateEvenement,
							int beforeAfter) {
	assert(evts != NULL);
	const LinkedList *toPrint = NULL;
	while (evts->value != NULL) {
		if (evts->value->e.dateEvenement == dateEvenement) {
			toPrint = evts;
			break;
		}
		evts = evts->next;
	}
	if (toPrint != NULL) {
		for (int i = 0; i < beforeAfter && evts->previous != NULL; i++)
			evts = evts->previous;
		while (evts != toPrint) {
			printEvenement(&evts->value->e);
			evts = evts->next;
		}
		for (int i = 0;
			 i < (beforeAfter + 1) && evts != NULL && evts->value != NULL;
			 i++) {
			printEvenement(&evts->value->e);
			evts = evts->next;
		}
	}
}

void printEvenement(const Evenement *toPrint) {
	assert(toPrint != NULL);
	assert(toPrint->valeurEvenement != NULL);
	printf("[%ld] : %s\n", toPrint->dateEvenement, toPrint->valeurEvenement);
}