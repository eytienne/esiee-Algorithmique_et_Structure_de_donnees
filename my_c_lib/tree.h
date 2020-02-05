#ifndef TREE_H
#define TREE_H

#include "cell.h"

typedef struct Tree {
	Cell *value;
	struct Tree *left;
	struct Tree *right;
} Tree;

enum PATHWAY { INFIXE, PREFIXE, POSTFIXE };

enum WALK_CHECK { WALK_SUCCESS, WALK_FAILURE };

enum BST_CHECK { ISBST = WALK_SUCCESS, ISNOTBST = WALK_FAILURE };

Tree *cree_arbre(const Cell *value, Tree *left, Tree *right);

void detruit_arbre(Tree *t);

int nombre_de_noeuds(const Tree *t);

void affiche_arbre(const Tree *t);

void affiche_arbre2(const Tree *t);

void insere(Tree *t, const Cell *newValue,
			int (*cmpFunc)(const Cell *newValue, const Cell *existing));

Tree *trouve_noeud(Tree *t, const Cell *value,
				   int (*cmpFunc)(const Cell *value, const Cell *existing));

int walk(const Tree *t, enum PATHWAY p,
		 int (*function)(const Tree *, void *buffer), void *buffer);

int isLeaf(const Tree *t);

int verifie(Tree *t, int (*cmpFunc)(const Cell *value, const Cell *existing));

int *tri(int *src, int n);

void supprime(Tree **t, const Cell *oldValue,
			  int (*cmpFunc)(const Cell *oldValue, const Cell *existing));

#endif