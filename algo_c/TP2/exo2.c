#include "../../structures_de_donnees_c/lib/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Grille {
	int **values;
} Grille;

Grille *newGrille(int n) {
	Grille *g = (Grille *)malloc(sizeof(Grille));
	g->values = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++) {
		g->values[i] = (int *)malloc(n * sizeof(int));
	}
    return g;
}

void initialiseGrille(const Grille *g, int n) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			g->values[i][j] = (rand() < __INT_MAX__ / 2 ? 0 : 1);
		}
	}
}

void afficheGrille(const Grille *g, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j > 0)
				printf("\t");
			printf("%d", g->values[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[]) {
	const int gsize = 10;
	Grille *g = newGrille(gsize);
	initialiseGrille(g, gsize);
	afficheGrille(g, gsize);
	return 0;
}
