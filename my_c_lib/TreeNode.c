#include "TreeNode.h"
#include "BinarySequence.h"
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

int __freeTree(TreeNode *tn, void *buffer) {
	void (*freeValue)(void *value) = (void (*)(void *))buffer;
	if (freeValue != NULL)
		freeValue(tn->value);
	else
		free(tn->value);
	free(tn);
	return WALK_SUCCESS;
}

void freeTreeNode(TreeNode *tn, void (*freeValue)(void *value)) {
	transform(tn, POSTFIXE, __freeTree, freeValue);
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
									const BinarySequence *bs),
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
							   const BinarySequence *bs),
			   void *buffer) {
	int walkResult = WALK_SUCCESS;
	BinarySequence *bs = newBinarySequence();
	ShallowStack *parents = newShallowStack();

	ShallowStack *toVisit = newShallowStack();
	sstack(toVisit, root);

	ShallowStack *toProcess =
		newShallowStack(); // marked: visited but not processed
	ShallowStack *TPR = newShallowStack();

	while (!isSSEmpty(toVisit) && walkResult != WALK_FAILURE) {
		const TreeNode *cur = unsstack(toVisit);
		if (cur == NULL)
			continue;
		switch (p) {
		case PREFIXE: {
			while (!isSSEmpty(parents) && !isParent(cur, top(parents))) {
				unsstack(parents);
				if (!isSSEmpty(parents))
					shorten(bs);
			}
			if (!isSSEmpty(parents)) {
				const TreeNode *father = top(parents);
				if (father->left == cur) {
					addZero(bs);
				} else if (father->right == cur) {
					addOne(bs);
				}
			}
		}
			walkResult = function(cur, buffer, bs);
			sstack(parents, cur);
			sstack(toVisit, cur->right);
			sstack(toVisit, cur->left);
			break;
		case INFIXE:
			// left angle
			if (cur->left == NULL) {
				walkResult = function(cur, buffer, bs);

				// loop to come back while not finding right to visit
				while (cur->right == NULL && !isSSEmpty(toProcess)) {
					cur = unsstack(toProcess);
					while (!isSSEmpty(parents) &&
						   !isParent(cur, top(parents))) {
						unsstack(parents);
						shorten(bs);
					}
					walkResult = function(cur, buffer, bs);
				}
				if (cur->right != NULL) {
					sstack(parents, cur);
					addOne(bs);
					sstack(toVisit, cur->right);
				}
			} else {
				sstack(toProcess, cur);
				sstack(parents, cur);
				addZero(bs);
				sstack(toVisit, cur->left);
			}
			break;
		case POSTFIXE:
			walkResult = postfixWalk_rec(cur, function, buffer);
			break;
		default:
			walkResult = WALK_FAILURE;
		}
	}
	freeShallowStack(parents);
	freeShallowStack(toVisit);
	freeShallowStack(toProcess);
	freeShallowStack(TPR);
	freeBinarySequence(bs);
	return walkResult;
}

typedef struct __walkApplyInfo {
	int (*function)(const TreeNode *, void *buffer);
	void *buffer;
} __walkApplyInfo;

int __walkApply(const TreeNode *tn, void *buffer, const BinarySequence *bs) {
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
									const BinarySequence *bs),
					void *buffer) {
	return walk(root, p, (int (*)(const TreeNode *, void *))function, buffer);
}

int transform(TreeNode *root, enum PATHWAY p,
			  int (*function)(TreeNode *, void *buffer), void *buffer) {
	__walkApplyInfo wai = {(int (*)(const TreeNode *, void *))function, buffer};
	return transformExpert(
		root, p,
		(int (*)(TreeNode *, void *, const BinarySequence *))__walkApply, &wai);
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

int prefixPrint(const TreeNode *t, void *buffer, const BinarySequence *bs) {
	assert(buffer != NULL);
	void (*printer)(const void *) = (void (*)(const void *))buffer;

	for (int i = 1; i < bs->length; i++)
		printf("\t");
	if (bs->length > 0)
		printf("\\--%d--", getBit(bs, bs->length - 1));
	printer(t->value);
	printf("\n");

	return WALK_SUCCESS;
}