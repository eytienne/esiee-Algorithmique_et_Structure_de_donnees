#include "TreeNode.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

TreeNode *newTreeNode(const void *value, size_t size) {
	assert(value != NULL);
	assert(size > 0);
	TreeNode *newOne = (TreeNode *)malloc(sizeof(TreeNode));
	newOne->value = malloc(size);
	memcpy(newOne->value, value, size);
	newOne->left = newOne->right = NULL;
	return newOne;
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