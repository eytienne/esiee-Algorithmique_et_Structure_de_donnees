
#ifndef SHALLOW_STACK_H
#define SHALLOW_STACK_H

typedef struct SSCell
{
	const void *value;
	struct SSCell *next;
} SSCell;

typedef struct ShallowStack {
	SSCell *top;
} ShallowStack;

ShallowStack *newShallowStack();

void freeShallowStack(ShallowStack *ss);

const void *top(ShallowStack *ss);

const void *unsstack(ShallowStack *ss);

void sstack(ShallowStack *ss, const void *v);

int isSSEmpty(const ShallowStack *ss);

#endif
