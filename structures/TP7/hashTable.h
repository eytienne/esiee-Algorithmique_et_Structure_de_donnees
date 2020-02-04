#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "types.h"

typedef struct HTCell HTCell;
struct HTCell {
	Key key;
	Value value;
	HTCell *next;
};

typedef struct HashTable {
	HTCell *first;
	size_t size;
} HashTable;

#endif