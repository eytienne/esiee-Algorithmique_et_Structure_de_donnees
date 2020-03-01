#ifndef BINARY_SEQUENCE_H
#define BINARY_SEQUENCE_H

#include <stddef.h>

typedef struct BinarySequence {
	unsigned char *bits;
	size_t length;
} BinarySequence;

BinarySequence *newBinarySequence();

void freeBinarySequence(BinarySequence *bs);

BinarySequence *bscpy(BinarySequence *dest, const BinarySequence *src);

void addZero(BinarySequence *bs);
void addOne(BinarySequence *bs);
void shorten(BinarySequence *bs);

int getBit(const BinarySequence *bs, size_t index);

void printBinarySequence(const BinarySequence *bs);

#endif