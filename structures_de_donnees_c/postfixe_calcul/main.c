#include "lib/pile.h"
#include "lib/vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printVectorWithChars(Vector *v) {
	printf("Vector (size : %d, capacity : %d): \n", v->size, v->capacity);
	for (int i = 0; i < size(v); i++) {
		Cell *c = getCell(v, i);
		switch (c->size) {
		case 1:
			printf("%s\n", (char *)c->value);
			break;
		case 2:
			printf("%hd\n", *(short *)c->value);
			break;
		case 4:
			printf("%d\n", *(int *)c->value);
			break;
		case 8:
			printf("%ld\n", *(long *)c->value);
			break;
		default:
			fprintf(stderr, "Value cannot be printed!");
			break;
		}
	}
}

void *popV(Vector *v) { return removeFromVectorAtIndex(v, size(v) - 1); }

int isOperator(char *c) {
	return !strcmp(c, "+") || !strcmp(c, "-") || !strcmp(c, "*") ||
		   !strcmp(c, "/");
}

int isOperand(char *c) { return !isOperator(c); }

double getOperation(double op1, char *op, double op2) {
	if (!strcmp(op, "+"))
		return op1 + op2;
	if (!strcmp(op, "-"))
		return op1 - op2;
	if (!strcmp(op, "*"))
		return op1 * op2;
	if (!strcmp(op, "/"))
		return op1 / op2;
}

double calcul(Vector *v) {
	assert(*(char *)removeFromVectorAtIndex(v, size(v) - 1) == '#');
	double ret = 0;
	Pile *oPile = (*Pile)malloc(sizeof(Pile));

	empiler(oPile, (char *)popV(v));
	while (size(v) > 0) {
	}
}

int main(int argc, char const *argv[]) {
	Vector *v;
	create(v);
	char *c = "1";
	add(v, c, 1);
	c = "2";
	add(v, c, 1);
	c = "+";
	add(v, c, 1);
	c = "3";
	add(v, c, 1);
	c = "*";
	add(v, c, 1);
	c = "#";
	add(v, c, 1);
	printVectorWithChars(v);
	printf("Calcul : %lf", calcul(v));
	return 0;
}
