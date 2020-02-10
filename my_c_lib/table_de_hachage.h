#ifndef table_de_hachage_H
#define table_de_hachage_H

#include "linkedList.h"
#include <stdlib.h>

typedef struct table_de_hachage_t {
	LinkedList **values;
	int taille;
} table_de_hachage_t;

table_de_hachage_t *cree_table_de_hachage(int taille);

void detruit_table_de_hachage(table_de_hachage_t *table);

int hachage(const table_de_hachage_t *table, const char *cle);

void insere(table_de_hachage_t *table, char *cle, int valeur);

int recherche(const table_de_hachage_t *table, char* cle, int* valeur);

void supprime(table_de_hachage_t *table, char* cle);

#endif