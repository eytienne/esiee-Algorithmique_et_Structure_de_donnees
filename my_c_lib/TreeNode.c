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

int isParent(const TreeNode *from, const TreeNode *it) {
	return from == it->left || from == it->right;
}

typedef struct WalkWithPathInfo {
	BinaryPath *bp;
	ShallowStack *parents;
	int (*function)(const TreeNode *, void *buffer, const BinaryPath *bp);
	void *buffer;
} WalkWithPathInfo;

int __walkWithPath(const TreeNode *tn, void *buffer) {

	assert(buffer != NULL);
	WalkWithPathInfo *wwpi = (WalkWithPathInfo *)buffer;

	const TreeNode *last =
		!isSSEmpty(wwpi->parents) ? top(wwpi->parents) : NULL;
	if (last)
		printf("last %d\n", *(int *)last->value);

	while (!isSSEmpty(wwpi->parents) && !isParent(tn, last)) {
		unsstack(wwpi->parents);
		goBack(wwpi->bp);
		last = !isSSEmpty(wwpi->parents) ? top(wwpi->parents) : NULL;
	}
	// printf("step2\n");
	if (last != NULL) {
		if (last->left == tn) {
			goToLeft(wwpi->bp);
		} else if (last->right == tn) {
			goToRight(wwpi->bp);
		}
	}

	if (wwpi->function(tn, wwpi->buffer, wwpi->bp))
		return WALK_FAILURE;

	sstack(wwpi->parents, tn);

	return WALK_SUCCESS;
}

int walkWithPath(const TreeNode *root, enum PATHWAY p,
				 int (*function)(const TreeNode *, void *buffer,
								 const BinaryPath *bp),
				 void *buffer) {
	BinaryPath *bp = newBinaryPath();
	WalkWithPathInfo wwpi = {bp, newShallowStack(), function, buffer};
	return walk(root, p, __walkWithPath, &wwpi);
}

int postfixWalk_rec(const TreeNode *tn,
					int (*function)(const TreeNode *, void *buffer),
					void *buffer) {
	if (tn == NULL)
		return WALK_SUCCESS;
	if (postfixWalk_rec(tn->left, function, buffer))
		return WALK_FAILURE;
	if (postfixWalk_rec(tn->right, function, buffer))
		return WALK_FAILURE;
	if (function(tn, buffer))
		return WALK_FAILURE;
	return WALK_SUCCESS;
}

int walk(const TreeNode *root, enum PATHWAY p,
		 int (*function)(const TreeNode *, void *buffer), void *buffer) {

	ShallowStack *toVisit = newShallowStack();
	sstack(toVisit, root);
	ShallowStack *toProcess = newShallowStack();
	ShallowStack *toProcessOnRight = newShallowStack();

	while (!isSSEmpty(toVisit)) {
		const TreeNode *cur = unsstack(toVisit);
		if (cur == NULL)
			continue;
		switch (p) {
		case PREFIXE:
			if (function(cur, buffer))
				return WALK_FAILURE;
			sstack(toVisit, cur->right);
			sstack(toVisit, cur->left);
			break;
		case INFIXE:
			// left angle
			if (cur->left == NULL) {
				if (function(cur, buffer))
					return WALK_FAILURE;

				if (cur->right != NULL) {
					sstack(toVisit, cur->right);
				} else {
					const TreeNode *previousRight = NULL;
					// loop to come back while not finding right to visit
					while (previousRight == NULL && !isSSEmpty(toProcess)) {
						const TreeNode *previous = unsstack(toProcess);
						if (function(previous, buffer))
							return WALK_FAILURE;
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
			// left angle
			// if (isLeaf(cur)) {
			// 	if (function(cur, buffer))
			// 		return WALK_FAILURE;

			// 	if (cur->right != NULL) {
			// 		sstack(toVisit, cur->right);
			// 	} else {
			// 		if (!isSSEmpty(toProcess)) {
			// 			const TreeNode *previous = top(toProcess);
			// 			// loop to come back while not finding right to visit
			// 			while (previous == NULL && !isSSEmpty(toProcess)) {
			// 				const TreeNode *previous = unsstack(toProcess);
			// 				if (function(previous, buffer))
			// 					return WALK_FAILURE;
			// 				if (previous->right != NULL)
			// 					previousRight = previous->right;
			// 			}
			// 			sstack(toVisit, previousRight);
			// 		}
			// 	}
			// } else {
			// 	sstack(toProcess, cur);
			// 	sstack(toVisit, cur->right);
			// 	sstack(toVisit, cur->left);
			// }
			return postfixWalk_rec(cur, function, buffer);
			// break;
		default:
			return WALK_FAILURE;
		}
	}
	return WALK_SUCCESS;
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

	for (int i = 0; i < bp->length; i++)
		printf("\t");
	printf("\\---");
	printer(t->value);
	printf("\n");

	return WALK_SUCCESS;
}