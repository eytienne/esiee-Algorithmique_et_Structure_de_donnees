#ifndef VECTOR_H
#define VECTOR_H

#include "cell.h"

struct Vector {
	void **values;
	size_t sizeofEach;
	int size;
	int capacity;
	int increment;
};
typedef struct Vector Vector;

void create_expert(Vector *v, int capacity, int increment, size_t sizeofEach);

void create(Vector *v, size_t sizeofEach);

void destroy(Vector *v);

int size(const Vector *v);

int capacity(const Vector *v);

void *get(const Vector *v, int index);

Cell *getCell(const Vector *v, int index);

int add(Vector *v, const void *element);

int insert(Vector *v, int index, const void *element);

void set(Vector *v, int index, const void *element);

void *removeFromVectorAtIndex(Vector *v, int index);

int delete (Vector *v, int start, int end);

int adjust(Vector *v);

#endif