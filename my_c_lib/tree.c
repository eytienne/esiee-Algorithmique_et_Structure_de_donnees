#include "tree.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef Tree **SonParentDuet;
SonParentDuet newSonParentDuet();

int __nombre_de_noeuds(const Tree *t, void *counter);
int __affiche_arbre(const Tree *t, void *first);
SonParentDuet findNodeWithParent(Tree *t, const Cell *value,
								 int (*cmpFunc)(const Cell *value,
												const Cell *existing));
int __verifie(const Tree *t, void *lastNodeValue);
int __tri(const Tree *t, void *si);
void cutTree(Tree *toCut, Tree *from);
int minValue(const Tree *t);
Tree *minNode(Tree *t);
SonParentDuet minNodeWithParent(Tree *t);

Tree *cree_arbre(const Cell *value, Tree *left, Tree *right) {
	Tree *t = (Tree *)malloc(sizeof(Tree));
	Cell *initValue = malloc(sizeof(Cell));
	cellcpy(initValue, value);
	t->value = initValue;
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

void insere(Tree *t, const Cell *newValue,
			int (*cmpFunc)(const Cell *newValue, const Cell *existing)) {
	while (1) {
		if (cmpFunc(newValue, t->value) > 0)
			if (t->right == NULL) {
				t->right = cree_arbre(newValue, NULL, NULL);
				return;
			} else
				t = t->right;
		else if (cmpFunc(newValue, t->value) <= 0)
			if (t->left == NULL) {
				t->left = cree_arbre(newValue, NULL, NULL);
				return;
			} else
				t = t->left;
	}
}

Tree *trouve_noeud(Tree *t, const Cell *value,
				   int (*cmpFunc)(const Cell *value, const Cell *existing)) {
	SonParentDuet twp = findNodeWithParent(t, value, cmpFunc);
	Tree *ret = twp[0];
	free(twp);
	return ret;
}

SonParentDuet findNodeWithParent(Tree *t, const Cell *value,
								 int (*cmpFunc)(const Cell *value,
												const Cell *existing)) {
	SonParentDuet twp = newSonParentDuet();
	while (t != NULL) {
		int cmp = cmpFunc(value, t->value);
		if (cmp == 0) {
			twp[0] = t;
			break;
		} else if (cmp > 0)
			t = t->right;
		else
			t = t->left;
		twp[1] = t;
	}
	return twp;
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

typedef struct CheckInfo {
	Cell *lastCell;
	int (*cmpFunc)(const Cell *value, const Cell *existing);
} CheckInfo;

int verifie(Tree *t, int (*cmpFunc)(const Cell *value, const Cell *existing)) {
	CheckInfo ci;
	ci.lastCell = NULL;
	ci.cmpFunc = cmpFunc;
	int badWalk = walk(t, INFIXE, __verifie, &ci);
	return badWalk ? ISNOTBST : ISBST;
}

int __verifie(const Tree *t, void *buffer) {
	const CheckInfo *ci = (CheckInfo *)*buffer;
	int cmp = ci->cmpFunc(t->value, ci->lastCell);
	if (cmp < 0)
		return ISNOTBST;
	ci->lastCell = t->value;
	return ISBST;
}

typedef struct SortInfo {
	Cell **dest;
	int index;
} SortInfo;

int *tri(int *src, int n) {
	if (n <= 0)
		return NULL;

	Tree *t = cree_arbre(src[0], NULL, NULL);
	for (int i = 0; i < n; i++)
		insere(t, src[i]);

	SortInfo si;
	si.dest = calloc(n, sizeof(int));
	si.index = 0;
	int failed = walk(t, INFIXE, __tri, &si);
	int *ret = si.dest;
	if (failed) {
		free(ret);
		return NULL;
	}
	return ret;
}

int __tri(const Tree *t, void *si) {
	SortInfo *csi = (SortInfo *)si;
	cellcpy(csi->dest[csi->index], t->value);
	csi->index++;
	return WALK_SUCCESS;
}

void supprime(Tree **t, const Cell *oldValue,
			  int (*cmpFunc)(const Cell *oldValue, const Cell *existing)) {
	SonParentDuet pair = findNodeWithParent(*t, oldValue);
	Tree *toRemove = pair[0], *parent = pair[1];
	if (toRemove == NULL)
		return;
	Tree *newSon = NULL;
	if (toRemove->left != NULL && toRemove->right != NULL) {
		SonParentDuet spd = minNodeWithParent(toRemove->right);
		// clean min removal
		spd[1]->left = spd[0]->right;

		newSon = spd[0];
	} else if (toRemove->left == NULL ^ toRemove->right == NULL) {
		newSon = toRemove->left != NULL ? toRemove->left : toRemove->right;
	}
	if (newSon != NULL) {
		newSon->left = toRemove->left;
		newSon->right = toRemove->right;
	}
	if (parent == NULL)
		*t = newSon;
	else {
		if (parent->left == NULL)
			parent->left = newSon;
		else
			parent->right = newSon;
	}
	free(toRemove);
}

void cutTree(Tree *toCut, Tree *from) {
	if (from->left == toCut)
		from->left = NULL;
	else if (from->right == toCut)
		from->right = NULL;
}

int minValue(const Tree *t) { return minNode(t)->value; }

Tree *minNode(Tree *t) { return minNodeWithParent(t)[0]; }

SonParentDuet minNodeWithParent(Tree *t) {
	SonParentDuet spd = newSonParentDuet();
	spd[0] = t;
	while (t->left != NULL) {
		spd[0] = t->left;
		spd[1] = t;
		t = t->left;
	}
	return spd;
}

SonParentDuet newSonParentDuet() {
	Tree **twp = (Tree **)malloc(2 * sizeof(Tree *));
	twp[0] = NULL; // son
	twp[1] = NULL; // parent
	return twp;
}