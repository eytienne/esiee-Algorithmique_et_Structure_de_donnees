#include "types.h"
#include <stdio.h>
#include <stdlib.h>

int keycmp(const Key k1, const Key k2) { return strcmp(k1, k2); }
Key keycpy(Key dest, const Key src) {
	return (Key)strcpy((char *)dest, (const char *)src);
}

int valcmp(const Value v1, const Value v2) { return v1 == v2; }
Value valcpy(Value dest, const Value src) {
	*dest = *src;
	return dest;
}