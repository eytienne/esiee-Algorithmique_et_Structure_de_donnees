#ifndef LCA_H
#define LCA_H

#include "types.h"

typedef struct LCACell LCACell;
struct LCACell {
	Key key;
	Value value;
	LCACell *next;
};

typedef struct SDA {
	LCACell *first;
} LCA;

#endif