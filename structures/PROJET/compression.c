#include "compression.h"
#include "../../my_c_lib/PriorityQueue.h"
#include "../../my_c_lib/TreeNode.h"
#include "../../my_c_lib/Vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MAX 1000
#define ASCII_TABLE_SIZE 256

void printPQCell(const PQCell *pqc) {
	printf("'%c' (%d)\n", *(unsigned char *)(pqc->value), pqc->priority);
}

int printTreeNode(const TreeNode *tn, void *buffer) {
	const unsigned char *uc = (unsigned char *)tn->value;
	assert(uc != NULL);
	printf("'%c'\n", *uc);
	return WALK_SUCCESS;
}

void printVectorOfPQCell(const Vector *v) {
	printf("Vector (size : %d, capacity : %d): \n", size(v), capacity(v));
	for (int i = 0; i < size(v); i++) {
		PQCell *cc = v->values[i];
		printf("'%c' (%d)\n", *(unsigned char *)(cc->value), cc->priority);
	}
}

int dec_pq_cell_cmp(const void *a, const void *b) {
	return -1 * pq_cell_cmp(a, b);
}

void compress(FILE *src, char *filename) {
	unsigned char *buffer = malloc(sizeof(TAILLE_MAX));
	int *counters = calloc(ASCII_TABLE_SIZE, sizeof(int));

	while (!feof(src) && fgets(buffer, TAILLE_MAX, src) != NULL) {
		int i = 0;
		while (i < TAILLE_MAX) {
			printf("%c", buffer[i]);
			counters[buffer[i]]++;
			if (buffer[i] == '\n')
				break;
			i++;
		}
	}

	Vector *v = malloc(sizeof(Vector));
	create(v, sizeof(PQCell));
	for (unsigned int i = 0; i < ASCII_TABLE_SIZE; i++) {
		if (counters[i] > 0) {
			const PQCell *toAdd =
				newPQCell(&i, sizeof(unsigned char), counters[i]);
			add(v, toAdd);
			printf("%p\n", v->values[size(v) - 1]);
		}
	}
	printVectorOfPQCell(v);
	qsort(v->values, size(v), sizeof(void *), dec_pq_cell_cmp);
	printVectorOfPQCell(v);
	printf("----------------------\n");

	PQCell **values = (PQCell **)v->values;

	PriorityQueue *pq = newPriorityQueue(sizeof(TreeNode));
	for (int i = 0; i < size(v); i++) {
		TreeNode *toAdd = newTreeNode(values[i]->value, sizeof(PQCell));
		printTreeNode(toAdd, NULL);
		addToPriorityQueue(pq, toAdd, values[i]->priority);
	}

	LLCell *huffmanHeap = pq->first;

	while (huffmanHeap != NULL) {
		printTreeNode(huffmanHeap->value, NULL);
		huffmanHeap = huffmanHeap->next;
	}

	// TreeNode *huffmanHeap = NULL;
	// while (!isLLEmpty(pq)) {
	// 	huffmanHeap = shift(pq);
	// 	printTreeNode(huffmanHeap, NULL);
	// 	if (!isLLEmpty(pq)) {
	// 		TreeNode *toMergeWith = shift(pq);
	// 		const unsigned char nonLeaf = EOF;
	// 		const int priority = ((PQCell *)huffmanHeap->value)->priority +
	// 							 ((PQCell *)toMergeWith->value)->priority;
	// 		TreeNode *merged = newTreeNode(
	// 			newPQCell(&nonLeaf, sizeof(unsigned char), priority),
	// 			sizeof(PQCell));
	// 		merged->left = huffmanHeap;
	// 		merged->right = toMergeWith;
	// 		addToPriorityQueue(pq, merged, priority);
	// 	}
	// }

	// walk(huffmanHeap, INFIXE, printTreeNode, NULL);
}

void uncompress(FILE *dest, char *filename);