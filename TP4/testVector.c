#include "vector.h"
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

int main(int argc, char const *argv[]) { return test(); }

int test() {
	Vector *v = create();
	assert(v->values != NULL);
	assert(v->capacity(v) == 10);
	assert(v->size(v) == 0);
	assert(v->__increment__ == 3);
	printVector(v);

	v->destroy(v);
	assert(v->values == NULL);
	assert(v->capacity(v) == 0);
	assert(v->size(v) == 0);
	printVector(v);

	free(v);

	v = create_expert(5, 4);
	assert(v->values != NULL);
	assert(v->capacity(v) == 5);
	assert(v->size(v) == 0);
	assert(v->__increment__ == 4);
	printVector(v);

	for (int i = 1; i <= 5; i++)
		v->add(v, &i, sizeof(i));
	printVector(v);
	assert(*(int *)v->get(v, v->size(v) - 1) == 5);
	assert(v->size(v) == 5);
	assert(v->capacity(v) == 5);

	v->delete (v, v->size(v) - 3, v->size(v));
	assert(*(int *)v->get(v, v->size(v) - 1) == 2);
	assert(v->size(v) == 2);
	assert(v->capacity(v) == 5);
	printVector(v);

	v->remove(v, v->size(v) - 1);
	assert(*(int *)v->get(v, v->size(v) - 1) == 1);
	assert(v->size(v) == 1);
	assert(v->capacity(v) == 1);
	printVector(v);

	int a = 11;
	int b = 11;
	int c = 11;
	v->add(v, &a, sizeof(a));
	v->add(v, &b, sizeof(b));
	v->add(v, &c, sizeof(c));
	assert(v->size(v) == 4);
	assert(v->capacity(v) == 5);
	printVector(v);
	v->adjust(v);
	assert(v->size(v) == 4);
	assert(v->capacity(v) == 4);
	printVector(v);

	a = 10;
	v->set(v, 0, &a, sizeof(a));
	assert(*(int *)v->get(v, 0) == 10);
	printVector(v);

	printf("\n" GREEN_BG CUSTOM_FG "All the tests passed !" COLOR_RESET "\n");
	return 0;
}

int demo() {
	Vector *v = create(&v);
	int i = 35;
	v->add(v, &i, sizeof(int));
	char *cc = "c";
	v->add(v, cc, sizeof(char));
	printVectorWithChars(v);
	char *cc2 = "wesh";
	v->set(v, 1, cc2, sizeof(char));
	printVectorWithChars(v);
	return 0;
}

void printVector(Vector *v) {
	printf("Vector (size : %d, capacity : %d): \n", v->size(v), v->capacity(v));
	for (int i = 0; i < v->size(v); i++)
		printf("%d\n", *(int *)v->get(v, i));
}

void printVectorWithChars(Vector *v) {
	printf("Vector (size : %d, capacity : %d): \n", v->size(v), v->capacity(v));
	for (int i = 0; i < v->size(v); i++) {
		Cell c = v->getCell(v, i);
		switch (c.size) {
		case 1:
			printf("%s\n", (char *)c.value);
			break;
		case 2:
			printf("%hd\n", *(short *)c.value);
			break;
		case 4:
			printf("%d\n", *(int *)c.value);
			break;
		case 8:
			printf("%ld\n", *(long *)c.value);
			break;
		default:
			fprintf(stderr, "Value cannot be printed!");
			break;
		}
	}
}