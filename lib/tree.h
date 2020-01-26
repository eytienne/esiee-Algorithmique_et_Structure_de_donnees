#ifndef TREE_H
#define TREE_H

typedef struct Tree {
	int value;
	struct Tree *left;
	struct Tree *right;
} Tree;

typedef struct TreeWithParent {
	struct TreeWithParent *parent;
	Tree *current;

} TreeWithParent;

enum PATHWAY { INFIXE, PREFIXE, POSTFIXE };

enum WALKCHECK { WALK_SUCCESS, WALK_FAILURE };

#define ISBST WALK_SUCCESS
#define ISNOTBST WALK_FAILURE

Tree *cree_arbre(int value, Tree *left, Tree *right);

void detruit_arbre(Tree *t);

int nombre_de_noeuds(const Tree *t);

void affiche_arbre(const Tree *t);

void affiche_arbre2(const Tree *t);

void insere(Tree *t, int value);

Tree *trouve_noeud(Tree *t, int value);

int walk(const Tree *t, enum PATHWAY p,
		 int (*function)(const Tree *, void *buffer), void *buffer);

int isLeaf(const Tree *t);

int verifie(Tree *t);

int *tri(int *src, int n);

#endif