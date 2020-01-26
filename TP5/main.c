#include "../lib/tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	Tree *t = cree_arbre(4, NULL, NULL);
	insere(t, 3);
	insere(t, 1);
	insere(t, 6);
	insere(t, 6);
	insere(t, 9);
	insere(t, 7);

	printf("Nb noeuds : %d\n", nombre_de_noeuds(t));
	affiche_arbre(t);
	affiche_arbre2(t);

	assert(trouve_noeud(t, 6) != NULL);
	assert(trouve_noeud(t, 8) == NULL);

	t->value = 0;
	int badWalk = verifie(t);
	assert(badWalk);

	t->value = 4;
	badWalk = verifie(t);
	assert(!badWalk);

	int sortThis[5] = {10, (-1), 4, 8, 2};
	int *sorted = tri(sortThis, 5);
	for (size_t i = 0; i < 5; i++)
		printf("%d,", sorted[i]);
	printf("\n");

	

	return 0;
}
