#include "BinarySequence.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum DIRECTION { ZERO, ONE };

BinarySequence *newBinarySequence() {
	BinarySequence *newOne = malloc(sizeof(BinarySequence));
	newOne->bits = NULL;
	newOne->length = 0;
	return newOne;
}

void freeBinarySequence(BinarySequence *bs) {
	free(bs->bits);
	bs->length = -1;
	free(bs);
}

BinarySequence *bscpy(BinarySequence *dest, const BinarySequence *src) {
	size_t toCopy = src->length / 8 + (src->length % 8 != 0);
	assert(dest->bits = malloc(toCopy));
	memcpy(dest->bits, src->bits, toCopy);
	dest->length = src->length;
	return dest;
}

void __goTo(BinarySequence *bs, enum DIRECTION d) {
	size_t i = bs->length / 8;
	if (bs->length % 8 == 0) {
		unsigned char *newBits = realloc(bs->bits, i + 1);
		assert(newBits != NULL);
		bs->bits = newBits;
		bs->bits[i] = 0;
	}
	bs->bits[i] = (bs->bits[i]) | (d << bs->length % 8);
	bs->length++;
}

void addZero(BinarySequence *bs) {
	__goTo(bs, ZERO);
}

void addOne(BinarySequence *bs) {
	__goTo(bs, ONE);
}

void shorten(BinarySequence *bs) {
	assert(bs->length > 0);
	size_t i = bs->length / 8;
	if (bs->length % 8 == 0) {
		unsigned char *newBits = realloc(bs->bits, i);
		assert(newBits != NULL);
		bs->bits = newBits;
	} else {
		bs->bits[i] &= 255 >> (8 - (bs->length) % 8);
	}
	bs->length--;
}

int getBit(const BinarySequence *bs, size_t index) {
	assert(index >= 0);
	assert(index < (bs->length / 8 + (bs->length % 8 != 0)) * 8);
	return ((bs->bits[index / 8] >> (index % 8)) & 1) != 0;
}

void printBinarySequence(const BinarySequence *bs) {
	for (size_t i = 0; i < bs->length; i++) {
		printf("%hhu", getBit(bs, i));
		if ((i + 1) % 8 == 0)
			printf(" ");
	}
}