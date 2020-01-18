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
	int __size__;
	int __capacity__;
	int __increment__;
	
	void (*destroy)(struct Vector *);
	int (*size)(const struct Vector *);
	int (*capacity)(const struct Vector *);
	void *(*get)(const struct Vector *, int);
	Cell (*getCell)(const struct Vector *, int);
	int (*add)(struct Vector *, void *, size_t);
	int (*insert)(struct Vector *, int, void *, size_t);
	void (*set)(struct Vector *, int, void *, size_t);
	void *(*remove)(struct Vector *, int);
	int (*delete)(struct Vector *, int, int);
	int (*adjust)(struct Vector *);
};
typedef struct Vector Vector;

Vector *create_expert(int capacity, int __increment__);

Vector *create();

#endif