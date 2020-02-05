#ifndef CELL_H
#define CELL_H

#include <stdlib.h>

typedef struct Cell {
	void *value;
	size_t size;
} Cell;

Cell *cellcpy(Cell *dest, const Cell *src);

int cellcmp(const Cell *c1, const Cell *c2);

void freeCell(Cell *toFree);

#endif