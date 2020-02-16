#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <stddef.h>

typedef struct TreeNode {
	void *value;
	struct TreeNode *left, *right;
} TreeNode;

enum PATHWAY { INFIXE, PREFIXE, POSTFIXE };

enum WALK_CHECK { WALK_SUCCESS, WALK_FAILURE };

TreeNode *newTreeNode(const void *value, size_t size);

int walk(const TreeNode *t, enum PATHWAY p,
		 int (*function)(const TreeNode *, void *buffer), void *buffer);

#endif