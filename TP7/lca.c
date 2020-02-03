#include "lca.h"
#include "sda.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

LCA *new () {
	LCA *newOne = (LCA *)malloc(sizeof(LCA));
	if (newOne == NULL) {
		fputs("Malloc failed!\n", stderr);
		exit(1);
	}
	newOne->first = NULL;
	return newOne;
}

int isEmpty(const LCA *lca) {
	assert(lca != NULL);
	return lca->first == NULL;
}

int put(LCA *lca, Key k, Value v) {
	assert(lca != NULL);

	LCACell *cell = (LCACell *)malloc(sizeof(LCACell));
	cell->key = malloc(sizeof(Key));
	keycpy(cell->key, k);
	cell->value = malloc(sizeof(Value));
	valcpy(cell->value, v);
	cell->next = lca->first;
	lca->first = cell;
}

const __SDA__ SDAFunc = {new, isEmpty, put};
