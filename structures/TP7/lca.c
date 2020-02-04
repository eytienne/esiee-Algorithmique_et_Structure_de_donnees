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

int containsKey(const LCA *lca, Key k) {
	assert(lca != NULL);
	LCACell *current = lca->first;
	while (current != NULL) {
		if (keycmp(current->key, k) == 0)
			return 1;
		current = current->next;
	}
	return 0;
}

Value get(const LCA *lca, Key k) {
	assert(lca != NULL);
	LCACell *current = lca->first;
	while (current != NULL) {
		if (keycmp(current->key, k) == 0) {
			Value ret = malloc(sizeof(Value));
			return valcpy(ret, current->value);
		}
		current = current->next;
	}
	return NULL;
}

void clear(LCA *lca) {
	assert(lca != NULL);
	LCACell *current = lca->first;
	while (current != NULL) {
		LCACell *next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	lca->first = NULL;
}

const __SDA__ SDAFunc = {new, isEmpty, put, containsKey, get, clear};
