#include "cell.h"
#include <string.h>

Cell *cellcpy(Cell *dest, const Cell *src) {
	dest->size = src->size;
	memcpy(dest->value, src->value, src->size);
}

void freeCell(Cell *toFree){
    free(toFree->value);
    toFree->size = -1;
}