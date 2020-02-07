#ifndef __LISTE2__H_
#define __LISTE2__H_

/*---------------Prototypes Structures ---------------*/

typedef struct Element {
	struct Tree *arbre;
	struct Element *suivant;
	struct Element *precedent;
} Element;

typedef struct LinkedList {
	struct Element *premier;
	struct Element *dernier;
} LinkedList;

/*---------------Prototypes fonctions ---------------*/

LinkedList *newLinkedList();
void ajouterListe(LinkedList *l, Tree *arbre);

#endif
