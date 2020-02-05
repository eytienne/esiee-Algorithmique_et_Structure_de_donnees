#include "cell.h"
#include <string.h>

Cell *cellcpy(Cell *dest, const Cell *src) {
	dest->size = src->size;
	memcpy(dest->value, src->value, src->size);
}

int cellcmp(const Cell *c1, const Cell *c2){
    int sizeDiff = c1->size - c2->size;
    if(sizeDiff != 0)
        return sizeDiff;
    return memcmp(c1, c2, c1->size);
}

void freeCell(Cell *toFree){
    free(toFree->value);
    toFree->size = -1;
}