/****************************************************************
 *  Objectif : D�finition d'une pile de char
 ***************************************************************/

#ifndef PILE__H /* prot�ger contre la double inclusion */
#define PILE__H

#include <stdbool.h>
#include "Cell.h"

#define PILE_CAPACITE 10 /* Taille de la pile */

typedef struct Pile {
	Cell *element;		   /* l'�l�ment de la cellule */
	struct Pile *suivante; /* acc�s � la cellule suivante */
} Pile;

void initialiser(Pile *p);
/* Initialiser la pile.  La pile est vide.
 *
 * N�cessite :
 *	p != NULL;
 *
 * Assure :
 *	est_vide(*p);
 */

Pile *newPile();

void detruire(Pile *p);
/* D�truire la pile.  Les ressources associ�es seront lib�r�es et la
 * pile p ne devra plus �tre utilis�e.
 *
 * N�cessite :
 *	p != NULL;
 */

char sommet(const Pile *p);
/* L'�l�ment au sommet de la pile p.
 *
 * N�cessite :
 *	! est_vide(p);
 */

void depiler(Pile *p);
/* Supprimer l'�l�ment au sommet de la pile p.
 *
 * N�cessite :
 *	p != NULL;
 *	! est_vide(*p);
 */

void empiler(Pile *p, const Cell *v);
/* Ajouter l'�l�ment v en sommet de pile p.
 *
 * N�cessite :
 *	p != NULL;
 *	! est_pleine(*p);
 *
 * Assure :
 *	sommet(*p) == v;
 */

bool est_vide(const Pile *p);
/* la pile est-elle vide ?  */

bool est_pleine(const Pile *p);
/* la pile est-elle pleine ?  */

#endif
