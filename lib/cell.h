#ifndef CELL_H
#define CELL_H

#include <stdlib.h>

typedef struct Cell {
	void *value;
	size_t size;
} Cell;

#endif