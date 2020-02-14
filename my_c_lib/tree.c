#include "tree.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TreeNode **findNodeWithParent(Tree *t, const void *value);
void cutTree(TreeNode *toCut, TreeNode *from);
const TreeNode **minNodeWithParent(const TreeNode *t);

TreeNode *newTreeNode(const void *value, size_t size) {
	assert(size > 0);
	TreeNode *newOne = (TreeNode *)malloc(sizeof(TreeNode));
	newOne->value = malloc(size);
	memcpy(newOne->value, value, size);
	newOne->left = newOne->right = NULL;
	return newOne;
}

Tree *newTree(size_t sizeofEach,
			  int (*nodecmp)(const void *newValue, const void *existing)) {
	assert(sizeofEach > 0);
	assert(nodecmp != NULL);
	Tree *newOne = (Tree *)malloc(sizeof(Tree));
	newOne->root = NULL;
	newOne->sizeofEach = sizeofEach;
	newOne->nodecmp = nodecmp;
	return newOne;
}

void __freeTree(TreeNode *t) {
	if (t == NULL)
		return;
	__freeTree(t->left);
	__freeTree(t->right);
	free(t);
}

void freeTree(Tree *t) {
	__freeTree(t->root);
	t->sizeofEach = -1;
	t->nodecmp = NULL;
}

int __countTreeNodes(const TreeNode *t, void *counter) {
	++*(int *)counter;
	return WALK_SUCCESS;
}

int countTreeNodes(const Tree *t) {
	int counter = 0;
	walk(t, INFIXE, __countTreeNodes, &counter);
	return counter;
}

typedef struct PrintInfo {
	void (*printer)(const void *value);
	int first;
} PrintInfo;

int __printTree(const TreeNode *t, void *pi) {
	if (t == NULL)
		return WALK_SUCCESS;
	PrintInfo *cpi = (PrintInfo *)pi;
	if (!cpi->first)
		printf("\t");
	cpi->printer(t->value);
	if (cpi->first)
		cpi->first = 0;
	return WALK_SUCCESS;
}

void printTree(const Tree *t, void (*printer)(const void *value)) {
	PrintInfo pi = {printer, 1};
	walk(t, INFIXE, __printTree, &pi);
	printf("\n");
}

void __printTree2(const TreeNode *t, void (*printer)(const void *value)) {
	if (t == NULL) {
		printf("_");
		return;
	}
	printf("{");
	__printTree2(t->left, printer);
	printer(t->value);
	__printTree2(t->right, printer);
	printf("}");
}

void printTree2(const Tree *t, void (*printer)(const void *value)) {
	__printTree2(t->root, printer);
	printf("\n");
}

void insertIntoTree(Tree *t, const void *newValue) {
	assert(t != NULL);
	if (t->root == NULL) {
		t->root = newTreeNode(newValue, t->sizeofEach);
		return;
	}
	TreeNode *cur = t->root;
	while (1) {
		if (t->nodecmp(newValue, cur->value) > 0) {
			if (cur->right == NULL) {
				cur->right = newTreeNode(newValue, t->sizeofEach);
				return;
			} else
				cur = cur->right;
		} else if (t->nodecmp(newValue, cur->value) <= 0) {

			if (cur->left == NULL) {
				cur->left = newTreeNode(newValue, t->sizeofEach);
				return;
			} else
				cur = cur->left;
		}
	}
}

TreeNode *findTreeNode(Tree *t, const void *value) {
	TreeNode **twp = findNodeWithParent(t, value);
	TreeNode *ret = twp[0];
	free(twp);
	return ret;
}

TreeNode **findNodeWithParent(Tree *t, const void *value) {
	TreeNode **twp = malloc(2 * sizeof(TreeNode *));
	twp[0] = twp[1] = NULL;
	TreeNode *cur = t->root;
	while (cur != NULL) {
		int cmp = t->nodecmp(value, cur->value);
		if (cmp == 0) {
			twp[0] = cur;
			break;
		} else if (cmp > 0)
			cur = cur->right;
		else
			cur = cur->left;
		twp[1] = cur;
	}
	return twp;
}

