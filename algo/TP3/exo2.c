#include "evenement.h"
#include "linkedList.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	LinkedList *evts = newLinkedList();
	time_t t0 = time(NULL);
	ajouterEvenementListe(&evts, t0, "first event");
	ajouterEvenementListe(&evts, t0 + 2, "third event");
	ajouterEvenementListe(&evts, t0 + 3, "fourth event");
	ajouterEvenementListe(&evts, t0 + 1, "second event");
	ajouterEvenementListe(&evts, t0 + 4, "fifth event");

	assert(evts->value->e.dateEvenement == t0 + 4);
	assert(strcmp(evts->value->e.valeurEvenement, "fifth event") == 0);

	afficheListeEvenement(evts);

	printf("---------------------\n");

	afficheEvenementAutour(evts, t0 + 2, 1);
	return 0;
}
