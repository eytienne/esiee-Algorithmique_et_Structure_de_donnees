#ifndef BINARY_PATH_H
#define BINARY_PATH_H

#include <stddef.h>

typedef struct BinaryPath {
	unsigned char *bits;
	size_t length;
} BinaryPath;

BinaryPath *newBinaryPath();
void goToLeft(BinaryPath *bp);
void goToRight(BinaryPath *bp);
void goBack(BinaryPath *bp);
void printBinaryPath(const BinaryPath *bp);

#endif