int __walk(const TreeNode *t, enum PATHWAY p,
		   int (*function)(const TreeNode *, void *buffer), void *buffer) {
	if (t == NULL)
		return WALK_SUCCESS;
	switch (p) {
	case INFIXE:
		if (__walk(t->left, p, function, buffer))
			return WALK_FAILURE;
		if (function(t, buffer))
			return WALK_FAILURE;
		if (__walk(t->right, p, function, buffer))
			return WALK_FAILURE;
		break;
	case PREFIXE:
		if (function(t, buffer))
			return WALK_FAILURE;
		if (__walk(t->left, p, function, buffer))
			return WALK_FAILURE;
		if (__walk(t->right, p, function, buffer))
			return WALK_FAILURE;
		break;
	case POSTFIXE:
		if (__walk(t->left, p, function, buffer))
			return WALK_FAILURE;
		if (__walk(t->right, p, function, buffer))
			return WALK_FAILURE;
		if (function(t, buffer))
			return WALK_FAILURE;
		break;
	}
	return WALK_SUCCESS;
}

int walk(const Tree *t, enum PATHWAY p,
		 int (*function)(const TreeNode *, void *buffer), void *buffer) {
	return __walk(t->root, p, function, buffer);
}

int isLeaf(const TreeNode *t) {
	assert(t != NULL);
	return t->left == NULL && t->right == NULL;
}

typedef struct CheckInfo {
	void *last;
	int (*cmpFunc)(const void *value, const void *existing);
} CheckInfo;

int __isOrdered(const TreeNode *t, void *buffer) {
	CheckInfo *ci = (CheckInfo *)buffer;
	if (ci->last != NULL && ci->cmpFunc(t->value, ci->last) < 0) {
		return ISNOTBST;
	}
	ci->last = t->value;
	return ISBST;
}

int isOrdered(const Tree *t) {
	CheckInfo ci;
	ci.last = NULL;
	ci.cmpFunc = t->nodecmp;
	int badWalk = walk(t, INFIXE, __isOrdered, &ci);
	return badWalk ? ISNOTBST : ISBST;
}

typedef struct SortInfo {
	void **dest;
	int index;
	size_t size;
} SortInfo;

int __heapSort(const TreeNode *t, void *si) {
	if (t == NULL)
		return WALK_SUCCESS;
	SortInfo *csi = (SortInfo *)si;
	memcpy(csi->dest[csi->index], t->value, csi->size);
	csi->index++;
	return WALK_SUCCESS;
}

void **heapSort(void **src, int n, size_t size,
				int (*nodecmp)(const void *newValue, const void *existing)) {
	if (n <= 0)
		return NULL;

	Tree *t = newTree(size, nodecmp);
	for (int i = 0; i < n; i++)
		insertIntoTree(t, src[i]);

	SortInfo si;
	si.dest = malloc(n * sizeof(void *));
	for (int i = 0; i < n; i++)
		si.dest[i] = malloc(t->sizeofEach);
	si.index = 0;
	si.size = t->sizeofEach;
	int failed = walk(t, INFIXE, __heapSort, &si);
	void **ret = si.dest;
	if (failed) {
		free(ret);
		return NULL;
	}
	return ret;
}

void deleteFromTree(Tree *t, const void *oldValue) {
	TreeNode **pair = findNodeWithParent(t, oldValue);
	TreeNode *toRemove = pair[0], *parent = pair[1];
	if (toRemove == NULL)
		return;
	TreeNode *newSon = NULL;
	if (toRemove->left != NULL && toRemove->right != NULL) {
		TreeNode **spd = (TreeNode **)minNodeWithParent(toRemove->right);
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
		t->root = newSon;
	else {
		if (parent->left == NULL)
			parent->left = newSon;
		else
			parent->right = newSon;
	}
	free(toRemove);
}

void cutTree(TreeNode *toCut, TreeNode *from) {
	if (from->left == toCut)
		from->left = NULL;
	else if (from->right == toCut)
		from->right = NULL;
}

const TreeNode **minNodeWithParent(const TreeNode *t) {
	const TreeNode **spd = malloc(2 * sizeof(TreeNode *));
	spd[0] = t;
	spd[1] = NULL;
	while (t->left != NULL) {
		spd[0] = t->left;
		spd[1] = t;
		t = t->left;
	}
	return spd;
}
