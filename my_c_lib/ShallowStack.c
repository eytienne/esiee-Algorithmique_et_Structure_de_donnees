
#include "ShallowStack.h"
#include <assert.h>
#include <stdlib.h>

ShallowStack *newShallowStack() {
	ShallowStack *newOne = malloc(sizeof(ShallowStack));
	newOne->top = NULL;
	return newOne;
}

void freeShallowStack(ShallowStack *ss) {
	assert(ss != NULL);
	while (!isSSEmpty(ss))
		unsstack(ss);
	free(ss);
}

const void *top(ShallowStack *ss) {
	assert(ss != NULL);
	assert(!isSSEmpty(ss));
	return ss->top->value;
}

const void *unsstack(ShallowStack *ss) {
	const void *ret = top(ss);
	SSCell *toFree = ss->top;
	ss->top = ss->top->next;
	free(toFree);
	return ret;
}

void sstack(ShallowStack *ss, const void *v) {
	assert(ss != NULL);
	SSCell *newTop = malloc(sizeof(SSCell));
	newTop->value = v;
	newTop->next = ss->top;
	ss->top = newTop;
	assert(top(ss) == v);
}

int isSSEmpty(const ShallowStack *ss) {
	assert(ss != NULL);
	return ss->top == NULL;
}
