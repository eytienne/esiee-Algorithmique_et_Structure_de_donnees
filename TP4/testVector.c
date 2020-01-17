#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void printVector(Vector v);

int main(int argc, char const *argv[]) {
	Vector v;
	create(&v);
	assert(v.values != NULL);
	assert(capacity(v) == 10);
	assert(size(v) == 0);
	assert(v.increment == 3);
	printVector(v);

	destroy(&v);
	assert(v.values == NULL);
	assert(capacity(v) == 0);
	assert(size(v) == 0);
	printVector(v);

	create_expert(&v, 5, 4);
	assert(v.values != NULL);
	assert(capacity(v) == 5);
	assert(size(v) == 0);
	assert(v.increment == 4);
	printVector(v);

	for (int i = 1; i <= 5; i++)
		add(&v, i);
	assert(get(v, size(v) - 1) == 5);
	assert(size(v) == 5);
	assert(capacity(v) == 5);
	printVector(v);

	delete (&v, size(v) - 3, size(v));
	assert(get(v, size(v) - 1) == 2);
	assert(size(v) == 2);
	assert(capacity(v) == 5);
	printVector(v);

	removeFromVectorAtIndex(&v, size(v) - 1);
	assert(get(v, size(v) - 1) == 1);
	assert(size(v) == 1);
	assert(capacity(v) == 1);
	printVector(v);

	add(&v, 11);
	add(&v, 11);
	add(&v, 11);
	assert(size(v) == 4);
	assert(capacity(v) == 5);
	printVector(v);
	adjust(&v);
	assert(size(v) == 4);
	assert(capacity(v) == 4);
	printVector(v);

	set(&v, 0, 10);
	assert(get(v, 0) == 10);
	printVector(v);

	return 0;
}

void printVector(Vector v) {
	printf("Vector (size : %d, capacity : %d): \n", v.size, v.capacity);
	for (int i = 0; i < size(v); i++)
		printf("%d\n", get(v, i));
}