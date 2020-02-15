#include "../../my_c_lib/Tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int intcmp(const void *c1, const void *c2) { return *(int *)c1 - *(int *)c2; }

void intprint(const void *v) { printf("%d", *(int *)v); }

int main(int argc, char const *argv[]) {

	Tree *t = newTree(sizeof(int), intcmp);
	assert(t != NULL);
	assert(t->root == NULL);
	assert(t->sizeofEach = sizeof(int));
	assert(t->nodecmp == intcmp);

	int value = 4;
	insertIntoTree(t, &value);
	value = 3;
	insertIntoTree(t, &value);
	value = 1;
	insertIntoTree(t, &value);
	value = 6;
	insertIntoTree(t, &value);
	insertIntoTree(t, &value);
	value = 9;
	insertIntoTree(t, &value);
	value = 7;
	insertIntoTree(t, &value);

	int nb = countTreeNodes(t);
	printf("Nb noeuds : %d\n", nb);
	assert(nb == 7);
	printTree(t, intprint);
	printTree2(t, intprint);

	value = 6;
	assert(findTreeNode(t, &value) != NULL);
	value = 8;
	assert(findTreeNode(t, &value) == NULL);

	int newRoot = 0;
	t->root->value = &newRoot;
	int badWalk = isOrdered(t);
	assert(badWalk);

	newRoot = 4;
	t->root->value = &newRoot;
	badWalk = isOrdered(t);
	assert(!badWalk);

	int **sortThis = malloc(5 * sizeof(int *));
	for (int i = 0; i < 5; i++)
		sortThis[i] = malloc(sizeof(int));
	*sortThis[0] = 10;
	*sortThis[1] = -1;
	*sortThis[2] = 4;
	*sortThis[3] = 8;
	*sortThis[4] = 2;
	int **sorted = (int **)heapSort((void **)sortThis, 5, sizeof(int), intcmp);
	for (size_t i = 0; i < 5; i++) {
		if (i > 0)
			printf(", ");
		printf("%d", *sorted[i]);
	}
	printf("\n");

	value = 4;
	deleteFromTree(t, &value);
	value = 6;
	assert(intcmp(t->root->value, &value) == 0);
	printTree2(t, intprint);
	nb = countTreeNodes(t);
	printf("Nb noeuds : %d\n", nb);
	assert(nb == 6);

	prefixPrint(t, intprint);

	freeTree(t, NULL);

	return 0;
}
