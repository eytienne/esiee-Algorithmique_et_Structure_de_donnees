#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int swap(void *const a, void *const b, size_t size);

struct Cell {
	void *value;
	size_t size;
};
typedef struct Cell Cell;

Cell *getCell(void *const value, size_t size);

int main(int argc, char const *argv[]) {
	int a = 3;
	Cell *c = getCell(&a, sizeof(a));
	printf("%d\n", *(int *)c->value);
	a = 5;
	printf("%d\n", *(int *)c->value);
	return 0;
}

Cell *getCell(void *const value, size_t size) {
	Cell *c = (Cell *)malloc(sizeof(Cell));
	void *temp = malloc(size);
	memcpy(temp, value, size);
	c->value = temp;
	c->size = size;
	return c;
}

void test_swap() {
	int a = 2, b = 3;
	swap(&a, &b, sizeof(a));
	printf("a : %d, b : %d\n", a, b);
}

int swap(void *const a, void *const b, size_t size) {
	void *const temp = malloc(size);

	if (temp == NULL)
		return EXIT_FAILURE;

	memcpy(temp, a, size);
	memcpy(a, b, size);
	memcpy(b, temp, size);

	free(temp);

	return EXIT_SUCCESS;
}