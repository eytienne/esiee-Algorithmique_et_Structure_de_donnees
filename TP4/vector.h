#ifndef VECTOR_H
#define VECTOR_H

struct Vector {
	int *values;
	int size;
	int capacity;
	int increment;
};

typedef struct Vector Vector;

void create_expert(Vector *v, int capacity, int increment);

void create(Vector *v);

void destroy(Vector *v);

int size(Vector v);

int capacity(Vector v);

int get(Vector v, int index);

void add(Vector *v, int element);

int insert(Vector *v, int index, int element);

void set(Vector *v, int index, int element);

int removeFromVectorAtIndex(Vector *v, int index);

int delete (Vector *v, int start, int end);

int adjust(Vector *v);

#endif