#include "BinaryPath.h"
#include <assert.h>
#include <stdio.h>

enum DIRECTION { LEFT, RIGHT };

BinaryPath *newBinaryPath() {
	BinaryPath *newOne = malloc(sizeof(BinaryPath));
	newOne->bits = NULL;
	newOne->length = 0;
}

void __goTo(BinaryPath *bp, enum DIRECTION d) {
	size_t i = bp->length / 8;
	if (bp->length % 8 == 0) {
		unsigned char *newBits = realloc(bp->bits, i + 1);
		assert(newBits != NULL);
		bp->bits = newBits;
	}
	bp->bits[i] = (bp->bits[i]) | (d << bp->length % 8);
	bp->length++;
}

void goToLeft(BinaryPath *bp) { __goTo(bp, LEFT); }

void goToRight(BinaryPath *bp) { __goTo(bp, RIGHT); }

void goBack(BinaryPath *bp) {
	assert(bp->length > 0);
	size_t i = bp->length / 8;
	printf("\n%lu (%lu)\n", bp->length, i);
	if (bp->length % 8 == 0) {
		unsigned char *newBits = realloc(bp->bits, i);
		assert(newBits != NULL);
		bp->bits = newBits;
		printf("realloc!\n");
	} else {
		bp->bits[i] &= bp->length % 8;
	}
	bp->length--;
}

int getBPStep(const BinaryPath *bp, size_t index) {
	assert(index >= 0);
	return ((bp->bits[index / 8] >> (index % 8)) & 1) != 0;
}

void printBinaryPath(const BinaryPath *bp) {
	for (size_t i = 0; i < bp->length; i++) {
		printf("%hhu", getBPStep(bp, i));
		if ((i + 1) % 8 == 0)
			printf(" ");
	}
	printf("\n");
}