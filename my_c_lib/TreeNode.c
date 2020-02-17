#include "TreeNode.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TreeNode *newTreeNode(const void *value, size_t size, TreeNode *left,
					  TreeNode *right) {
	assert(value != NULL);
	assert(size > 0);
	TreeNode *newOne = (TreeNode *)malloc(sizeof(TreeNode));
	newOne->value = malloc(size);
	memcpy(newOne->value, value, size);
	newOne->left = left;
	newOne->right = right;
	return newOne;
}

int isLeaf(const TreeNode *t) {
	assert(t != NULL);
	return t->left == NULL && t->right == NULL;
}

int walk(const TreeNode *t, enum PATHWAY p,
		 int (*function)(const TreeNode *, void *buffer), void *buffer) {
	if (t == NULL)
		return WALK_SUCCESS;
	switch (p) {
	case INFIXE:
		if (walk(t->left, p, function, buffer))
			return WALK_FAILURE;
		if (function(t, buffer))
			return WALK_FAILURE;
		if (walk(t->right, p, function, buffer))
			return WALK_FAILURE;
		break;
	case PREFIXE:
		if (function(t, buffer))
			return WALK_FAILURE;
		if (walk(t->left, p, function, buffer))
			return WALK_FAILURE;
		if (walk(t->right, p, function, buffer))
			return WALK_FAILURE;
		break;
	case POSTFIXE:
		if (walk(t->left, p, function, buffer))
			return WALK_FAILURE;
		if (walk(t->right, p, function, buffer))
			return WALK_FAILURE;
		if (function(t, buffer))
			return WALK_FAILURE;
		break;
	default:
		return WALK_FAILURE;
	}
	return WALK_SUCCESS;
}

int countTreeNodeNodes(const TreeNode *t, void *counter) {
	++*(int *)counter;
	return WALK_SUCCESS;
}

int printTreeNode(const TreeNode *t, void *pi) {
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

void printTreeNode2(const TreeNode *t, void (*printer)(const void *value)) {
	if (t == NULL) {
		printf("_");
		return;
	}
	printf("{");
	printTreeNode2(t->left, printer);
	printf(", ");
	printer(t->value);
	printf(", ");
	printTreeNode2(t->right, printer);
	printf("}");
}

int prefixPrint(const TreeNode *t, void *buffer) {
	prefixePrintInfo *ppi = (prefixePrintInfo *)buffer;
	ppi->nbTabs += 1;

	for (int i = 0; i < ppi->nbTabs; i++)
		printf("\t");
	printf("\\---");
	ppi->printer(t->value);
	printf("\n");
	
	if (isLeaf(t))
		ppi->nbTabs -= 1;
	
	// printf("ppi->nbTabs : %d", ppi->nbTabs);
	return WALK_SUCCESS;
}