// #include "compression.h"
#include "../../my_c_lib/linkedList.h"
#include "../../my_c_lib/tree.h"
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MAX 1000
#define ASCII_TABLE_SIZE 256

void arbreHuffman(LinkedList *l);

void compress(FILE *src, char *filename) {
	unsigned char *buffer = malloc(sizeof(TAILLE_MAX));
	int *counters = calloc(ASCII_TABLE_SIZE, sizeof(int));

	while (feof(src) && fgets(buffer, TAILLE_MAX, src) != NULL) {
		int i = 0;
		while (i < TAILLE_MAX) {
			counters[buffer[i]]++;
			if (buffer[i] == '\n')
				break;
			i++;
		}
	}

	char c;
	LinkedList *liste = newLinkedList(sizeof(Tree));
	for (int i = 0; i < 255; i++) {
		if (counters[i] > 0) {
			Tree *arbre = creationArbre((char)i, counters[i]);
			addToLinkedList(liste, arbre);
		}
	}

	// arbreHuffman(liste);
	// printf("TEST ARBRE HUFFMAN\n");
}

void uncompress(FILE *dest, char *filename);

Tree *__countToTree(int letters[255], int beg, int end) {}

// void arbreHuffman(LinkedList *l) {
// 	LLCell *test = l->first;
// 	while (test->suivant != NULL) {
// 		test->value Tree *arbre = creationArbre(
// 			(char)0, (->encountered + test->suivant->arbre->encountered));
// 		arbre->left =
// 			creationArbre(test->arbre->value, test->arbre->encountered);
// 		test = test->suivant;
// 		arbre->right =
// 			creationArbre(test->arbre->value, test->arbre->encountered);
// 		ajouterListe(l, arbre);
// 		l->premier = test->suivant;
// 		break;
// 	}
// }
