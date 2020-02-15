#include "../../my_c_lib/HashTable.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

	HashTable *t = newHashTable(2, sizeof(int));
	assert(t != NULL);
	assert(t->capacity == 2);

	char *first = "first";
	char *second = "second";
	char *third = "third";

	int value = 1;
	put(t, first, &value);

	int j = 0;
	assert(get(t, first, &j));
	assert(j == 1);

	value = 2;
	put(t, second, &value);
	value = 3;
	put(t, third, &value);
	j = 0;
	assert(get(t, first, &j));
	assert(j == 1);
	j = 0;
	assert(get(t, second, &j));
	assert(j == 2);
	j = 0;
	assert(get(t, third, &j));
	assert(j == 3);

	removeFromHashTable(t, first);
	j = 0;
	assert(!get(t, first, &j));
	assert(j == 0);
	j = 0;
	assert(get(t, second, &j));
	assert(j == 2);
	j = 0;
	assert(get(t, third, &j));
	assert(j == 3);

	return 0;
}
