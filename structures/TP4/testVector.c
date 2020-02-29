#include "../../my_c_lib/Vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define GREEN_BG "\x1b[42m"
#define CUSTOM_FG "\x1b[97m"
#define COLOR_RESET "\x1b[0m"

int test();
int demo();

void printVector(Vector *v);
void printVectorWithChars(Vector *v);

int main(int argc, char const *argv[]) {
	return test();
	// return demo();
}

int test() {
	Vector *v = newVector(sizeof(int));
	printVector(v);
	assert(v->values != NULL);
	assert(capacity(v) == 10);
	assert(size(v) == 0);
	assert(v->increment == 3);

	freeVector(v, NULL);
	v = NULL;

	v = newVectorExpert(5, 4, sizeof(int));
	printVector(v);
	assert(v->values != NULL);
	assert(capacity(v) == 5);
	assert(size(v) == 0);
	assert(v->increment == 4);

	for (int i = 1; i <= 5; i++)
		add(v, &i);

	printVector(v);
	assert(*(int *)get(v, size(v) - 1) == 5);
	assert(size(v) == 5);
	assert(capacity(v) == 5);

	delete (v, 0, 3);
	printVector(v);
	assert(size(v) == 2);
	assert(capacity(v) == 5);

	int removed = *(int *)removeFromVectorAtIndex(v, size(v) - 1);
	printVector(v);
	assert(*(int *)get(v, size(v) - 1) == 4);
	assert(removed == 5);
	assert(size(v) == 1);
	assert(capacity(v) == 1);

	int a = 11;
	add(v, &a);
	add(v, &a);
	add(v, &a);
	printVector(v);
	assert(size(v) == 4);
	assert(capacity(v) == 5);

	adjust(v);
	printVector(v);
	assert(size(v) == 4);
	assert(capacity(v) == 4);

	a = 10;
	set(v, 0, &a);
	printVector(v);

	assert(*(int *)get(v, 0) == 10);

	int *getRef = (int *)get(v, 0);
	assert(*getRef == 10);
	*getRef = 7;
	printVector(v);
	getRef = (int *)get(v, 0);
	assert(*getRef == 10);

	freeVector(v, NULL);
	v = NULL;

	printf("\n" GREEN_BG CUSTOM_FG "All the tests passed !" COLOR_RESET "\n");
	return 0;
}

int demo() {
	Vector *v = newVector(sizeof(char *));

	char *cc = "c";
	add(v, cc);
	printVectorWithChars(v);

	char *cc2 = "wesh";
	add(v, cc2);
	printVectorWithChars(v);

	free(v);
	v = NULL;

	return 0;
}

void printVector(Vector *v) {
	printf("Vector (size : %d, capacity : %d): \n", size(v), capacity(v));
	int *cur = NULL;
	while (forEach(v, (const void **)&cur))
		printf("%d\n", *cur);
}

void printVectorWithChars(Vector *v) {
	printf("Vector (size : %d, capacity : %d): \n", size(v), capacity(v));
	char *cur = NULL;
	while (forEach(v, (const void **)&cur))
		printf("%s\n", cur);
}