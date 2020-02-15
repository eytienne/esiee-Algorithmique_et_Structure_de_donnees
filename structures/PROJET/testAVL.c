#include "../../my_c_lib/Tree.h"
#include <stdlib.h>
#include <stdio.h>

int intcmp(const void *c1, const void *c2) { return *(int *)c1 - *(int *)c2; }

void intprint(const void *v) { printf("%d", *(int *)v); }

int main(int argc, char const *argv[]) {

    Tree* t = newTree(sizeof(int), intcmp);
	for (int i = 0; i < 10; i++)
        insertIntoTree(t, &i);
    
    prefixPrint(t, intprint);

	return 0;
}
