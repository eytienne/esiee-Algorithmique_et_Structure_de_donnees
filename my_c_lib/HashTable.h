#ifndef table_de_hachage_H
#define table_de_hachage_H

#include "LinkedList.h"
#include <stddef.h>

typedef struct HashTable {
	LinkedList **values;
	int capacity;
	size_t sizeofEach;
} HashTable;

HashTable *newHashTable(int capacity, size_t sizeofEach);

void freeHashTable(HashTable *table);

int hachage(const HashTable *table, const char *key);

void put(HashTable *table, char *key, const void *value);

int get(const HashTable *table, char *key, void *value);

void removeFromHashTable(HashTable *table, char *key);

#endif