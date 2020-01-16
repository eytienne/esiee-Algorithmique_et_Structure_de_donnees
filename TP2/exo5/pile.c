/****************************************************************
 *  Objectif : Implantation d'une pile de char
 ***************************************************************/

#include "pile.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void initialiser(Pile *p) {
	assert(p != NULL);
	Pile pp = (Pile)malloc(sizeof(Cellule));
	pp->suivante = NULL;
	*p = pp;
	assert(est_vide(*p));
}

void detruire(Pile *p) {
	assert(p != NULL);
	while (!est_vide(*p))
		depiler(p);
}

char sommet(Pile p) {
	assert(!est_vide(p));
	return p->suivante->element;
}

void depiler(Pile *p) {
	assert(p != NULL);
	assert(!est_vide(*p));
	*p = (*p)->suivante;
}

void empiler(Pile *p, char v) {
	assert(p != NULL);
	assert(!est_pleine(*p));

	Pile newSommet;
	initialiser(&newSommet);
	(*p)->element = v;
	newSommet->suivante = (Cellule *)*p;
	*p = newSommet;
	printf("%c\n", (*p)->suivante->element);
	assert(sommet(*p) == v);
}

bool est_vide(Pile p) { return p->suivante == NULL; }

bool est_pleine(Pile p) {
	int length = 0;
	while (p->suivante != NULL) {
		p = p->suivante;
		++length;
	}

	return length > PILE_CAPACITE;
}
