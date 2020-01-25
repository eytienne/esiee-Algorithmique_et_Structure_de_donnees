#include "tree.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int __affiche_arbre(Tree *t, void *first);
int __verifie(Tree *t, void *lastNodeValue);
int __tri(Tree *t, void *si);

Tree *cree_arbre(int value, Tree *left, Tree *right) {
	Tree *t = (Tree *)malloc(sizeof(Tree));
	t->value = value;
	t->left = left;
	t->right = right;
	return t;
}

void detruit_arbre(Tree *t) {
	if (t->left != NULL)
		detruit_arbre(t->left);
	if (t->right != NULL)
		detruit_arbre(t->right);
	free(t);
}

int nombre_de_noeuds(const Tree *t) {
	if (t == NULL)
		return 0;
	return 1 + nombre_de_noeuds(t->left) + nombre_de_noeuds(t->right);
}

void affiche_arbre(Tree *t) {
	int first = 1;
	walk(t, INFIXE, __affiche_arbre, &first);
	printf("\n");
}

int __affiche_arbre(Tree *t, void *first) {
	if (t == NULL)
		return 2;
	if (!*(int *)first)
		printf("\t");
	printf("%d", t->value);
	if (*(int *)first)
		*(int *)first = 0;
	return 0;
}

void affiche_arbre2(const Tree *t) {
	if (t == NULL) {
		printf("_");
		return;
	}
	printf("{");
	affiche_arbre2(t->left);
	printf(",%d,", t->value);
	affiche_arbre2(t->right);
	printf("}");
}

void insere(Tree *t, int value) {
	if (value > t->value)
		if (t->right == NULL)
			t->right = cree_arbre(value, NULL, NULL);
		else
			insere(t->right, value);
	else if (value < t->value)
		if (t->left == NULL)
			t->left = cree_arbre(value, NULL, NULL);
		else
			insere(t->left, value);
}

Tree *trouve_noeud(Tree *t, int value) {
	if (t == NULL)
		return NULL;
	if (t->value == value)
		return t;
	else {
		if (value > t->value)
			return trouve_noeud(t->right, value);
		else
			return trouve_noeud(t->left, value);
	}
}

int walk(Tree *t, enum PATHWAY p, int (*function)(Tree *, void *buffer),
		 void *buffer) {
	if (t == NULL)
		return 0;
	switch (p) {
	case INFIXE:
		if (walk(t->left, p, function, buffer))
			return 1;
		if (function(t, buffer))
			return 1;
		if (walk(t->right, p, function, buffer))
			return 1;
		break;
	case PREFIXE:
		if (function(t, buffer))
			return 1;
		if (walk(t->left, p, function, buffer))
			return 1;
		if (walk(t->right, p, function, buffer))
			return 1;
		break;
	case POSTFIXE:
		if (walk(t->left, p, function, buffer))
			return 1;
		if (walk(t->right, p, function, buffer))
			return 1;
		if (function(t, buffer))
			return 1;
		break;
	}
	return 0;
}

int isLeaf(const Tree *t) {
	assert(t != NULL);
	return t->left == NULL && t->right == NULL;
}

int verifie(Tree *t) {
	int buffer = INT_MIN;
	int badWalk = walk(t, INFIXE, __verifie, &buffer);
	return badWalk;
}

int __verifie(Tree *t, void *lastNodeValue) {
	int *lnv = (int *)lastNodeValue;
	if (t->value < *lnv)
		return ISNOTBST;
	*lnv = t->value;
	return ISBST;
}

typedef struct SortInfo {
	int *dest;
	size_t size;
} SortInfo;

int *tri(int *src, int n) {
	if (n <= 0)
		return NULL;

	SortInfo *si = (SortInfo *)malloc(sizeof(SortInfo));
	si->dest = NULL;
	si->size = 0;

	Tree *t = cree_arbre(src[0], NULL, NULL);
	for (int i = 0; i < n; i++)
		insere(t, i);
	affiche_arbre2(t);
	printf("\n");

	int failed = walk(t, INFIXE, __tri, si);
	if (failed)
		return NULL;

	return si->dest;
}

int __tri(Tree *t, void *si) {
	SortInfo *csi = (SortInfo *)si;
	int *newDest = (int *)realloc(csi->dest, csi->size + sizeof(int));
	if (newDest == NULL)
		return WALK_FAILURE;
	newDest[csi->size] = t->value;
	csi->dest = newDest;
	csi->size++;
	return WALK_SUCCESS;
}