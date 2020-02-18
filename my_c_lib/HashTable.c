#include "HashTable.h"
#include "LinkedList.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct KeyValuePair {
	char *key;
	void *value;
} KeyValuePair;

HashTable *newHashTable(int capacity, size_t sizeofEach) {
	HashTable *newOne = malloc(sizeof(HashTable));
	newOne->capacity = capacity;
	newOne->sizeofEach = sizeofEach;
	newOne->values = calloc(capacity, sizeof(LinkedList *));
	for (int i = 0; i < capacity; i++) {
		newOne->values[i] = newLinkedList(sizeof(KeyValuePair));
	}
	return newOne;
}

void freeHashTable(HashTable *table) {
	assert(table != NULL);
	for (int i = 0; i < table->capacity; i++) {
		freeLinkedList(table->values[i], NULL);
	}
	free(table->values);
	table->capacity = -1;
}

int hachage(const HashTable *table, const char *key) {
	assert(table != NULL);
	int sum = 0;
	for (int i = 0; i < strlen(key); i++)
		sum += key[i];
	return sum % table->capacity;
}

void put(HashTable *table, char *key, const void *value) {
	assert(table != NULL);

	KeyValuePair *newOne = malloc(sizeof(KeyValuePair));
	size_t lenCle = strlen(key);
	newOne->key = malloc(lenCle);
	strncpy(newOne->key, key, lenCle);
	newOne->value = malloc(table->sizeofEach);
	memcpy(newOne->value, value, table->sizeofEach);

	addToLinkedList(table->values[hachage(table, key)], newOne);
}

int get(const HashTable *table, char *key, void *valeur) {
	assert(table != NULL);
	LinkedList *hit = table->values[hachage(table, key)];
	assert(hit != NULL);
	LLCell *cur = hit->first;
	while (cur != NULL) {
		const KeyValuePair *curP = (KeyValuePair *)cur->value;
		if (strcmp(curP->key, key) == 0) {
			memcpy(valeur, curP->value, table->sizeofEach);
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

void removeFromHashTable(HashTable *table, char *key) {
	assert(table != NULL);
	LinkedList *hit = table->values[hachage(table, key)];
	assert(hit != NULL);
	LLCell *cur = hit->first;
	while (cur != NULL) {
		const KeyValuePair *curP = (KeyValuePair *)cur->value;
		if (strcmp(curP->key, key) == 0) {
			if (cur == hit->first)
				hit->first = cur->next;
			if (cur == hit->last)
				hit->last = cur->previous;
			if (cur->previous != NULL)
				cur->previous->next = cur->next;
			if (cur->next != NULL)
				cur->next->previous = cur->previous;
			free(cur);
			return;
		}
		cur = cur->next;
	}
}
