#include "tree.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int __nombre_de_noeuds(const Tree *t, void *counter);
int __affiche_arbre(const Tree *t, void *first);
int __verifie(const Tree *t, void *lastNodeValue);
int __tri(const Tree *t, void *si);

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
	int counter = 0;
	walk(t, INFIXE, __nombre_de_noeuds, &counter);
	return counter;
}

int __nombre_de_noeuds(const Tree *t, void *counter) {
	++*(int *)counter;
	return WALK_SUCCESS;
}

void affiche_arbre(const Tree *t) {
	int first = 1;
	walk(t, INFIXE, __affiche_arbre, &first);
	printf("\n");
}

int __affiche_arbre(const Tree *t, void *first) {
	if (t == NULL)
		return WALK_SUCCESS;
	if (!*(int *)first)
		printf("\t");
	printf("%d", t->value);
	if (*(int *)first)
		*(int *)first = 0;
	return WALK_SUCCESS;
}

void __affiche_arbre2(const Tree *t) {
	if (t == NULL) {
		printf("_");
		return;
	}
	printf("{");
	__affiche_arbre2(t->left);
	printf(",%d,", t->value);
	__affiche_arbre2(t->right);
	printf("}");
}

void affiche_arbre2(const Tree *t) {
	__affiche_arbre2(t);
	printf("\n");
}

void insere(Tree *t, int value) {
	while (1) {
		if (value > t->value)
			if (t->right == NULL) {
				t->right = cree_arbre(value, NULL, NULL);
				return;
			} else
				t = t->right;
		else if (value <= t->value)
			if (t->left == NULL) {
				t->left = cree_arbre(value, NULL, NULL);
				return;
			} else
				t = t->left;
	}
}

Tree *trouve_noeud(Tree *t, int value) {
	while (t != NULL)
		if (value == t->value)
			return t;
		else if (value > t->value)
			t = t->right;
		else
			t = t->left;
	return NULL;
}

int walk(const Tree *t, enum PATHWAY p,
		 int (*function)(const Tree *, void *buffer), void *buffer) {
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
	return badWalk ? ISNOTBST : ISBST;
}

int __verifie(const Tree *t, void *lastNodeValue) {
	int *lnv = (int *)lastNodeValue;
	if (t->value < *lnv)
		return ISNOTBST;
	*lnv = t->value;
	return ISBST;
}

typedef struct SortInfo {
	int *dest;
	int index;
} SortInfo;

int *tri(int *src, int n) {
	if (n <= 0)
		return NULL;

	Tree *t = cree_arbre(src[0], NULL, NULL);
	for (int i = 0; i < n; i++)
		insere(t, src[i]);

	SortInfo *si = (SortInfo *)malloc(sizeof(SortInfo));
	si->dest = calloc(n, sizeof(int));
	si->index = 0;
	int failed = walk(t, INFIXE, __tri, si);
	int *ret = si->dest;
	free(si);
	if (failed) {
		free(ret);
		return NULL;
	}
	return ret;
}

int __tri(const Tree *t, void *si) {
	SortInfo *csi = (SortInfo *)si;
	csi->dest[csi->index] = t->value;
	csi->index++;
	return WALK_SUCCESS;
}
