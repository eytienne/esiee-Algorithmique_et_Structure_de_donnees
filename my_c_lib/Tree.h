#ifndef TREE_H
#define TREE_H

#include "Cell.h"

typedef struct TreeNode {
	void *value;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode;

typedef struct Tree {
	TreeNode *root;
	size_t sizeofEach;
	int (*nodecmp)(const void *newValue, const void *existing);
} Tree;

enum PATHWAY { INFIXE, PREFIXE, POSTFIXE };

enum WALK_CHECK { WALK_SUCCESS, WALK_FAILURE };

enum BST_CHECK { ISBST = WALK_SUCCESS, ISNOTBST = WALK_FAILURE };

Tree *newTree(size_t sizeofEach,
			  int (*nodecmp)(const void *newValue, const void *existing));

void freeTree(Tree *t, void (*freeValue)(void *value));

int countTreeNodes(const Tree *t);

void printTree(const Tree *t, void (*printer)(const void *value));

void printTree2(const Tree *t, void (*printer)(const void *value));

void insertIntoTree(Tree *t, const void *newValue);

const TreeNode *findTreeNode(Tree *t, const void *value);

int walk(const Tree *t, enum PATHWAY p,
		 int (*function)(const TreeNode *, void *buffer), void *buffer);

int transform(Tree *t, enum PATHWAY p,
			  int (*function)(TreeNode *, void *buffer), void *buffer);

int isLeaf(const TreeNode *t);

int isOrdered(const Tree *t);

void **heapSort(void **src, int n, size_t size, int (*nodecmp)(const void *newValue, const void *existing));

void deleteFromTree(Tree *t, const void *oldValue);

#endif