
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

void freeShallowStack(ShallowStack *p);

const void *top(ShallowStack *p);

const void *unsstack(ShallowStack *p);

void sstack(ShallowStack *p, const void *v);

int isSSEmpty(const ShallowStack *p);

#endif
