#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// public methods
void destroy(Vector *v);

int size(const Vector *v);

int capacity(const Vector *v);

void *get(const Vector *v, int index);

Cell getCell(const Vector *v, int index);

int add(Vector *v, void *const element, size_t size);

int insert(Vector *v, int index, void *const element, size_t size);

void set(Vector *v, int index, void *const element, size_t size);

void *removeFromVectorAtIndex(Vector *v, int index);

int delete (Vector *v, int start, int end);

int adjust(Vector *v);

// private method
int changeCapactity(Vector *v, int newCapacity);

Vector *create_expert(int cap, int inc) {
	Vector *v = (Vector *)malloc(sizeof(Vector));

	// setting public methods
	v->destroy = destroy;
	v->size = size;
	v->capacity = capacity;
	v->get = get;
	v->getCell = getCell;
	v->add = add;
	v->insert = insert;
	v->set = set;
	v->remove = removeFromVectorAtIndex;
	v->delete = delete;
	v->adjust = adjust;

	v->__capacity__ = cap;
	v->values = (Cell *)malloc(v->capacity(v) * sizeof(Cell));
	v->__size__ = 0;
	v->__increment__ = inc;
	return v;
}

Vector *create() { return create_expert(10, 3); }

void destroy(Vector *v) {
	assert(v != NULL);
	for (int i = 0; i < v->size(v); i++) {
		free(v->values[i].value);
		v->values[i].size = 0;
		free(&v->values[i]);
	}
	free(v->values);
	v->values = NULL;
	v->__capacity__ = 0;
	v->__size__ = 0;
}

int size(const Vector *v) { return v->__size__; }

int capacity(const Vector *v) { return v->__capacity__; }

void *get(const Vector *v, int index) { return getCell(v, index).value; }

Cell getCell(const Vector *v, int index) {
	assert(index >= 0 && index < v->size(v));
	return v->values[index];
}

int add(Vector *v, void *const element, size_t s) {
	assert(v != NULL);
	return insert(v, v->size(v), element, s);
}

int insert(Vector *v, int index, void *const element, size_t s) {
	assert(v != NULL);
	assert(index >= 0);

	if (v->size(v) + 1 > v->capacity(v)) {
		int newCapacity = v->capacity(v) + v->__increment__;
		int failed = changeCapactity(v, newCapacity);
		if (failed)
			return failed;
	}

	if (index < v->size(v)) {
		for (int i = v->size(v); i < index; i--)
			v->values[i] = v->values[i - 1];
	}

	Cell *newCell = (Cell *)malloc(sizeof(Cell));
	newCell->value = malloc(s);
	if (s == 1) {
		strcpy(newCell->value, element);
	} else {
		memcpy(newCell->value, element, s);
	}

	newCell->size = s;
	v->values[index] = *newCell;

	v->__size__++;
	return 0;
}

void set(Vector *v, int index, void *const element, size_t s) {
	assert(v != NULL);
	assert(index >= 0 && index < v->size(v));
	v->values[index].value = element;
	v->values[index].size = s;
}

void *removeFromVectorAtIndex(Vector *v, int index) {
	assert(v != NULL);
	assert(index >= 0 && index < v->size(v));
	Cell removed = v->values[index];
	delete (v, index, index + 1);
	return removed.value;
}

int delete (Vector *v, int start, int end) {
	assert(v != NULL);
	assert(start >= 0 && start < v->size(v) && start < end);
	for (int i = start; i < end; i++)
		v->values[i] = v->values[i + 1];
	v->__size__ -= (end - start);
	size_t newCapacity = v->capacity(v) - (v->capacity(v) - v->size(v)) /
											  v->__increment__ *
											  v->__increment__;
	if (newCapacity < v->capacity(v)) {
		int failed = changeCapactity(v, newCapacity);
		if (failed)
			return failed;
	}
	return 0;
}

int adjust(Vector *v) {
	assert(v != NULL);
	if (size(v) < v->capacity(v))
		return changeCapactity(v, v->size(v));
	return 0;
}

int changeCapactity(Vector *v, int newCapacity) {
	Cell *newValues = (Cell *)realloc(v->values, newCapacity * sizeof(Cell));
	if (newValues == NULL)
		return EXIT_FAILURE;
	v->values = newValues;
	v->__capacity__ = newCapacity;
	return EXIT_SUCCESS;
}