/****************************************************************
 *  Objectif : Implantation d'une pile de char
 ***************************************************************/

#include "Pile.h"
#include <assert.h>
#include <stdlib.h>

void initialiser(Pile *p) {
	assert(p != NULL);
	p->suivante = NULL;
	assert(est_vide(p));
}

Pile *newPile(){
	Pile *oldTop = (Pile *)malloc(sizeof(Pile));
	initialiser(oldTop);
	return oldTop;
}

void detruire(Pile *p) {
	assert(p != NULL);
	while (!est_vide(p))
		depiler(p);
}

Cell *sommet(const Pile *p) {
	assert(!est_vide(p));
	Cell *top = malloc(sizeof(Cell));
	cellcpy(top, p->element);
	return top;
}

void depiler(Pile *p) {
	assert(p != NULL);
	assert(!est_vide(p));
	freeCell(p->element);
	*p = *(p->suivante);
}

void empiler(Pile *p, const Cell *v) {
	assert(p != NULL);
	assert(!est_pleine(p));

	Pile *oldTop = newPile();
	assert(oldTop != NULL);
	oldTop->element = p->element;
	oldTop->suivante = p->suivante;	

	assert(cellcpy(p->element, v) != NULL);
	p->suivante = oldTop;
	
	assert(sommet(p) == v);
}

bool est_vide(const Pile *p) { return p->element == NULL; }

bool est_pleine(const Pile *p) {
	int length = 0;
	while (p != NULL) {
		p = p->suivante;
		++length;
	}
	return length >= PILE_CAPACITE;
}
