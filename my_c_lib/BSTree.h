#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include <stddef.h>

typedef struct BSTree {
	TreeNode *root;
	size_t sizeofEach;
	int (*nodecmp)(const void *newValue, const void *existing);
} BSTree;

enum BST_CHECK { ISBST = WALK_SUCCESS, ISNOTBST = WALK_FAILURE };

BSTree *newTree(size_t sizeofEach,
			  int (*nodecmp)(const void *newValue, const void *existing));

void freeTree(BSTree *t, void (*freeValue)(void *value));

int countTreeNodes(const BSTree *t);

void printTree(const BSTree *t, void (*printer)(const void *value));

void printTree2(const BSTree *t, void (*printer)(const void *value));

void prefixPrintTree(const BSTree *t, void (*printer)(const void *value));

void insertIntoTree(BSTree *t, const void *newValue);

const TreeNode *findTreeNode(BSTree *t, const void *value);

int walk(const TreeNode *t, enum PATHWAY p,
		   int (*function)(const TreeNode *, void *buffer), void *buffer);

int walkTree(const BSTree *t, enum PATHWAY p,
		 int (*function)(const TreeNode *, void *buffer), void *buffer);

int transformTree(BSTree *t, enum PATHWAY p,
			  int (*function)(TreeNode *, void *buffer), void *buffer);

int isOrdered(const BSTree *t);

void **treeSort(void **src, int n, size_t size, int (*nodecmp)(const void *newValue, const void *existing));

void deleteFromTree(BSTree *t, const void *oldValue);

const TreeNode **minNodeWithParent(const TreeNode *t);

#endif