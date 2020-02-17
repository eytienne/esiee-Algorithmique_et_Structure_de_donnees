#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <stddef.h>

typedef struct TreeNode {
	void *value;
	struct TreeNode *left, *right;
} TreeNode;

enum PATHWAY { INFIXE, PREFIXE, POSTFIXE };

enum WALK_CHECK { WALK_SUCCESS, WALK_FAILURE };

TreeNode *newTreeNode(const void *value, size_t size, TreeNode *left,
					  TreeNode *right);

int isLeaf(const TreeNode *t);

int walk(const TreeNode *t, enum PATHWAY p,
		 int (*function)(const TreeNode *, void *buffer), void *buffer);

int countTreeNodeNodes(const TreeNode *t, void *counter);

typedef struct PrintInfo {
	void (*printer)(const void *value);
	int first;
} PrintInfo;

int printTreeNode(const TreeNode *t, void *pi);

void printTreeNode2(const TreeNode *t, void (*printer)(const void *value));

typedef struct prefixePrintInfo {
	int nbTabs;
	void (*printer)(const void *value);
} prefixePrintInfo;

int prefixPrint(const TreeNode *t, void *buffer);

#endif