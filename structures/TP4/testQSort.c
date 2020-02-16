#include "../../my_c_lib/Vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void intprint(const int *values, size_t n) {
	for (size_t i = 0; i < n; i++) {
		printf("%d ", values[i]);
	}
	printf("\n");
}

void intprint2(const int **values, size_t n) {
	for (size_t i = 0; i < n; i++) {
		printf("%d ", *values[i]);
	}
	printf("\n");
}

void printIntV(const Vector *v) {
	for (size_t i = 0; i < size(v); i++) {
		printf("%d\t", *(int *)v->values[i]);
	}
	printf("\n");
}

int intcmp(const void *a, const void *b) {
	int va = *(const int *)a;
	int vb = *(const int *)b;
	return (va > vb) - (va < vb);
}

int intcmp2(const void *a, const void *b) {
	int *pa = *(const int **)a;
	int *pb = *(const int **)b;
	printf("'%p' '%p'\n", pa, pb);
	int va = *pa;
	int vb = *pb;
	return (va > vb) - (va < vb);
}

int main(int argc, char const *argv[]) {
	Vector *v = malloc(sizeof(Vector));
	create(v, sizeof(int));
	int value = 10;
	add(v, &value);
	value = -3;
	add(v, &value);
	value = 2;
	add(v, &value);
	value = 1;
	add(v, &value);
	printIntV(v);
	printf("try : %d\n", *(int *)v->values[0]);
	qsort(v->values, 4, sizeof(void *), intcmp2);
	printIntV(v);

	int pointed[4] = {10, -3, 2, 1};
	int *values[4];
	for (int i = 0; i < 4; i++) {
		values[i] = pointed + i;
	}
	intprint2(values, 4);
	qsort(values, 4, sizeof(int *), intcmp2);
	intprint2(values, 4);
	return 0;
}
