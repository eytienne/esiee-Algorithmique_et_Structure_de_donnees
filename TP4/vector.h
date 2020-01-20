#ifndef VECTOR_H
#define VECTOR_H
#include <stdlib.h>

struct Cell {
	void *value;
	size_t size;
};
typedef struct Cell Cell;

struct Vector {
	Cell *values;
	int size;
	int capacity;
	int increment;
};
typedef struct Vector Vector;

void create_expert(Vector *v, int capacity, int increment);

void create(Vector *v);

void destroy(Vector *v);

int size(const Vector *v);

int capacity(const Vector *v);

void *get(const Vector *v, int index);

Cell *getCell(const Vector *v, int index);

int add(Vector *v, void *const element, size_t size);

int insert(Vector *v, int index, void *const element, size_t size);

void set(Vector *v, int index, void *const element, size_t size);

void *removeFromVectorAtIndex(Vector *v, int index);

int delete (Vector *v, int start, int end);

int adjust(Vector *v);

#endif