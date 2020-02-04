#include "table_de_hachage.h"
#include <string.h>

table_de_hachage_t *cree_table_de_hachage(int taille) {
	table_de_hachage_t *newOne =
		(table_de_hachage_t *)malloc(sizeof(table_de_hachage_t));
	newOne->taille = taille;
	newOne->values = (Pile **)calloc(taille, sizeof(Pile *));
	for (int i = 0; i < taille; i++) {
		newOne->values[i] = newLinkedList();
	}
}

void detruit_table_de_hachage(table_de_hachage_t *table) {
	for (int i = 0; i < table->taille; i++) {
		freeLinkedList(table->values[i]);
	}
	free(table->values);
	table->taille = -1;
}

int hachage(const table_de_hachage_t *table, char *cle) {
	int sum = 0;
	for (int i = 0; i < strlen(cle); i++)
		sum += cle[i];
	return sum % table->taille;
}

void insere(table_de_hachage_t *table, char* cle, int valeur){

    ajouterAListe(table->values[hachage(table, cle)], valeur);
}