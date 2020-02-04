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

	int nb = nombre_de_noeuds(t);
	printf("Nb noeuds : %d\n", nb);
	assert(nb == 7);
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

	supprime(&t, 4);
	assert(t->value == 6);
	affiche_arbre2(t);
	nb = nombre_de_noeuds(t);
	printf("Nb noeuds : %d\n", nb);
	assert(nb == 6);

	return 0;
}
