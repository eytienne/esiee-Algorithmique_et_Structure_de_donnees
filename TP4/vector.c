#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void create_expert(Vector *v, int capacity, int increment) {
	assert(v != NULL);
	v->capacity = capacity;
	v->values = (int *)malloc(v->capacity * sizeof(int));
	v->size = 0;
	v->increment = increment;
}

void create(Vector *v) { create_expert(v, 10, 3); }

void destroy(Vector *v) {
	assert(v != NULL);
	free(v->values);
	v->values = NULL;
	v->capacity = 0;
	v->size = 0;
}

int size(Vector v) { return v.size; }

int capacity(Vector v) { return v.capacity; }

int get(Vector v, int index) {
	assert(index >= 0 && index < v.size);
	return v.values[index];
}

void add(Vector *v, int element) {
	assert(v != NULL);
	insert(v, size(*v), element);
}

int insert(Vector *v, int index, int element) {
	assert(v != NULL);
	assert(index >= 0);
	if (v->size + 1 > v->capacity) {
		int newCapacity = v->capacity + v->increment;
		int *newValues = (int *)realloc(v->values, newCapacity * sizeof(int));
		if (newValues == NULL)
			return -1;
		v->values = newValues;
		v->capacity = newCapacity;
	}
	if (index < v->size) {
		set(v, v->size - 1, get(*v, v->size));
		for (int i = v->size - 2; i >= 0 && i >= index; i--)
			v->values[i + 1] = v->values[i];
	}
	v->values[index] = element;
	v->size++;
	return 0;
}

void set(Vector *v, int index, int element) {
	assert(v != NULL);
	assert(index >= 0 && index < v->size);
	v->values[index] = element;
}

int removeFromVectorAtIndex(Vector *v, int index) {
	assert(v != NULL);
	assert(index >= 0 && index < v->size);
	int removed = v->values[index];
	delete (v, index, index + 1);
	return removed;
}

int delete (Vector *v, int start, int end) {
	assert(v != NULL);
	assert(start >= 0 && start < v->size && start < end);
	if (1) {
		for (int i = start; i < end; i++)
			v->values[i] = v->values[i + 1];
	}
	v->size -= (end - start);
	int newCapacity =
		v->capacity - (v->capacity - v->size) / v->increment * v->increment;
	if (newCapacity < v->capacity) {
		int *newValues = (int *)realloc(v->values, newCapacity * sizeof(int));
		if (newValues == NULL)
			return -1;
		v->values = newValues;
		v->capacity = newCapacity;
	}
	return 0;
}

int adjust(Vector *v) {
	assert(v != NULL);
	if (v->size < v->capacity) {
		int *newValues = (int *)realloc(v->values, v->size * sizeof(int));
		if (newValues == NULL)
			return -1;
		v->values = newValues;
		v->capacity = v->size;
	}
	return 0;
}