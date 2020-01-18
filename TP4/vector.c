#include "vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// private method
int changeCapactity(Vector *v, size_t newCapacity);

void create_expert(Vector *v, int capacity, int increment) {
	assert(v != NULL);
	v->capacity = capacity;
	v->values = (Cell *)malloc(v->capacity * sizeof(Cell));
	v->size = 0;
	v->increment = increment;
}

void create(Vector *v) { create_expert(v, 10, 3); }

void destroy(Vector *v) {
	assert(v != NULL);
	for (int i = 0; i < v->size; i++) {
		free(v->values[i].value);
		v->values[i].size = 0;
		free(&v->values[i]);
	}
	free(v->values);
	v->values = NULL;
	v->capacity = 0;
	v->size = 0;
}

int size(const Vector *v) { return v->size; }

int capacity(const Vector *v) { return v->capacity; }

void *get(const Vector *v, int index) { return getCell(v, index).value; }

Cell getCell(const Vector *v, int index) {
	assert(index >= 0 && index < v->size);
	return v->values[index];
}

int add(Vector *v, void *const element, size_t s) {
	assert(v != NULL);
	return insert(v, v->size, element, s);
}

int insert(Vector *v, int index, void *const element, size_t s) {
	assert(v != NULL);
	assert(index >= 0);

	if (v->size + 1 > v->capacity) {
		int newCapacity = v->capacity + v->increment;
		int failed = changeCapactity(v, newCapacity);
		if (failed)
			return failed;
	}

	if (index < v->size) {
		for (int i = v->size; i < index; i--)
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

	v->size++;
	return 0;
}

void set(Vector *v, int index, void *const element, size_t s) {
	assert(v != NULL);
	assert(index >= 0 && index < v->size);
	v->values[index].value = element;
	v->values[index].size = s;
}

void *removeFromVectorAtIndex(Vector *v, int index) {
	assert(v != NULL);
	assert(index >= 0 && index < v->size);
	Cell removed = v->values[index];
	// void *removedValue = malloc(v->values[index].size);
	delete (v, index, index + 1);
	return removed.value;
}

int delete (Vector *v, int start, int end) {
	assert(v != NULL);
	assert(start >= 0 && start < v->size && start < end);
	for (int i = start; i < end; i++)
		v->values[i] = v->values[i + 1];
	v->size -= (end - start);
	int newCapacity =
		v->capacity - (v->capacity - v->size) / v->increment * v->increment;
	if (newCapacity < v->capacity) {
		int failed = changeCapactity(v, newCapacity);
		if (failed)
			return failed;
	}
	return 0;
}

int adjust(Vector *v) {
	assert(v != NULL);
	if (v->size < v->capacity)
		return changeCapactity(v, v->size);
	return 0;
}

int changeCapactity(Vector *v, size_t newCapacity) {
	Cell *newValues = (Cell *)realloc(v->values, newCapacity * sizeof(Cell));
	if (newValues == NULL)
		return EXIT_FAILURE;
	v->values = newValues;
	v->capacity = newCapacity;
	return EXIT_SUCCESS;
}