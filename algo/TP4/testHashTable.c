#include "../../my_c_lib/table_de_hachage.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	table_de_hachage_t *t = cree_table_de_hachage(2);
	assert(t != NULL);
	assert(t->taille == 2);

	char *first = "first";
	char *second = "second";
	char *third = "third";

	insere(t, first, 1);

	int j = 0;
	assert(recherche(t, first, &j));
	assert(j == 1);

	insere(t, second, 2);
	insere(t, third, 3);
	j = 0;
	assert(recherche(t, first, &j));
	assert(j == 1);
	j = 0;
	assert(recherche(t, second, &j));
	assert(j == 2);
	j = 0;
	assert(recherche(t, third, &j));
	assert(j == 3);

	supprime(t, first);
	j = 0;
	assert(!recherche(t, first, &j));
	assert(j == 0);
	j = 0;
	assert(recherche(t, second, &j));
	assert(j == 2);
	j = 0;
	assert(recherche(t, third, &j));
	assert(j == 3);

	return 0;
}
