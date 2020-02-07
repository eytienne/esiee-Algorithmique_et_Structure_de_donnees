#ifndef COMPRESSIONTREE_H
#define COMPRESSIONTREE_H

typedef struct Tree {
	int encountered;
	char value;
	struct Tree *left;
	struct Tree *right;
} Tree;

Tree *newArbre();

void arbreHuffman(LinkedList *l);

Tree *creationArbre(char occu, int encountered);

void afficheArbre(Tree *arbre);

#endif