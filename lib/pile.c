/****************************************************************
 *  Objectif : Implantation d'une pile de char
 ***************************************************************/

#include "pile.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void initialiser(Pile *p) {
	assert(p != NULL);
	p->suivante = NULL;
	assert(est_vide(p));
}

void detruire(Pile *p) {
	assert(p != NULL);
	while (!est_vide(p))
		depiler(p);
}

char sommet(const Pile *p) {
	assert(!est_vide(p));
	return p->suivante->element;
}

void depiler(Pile *p) {
	assert(p != NULL);
	assert(!est_vide(p));
	*p = *(p->suivante);
}

void empiler(Pile *p, char v) {
	assert(p != NULL);
	assert(!est_pleine(p));

	Pile *newSommet = (Pile *)malloc(sizeof(Pile));
	initialiser(newSommet);
	newSommet->suivante = p;

	p->element = v;
	*p = *newSommet;
	
	assert(sommet(p) == v);
}

bool est_vide(const Pile *p) { return p->suivante == NULL; }

bool est_pleine(const Pile *p) {
	int length = 0;
	while (p->suivante != NULL) {
		p = p->suivante;
		++length;
	}

	return length > PILE_CAPACITE;
}
