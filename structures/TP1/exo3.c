#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double soldeAterAnnees(double soldeInitial, double taux, int nbAnnees) {
	return soldeInitial * pow(1 + taux, (double)nbAnnees);
}

int main() {
	// 3.1
	// printf("Entrez : (solde initial) (taux) (nb annees)\n");
	// double soldeInitial, taux;
	// int nbAnnees;
	// scanf("%lf %lf %d", &soldeInitial, &taux, &nbAnnees);
	// printf("Vous aurez : %g €\n",
	// 	   soldeAterAnnees(soldeInitial, taux, nbAnnees));

	// 3.2
	printf("Entrez votre taux : ");
	double taux;
	scanf("%lf", &taux);
	taux += 1;
	int required = 1;
	while ((taux *= taux) < 2)
		++required;
	printf("Votre solde initial aura doublé après %d années !\n", required);
}