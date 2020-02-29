#include "TreeNode.h"
#include "BinaryPath.h"
#include "ShallowStack.h"
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

int isParent(const TreeNode *son, const TreeNode *it) {
	assert(it);
	return son == it->left || son == it->right;
}

int postfixWalk_rec(const TreeNode *tn,
					int (*function)(const TreeNode *, void *buffer,
									const BinaryPath *bp),
					void *buffer) {
	if (tn == NULL)
		return WALK_SUCCESS;
	if (postfixWalk_rec(tn->left, function, buffer))
		return WALK_FAILURE;
	if (postfixWalk_rec(tn->right, function, buffer))
		return WALK_FAILURE;
	if (function(tn, buffer, NULL))
		return WALK_FAILURE;
	return WALK_SUCCESS;
}

int walkExpert(const TreeNode *root, enum PATHWAY p,
			   int (*function)(const TreeNode *, void *buffer,
							   const BinaryPath *bp),
			   void *buffer) {
	int walkResult = WALK_SUCCESS;
	BinaryPath *bp = newBinaryPath();
	ShallowStack *parents = newShallowStack();
	sstack(parents, root);

	ShallowStack *toVisit = newShallowStack();
	sstack(toVisit, root);

	ShallowStack *toProcess = newShallowStack();
	ShallowStack *TPR = newShallowStack();

	while (!isSSEmpty(toVisit) && walkResult == WALK_SUCCESS) {
		const TreeNode *cur = unsstack(toVisit);
		if (cur == NULL)
			continue;
		while (!isSSEmpty(parents) &&
			   !isParent(cur, (const TreeNode *)top(parents))) {
			unsstack(parents);
			if (!isSSEmpty(parents))
				goBack(bp);
		}
		if (!isSSEmpty(parents)) {
			const TreeNode *father = top(parents);
			if (father->left == cur) {
				goToLeft(bp);
			} else if (father->right == cur) {
				goToRight(bp);
			}
		}
		switch (p) {
		case PREFIXE:
			walkResult = function(cur, buffer, bp);
			sstack(toVisit, cur->right);
			sstack(toVisit, cur->left);
			break;
		case INFIXE:
			// left angle
			if (cur->left == NULL) {
				walkResult = function(cur, buffer, bp);
				if (cur->right != NULL) {
					sstack(toVisit, cur->right);
				} else {
					const TreeNode *previousRight = NULL;
					// loop to come back while not finding right to visit
					while (previousRight == NULL && !isSSEmpty(toProcess)) {
						const TreeNode *previous = unsstack(toProcess);
						walkResult = function(previous, buffer, bp);
						if (previous->right != NULL)
							previousRight = previous->right;
					}
					sstack(toVisit, previousRight);
				}
			} else {
				sstack(toProcess, cur);
				sstack(toVisit, cur->left);
			}
			break;
		case POSTFIXE:
			walkResult = postfixWalk_rec(cur, function, buffer);
			break;
		default:
			walkResult = WALK_FAILURE;
		}
		sstack(parents, cur);
	}
	freeShallowStack(toVisit);
	freeShallowStack(toProcess);
	freeShallowStack(TPR);
	freeBinaryPath(bp);
	return walkResult;
}

typedef struct __walkApplyInfo {
	int (*function)(const TreeNode *, void *buffer);
	void *buffer;
} __walkApplyInfo;

int __walkApply(const TreeNode *tn, void *buffer, const BinaryPath *bp) {
	__walkApplyInfo *wai = buffer;
	return wai->function(tn, wai->buffer);
}

int walk(const TreeNode *root, enum PATHWAY p,
		 int (*function)(const TreeNode *, void *buffer), void *buffer) {
	__walkApplyInfo wai = {function, buffer};
	return walkExpert(root, p, __walkApply, &wai);
}

int transformExpert(TreeNode *root, enum PATHWAY p,
					int (*function)(TreeNode *, void *buffer,
									const BinaryPath *bp),
					void *buffer) {
	return walk(root, p, (int (*)(const TreeNode *, void *))function, buffer);
}

int transform(TreeNode *root, enum PATHWAY p,
			  int (*function)(TreeNode *, void *buffer), void *buffer) {
	__walkApplyInfo wai = {(int (*)(const TreeNode *, void *))function, buffer};
	return transformExpert(
		root, p, (int (*)(TreeNode *, void *, const BinaryPath *))__walkApply,
		&wai);
}

int countTreeNodeNodes(const TreeNode *t, void *counter) {
	++*(int *)counter;
	return WALK_SUCCESS;
}

int printTreeNode(const TreeNode *t, void *buffer) {
	if (t == NULL)
		return WALK_SUCCESS;
	PrintInfo *pi = (PrintInfo *)buffer;
	if (!pi->first)
		printf("\t");
	pi->printer(t->value);
	if (pi->first)
		pi->first = 0;
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

int prefixPrint(const TreeNode *t, void *buffer, const BinaryPath *bp) {
	assert(buffer != NULL);
	void (*printer)(const void *) = (void (*)(const void *))buffer;

	for (int i = 1; i < bp->length; i++)
		printf("\t");
	if (bp->length > 0)
		printf("\\--%d--", getBPStep(bp, bp->length - 1));
	printer(t->value);
	printf("\n");

	return WALK_SUCCESS;
}