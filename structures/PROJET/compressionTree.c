#include "compressionTree.h"

#include <assert.h>
#include <stdlib.h>


Tree *newArbre() {
	Tree *arbre = (Tree *)malloc(sizeof(Tree));
	assert(arbre != NULL);
	arbre->encountered = 0;
	arbre->value = 0;
	arbre->left = NULL;
	arbre->right = NULL;
	return arbre;
}

Tree *creationArbre(char occu, int encountered) {
	Tree *arbre = newArbre();
	arbre->encountered = encountered;
	arbre->value = occu;
	return arbre;
}

void afficheArbre(Tree *arbre) {

	printf("( [%c] -> [%d] | )", arbre->left->value, arbre->left->encountered);
	printf("( [%c] -> [%d] | )\n", arbre->right->value,
		   arbre->right->encountered);

	afficheArbre(arbre->left);
	afficheArbre(arbre->right);
}
