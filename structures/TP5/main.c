#include "../../my_c_lib/tree.h"
#include "../../my_c_lib/cell.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Cell *cellFromInt(int init){
	Cell *newOne = malloc(sizeof(Cell));
	int *copy = malloc(sizeof(int));
	*copy = init;
	newOne->value = copy;
	newOne->size = sizeof(int);
}

int intCellCmp(const Cell *c1, const Cell *c2){
	return *((int*)c1->value) - *((int*)c2->value);
}

int main(int argc, char const *argv[]) {
	Tree *t = cree_arbre(4, NULL, NULL);
	insere(t, cellFromInt(3), intCellCmp);
	insere(t, cellFromInt(1), intCellCmp);
	insere(t, cellFromInt(6), intCellCmp);
	insere(t, cellFromInt(6), intCellCmp);
	insere(t, cellFromInt(9), intCellCmp);
	insere(t, cellFromInt(7), intCellCmp);

	int nb = nombre_de_noeuds(t);
	printf("Nb noeuds : %d\n", nb);
	assert(nb == 7);
	affiche_arbre(t);
	affiche_arbre2(t);

	assert(trouve_noeud(t, cellFromInt(6)) != NULL);
	assert(trouve_noeud(t, cellFromInt(8)) == NULL);

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
