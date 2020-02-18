
#include "../../my_c_lib/BSTree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int intcmp(const void *c1, const void *c2) { return *(int *)c1 - *(int *)c2; }

void intprint(const void *v) { printf("%d", *(int *)v); }

int main(int argc, char const *argv[]) {


    if(2)
        printf("Start\n");

	BSTree *t = newTree(sizeof(int), intcmp);
	assert(t != NULL);
	assert(t->root == NULL);
	assert(t->sizeofEach = sizeof(int));
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
}