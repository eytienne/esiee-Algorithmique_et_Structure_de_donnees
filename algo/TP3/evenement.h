#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <time.h>

typedef struct LinkedList LinkedList;

typedef struct Evenement {
	time_t dateEvenement;
	char *valeurEvenement;
} Evenement;

struct Element {
	Evenement e;
};

int ajouterEvenementListe(LinkedList **evts, time_t eventDate,
						  const char *eventValue);

void afficheListeEvenement(const LinkedList *evts);

void afficheEvenement(const LinkedList *evts, time_t dateEvenement);

void afficheEvenementAutour(const LinkedList *evts, time_t dateEvenement,
							int beforeAfter);

#endif