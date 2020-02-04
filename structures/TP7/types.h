#ifndef SDATYPES_H
#define SDATYPES_H

#include <string.h>

typedef char *Key;
typedef int *Value;

int keycmp(const Key k1, const Key k2);
Key keycpy(Key dest, const Key src);

int valcmp(const Value v1, const Value v2);
Value valcpy(Value dest, const Value src);

#endif