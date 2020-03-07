#include "BinarySequence.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum DIRECTION { ZERO, ONE };

void __fprintBinary(const unsigned char *restrict ptr, size_t size,
					FILE *restrict stream) {
	for (size_t i = 0; i < size; i++) {
		fprintf(stream, "%hhu", ((ptr[i / 8] >> (i % 8)) & 1) != 0);
		if ((i + 1) % 8 == 0)
			fprintf(stream, " ");
	}
}

void __printBinary(const unsigned char *restrict ptr, size_t size) {
	__fprintBinary(ptr, size, stdout);
}

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

BinarySequence *bscat(BinarySequence *dest, const BinarySequence *src) {
	for (size_t i = 0; i < src->length; i++) {
		switch (getBit(src, i)) {
		case ONE:
			addOne(dest);
			break;
		case ZERO:
			addZero(dest);
		}
	}
	return dest;
}

void __add(BinarySequence *bs, enum DIRECTION d) {
	size_t i = bs->length / 8;
	if (bs->length % 8 == 0) {
		unsigned char *newBits = realloc(bs->bits, i + 1);
		assert(newBits != NULL);
		bs->bits = newBits;
		bs->bits[i] = 0;
	}
	unsigned char mask = (d << bs->length % 8);
	bs->bits[i] |= mask;
	bs->length++;
}

void addZero(BinarySequence *bs) {
	__add(bs, ZERO);
}

void addOne(BinarySequence *bs) {
	__add(bs, ONE);
}

void shorten(BinarySequence *bs) {
	assert(bs->length > 0);
	size_t i = bs->length / 8;
	if (bs->length % 8 == 0) {
		unsigned char *newBits = realloc(bs->bits, i);
		assert(newBits != NULL);
		bs->bits = newBits;
	} else {
		unsigned char mask = 255 >> (9 - (bs->length % 8));
		bs->bits[i] &= mask;
	}
	bs->length--;
}

int getBit(const BinarySequence *bs, size_t index) {
	assert(index >= 0);
	assert(index < (bs->length / 8 + (bs->length % 8 != 0)) * 8);
	return ((bs->bits[index / 8] >> (index % 8)) & 1) != 0;
}

void printBinarySequence(const BinarySequence *bs) {
	fprintBinarySequence(bs, stdout);
}

void fprintBinarySequence(const BinarySequence *bs, FILE *restrict stream) {
	__fprintBinary(bs->bits, bs->length, stream);
	return;
	for (size_t i = 0; i < bs->length; i++) {
		fprintf(stream, "%hhu", getBit(bs, i));
		if ((i + 1) % 8 == 0)
			fprintf(stream, " ");
	}
}