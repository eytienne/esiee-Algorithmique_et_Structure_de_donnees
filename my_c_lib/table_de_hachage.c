#include "table_de_hachage.h"
#include "linkedList.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct KeyValuePair {
	char *cle;
	void *value;
} KeyValuePair;

table_de_hachage_t *cree_table_de_hachage(int taille, size_t sizeofEach) {
	table_de_hachage_t *newOne = malloc(sizeof(table_de_hachage_t));
	newOne->taille = taille;
	newOne->values = calloc(taille, sizeof(LinkedList *));
	for (int i = 0; i < taille; i++) {
		newOne->values[i] = newLinkedList(sizeof(KeyValuePair));
	}
	return newOne;
}

void detruit_table_de_hachage(table_de_hachage_t *table) {
	assert(table != NULL);
	for (int i = 0; i < table->taille; i++) {
		freeLinkedList(table->values[i]);
	}
	free(table->values);
	table->taille = -1;
}

int hachage(const table_de_hachage_t *table, const char *cle) {
	assert(table != NULL);
	int sum = 0;
	for (int i = 0; i < strlen(cle); i++)
		sum += cle[i];
	return sum % table->taille;
}

void insere(table_de_hachage_t *table, char *cle, int valeur) {
	assert(table != NULL);

	KeyValuePair *newOne = malloc(sizeof(KeyValuePair));
	size_t lenCle = strlen(cle);
	newOne->cle = malloc(lenCle);
	strncpy(newOne->cle, cle, lenCle);
	newOne->value = valeur;

	addToLinkedList(table->values[hachage(table, cle)], newOne);
}

int recherche(const table_de_hachage_t *table, char *cle, int *valeur) {
	assert(table != NULL);
	LinkedList *hit = table->values[hachage(table, cle)];
	assert(hit != NULL);
	LLCell *cur = hit->first;
	while (cur != NULL) {
		const KeyValuePair *curP = (KeyValuePair *)cur->value;
		if (strcmp(curP->cle, cle) == 0) {
			*valeur = curP->value;
			return 1;
		}
		cur = cur->next;
	}
	return 0;
}

void supprime(table_de_hachage_t *table, char *cle) {
	assert(table != NULL);
	LinkedList *hit = table->values[hachage(table, cle)];
	assert(hit != NULL);
	LLCell *cur = hit->first;
	while (cur != NULL) {
		const KeyValuePair *curP = (KeyValuePair *)cur->value;
		if (strcmp(curP->cle, cle) == 0) {
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
