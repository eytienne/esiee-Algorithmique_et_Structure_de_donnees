#include "../../structures_de_donnees_c/lib/vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int insererAIndice(Vector *v, int index, int value) {
	return insert(v, index, &value, sizeof(int));
}

void supprimeAIndice(Vector *v, int index) {
	removeFromVectorAtIndex(v, index);
}

int rechercheSequentielle(const Vector *v, int value) {
	for (int i = 0; i < size(v); i++) {
		if (*(int *)get(v, i) == value)
			return i;
	}
	return -1;
}

void display(const Vector *v) {
	printf("------------------------\n");
	for (int i = 0; i < size(v); i++)
		printf("%d\n", *(int *)get(v, i));
}

int main(int argc, char const *argv[]) {

	srand(time(NULL));
	Vector *v;
	create_expert(v, 10, 1);
	for (int i = 0; i < 10; i++) {
		int r = rand();
		add(v, &r, sizeof(int));
	}
	display(v);
	insererAIndice(v, 8, 5);
	display(v);
	supprimeAIndice(v, 3);
	display(v);
	assert(rechercheSequentielle(v, 5) == 7);
	return 0;
}
