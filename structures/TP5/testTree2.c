
#include "../../my_c_lib/BSTree.h"
#include "../../my_c_lib/BinaryPath.h"
#include "../../my_c_lib/Vector.h"
#include <assert.h>
#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int intcmp(const void *c1, const void *c2) {
	return *(int *)c1 - *(int *)c2;
}

void intprint(const void *v) {
	printf("%d", *(int *)v);
}

int __pickLeaves(const TreeNode *t, void *buffer, const BinaryPath *bp) {
	assert(buffer != NULL);
	Vector *leaves = buffer;
	const int *value = t->value;
	printf("'%d' -> ", *value);
	printBinaryPath(bp);
	printf("\n");
	add(leaves, &value);
	return WALK_SUCCESS;
}

Vector *pickLeaves(TreeNode *root) {
	Vector *leaves = newVector(sizeof(int*));
	printf("LEAVES : %p\n", leaves);
	walkExpert(root, PREFIXE, __pickLeaves, leaves);
	printf("LEAVES (%d, %d): %p\n", size(leaves), capacity(leaves), leaves);
	return leaves;
}

void handler(int sig) {
	void *array[10];
	size_t size;

	// get void*'s for all entries on the stack
	size = backtrace(array, 10);

	// print out all the frames to stderr
	fprintf(stderr, "Error: signal %d:\n", sig);
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}

int main(int argc, char const *argv[]) {
	signal(SIGSEGV, handler);
	signal(SIGABRT, handler);

	BSTree *t = newTree(sizeof(int), intcmp);
	assert(t != NULL);
	assert(t->root == NULL);
	assert(t->sizeofEach == sizeof(int));
	assert(t->nodecmp == intcmp);

	int value = 5;
	insertIntoTree(t, &value);
	value = 3;
	insertIntoTree(t, &value);
	value = 1;
	insertIntoTree(t, &value);
	value = 4;
	insertIntoTree(t, &value);
	value = 8;
	insertIntoTree(t, &value);
	value = 7;
	insertIntoTree(t, &value);
	value = 10;
	insertIntoTree(t, &value);
	value = 12;
	insertIntoTree(t, &value);

	printTree(t, intprint);

	prefixPrintTree(t, intprint);

	Vector *ret = pickLeaves(t->root);
	freeVector(ret, NULL);
}