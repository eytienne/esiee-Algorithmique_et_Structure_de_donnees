#include "BinaryPath.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum DIRECTION { LEFT, RIGHT };

BinaryPath *newBinaryPath() {
	BinaryPath *newOne = malloc(sizeof(BinaryPath));
	newOne->bits = NULL;
	newOne->length = 0;
	return newOne;
}

void freeBinaryPath(BinaryPath *bp) {
	free(bp->bits);
	bp->length = -1;
	free(bp);
}

BinaryPath *bpcpy(BinaryPath *dest, const BinaryPath *src) {
	size_t toCopy = src->length / 8 + (src->length % 8 != 0);
	assert(dest->bits = malloc(toCopy));
	memcpy(dest->bits, src->bits, toCopy);
	dest->length = src->length;
	return dest;
}

void __goTo(BinaryPath *bp, enum DIRECTION d) {
	size_t i = bp->length / 8;
	if (bp->length % 8 == 0) {
		unsigned char *newBits = realloc(bp->bits, i + 1);
		assert(newBits != NULL);
		bp->bits = newBits;
		bp->bits[i] = 0;
	}
	bp->bits[i] = (bp->bits[i]) | (d << bp->length % 8);
	bp->length++;
}

void goToLeft(BinaryPath *bp) {
	__goTo(bp, LEFT);
}

void goToRight(BinaryPath *bp) {
	__goTo(bp, RIGHT);
}

void goBack(BinaryPath *bp) {
	assert(bp->length > 0);
	size_t i = bp->length / 8;
	if (bp->length % 8 == 0) {
		unsigned char *newBits = realloc(bp->bits, i);
		assert(newBits != NULL);
		bp->bits = newBits;
	} else {
		bp->bits[i] &= 255 >> (8 - (bp->length) % 8);
	}
	bp->length--;
}

int getBPStep(const BinaryPath *bp, size_t index) {
	assert(index >= 0);
	assert(index < (bp->length / 8 + (bp->length % 8 != 0)) * 8);
	return ((bp->bits[index / 8] >> (index % 8)) & 1) != 0;
}

void printBinaryPath(const BinaryPath *bp) {
	for (size_t i = 0;

		 i < bp->length
		 //  i < (bp->length / 8 + (bp->length % 8 != 0)) * 8

		 ;
		 i++) {
		printf("%hhu", getBPStep(bp, i));
		if ((i + 1) % 8 == 0)
			printf(" ");
	}
}