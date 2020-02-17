#include "compression.h"
#include "../../my_c_lib/PriorityQueue.h"
#include "../../my_c_lib/TreeNode.h"
#include "../../my_c_lib/Vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MAX 1000
#define ASCII_TABLE_SIZE 256

typedef struct HuffmanPair {
	unsigned char c;
	unsigned int nbOccurrences;
} HuffmanPair;

void printHuffmanPair(const HuffmanPair *hp) {
	printf("hp: ['%c' (%d)]", hp->c, hp->nbOccurrences);
}

void printVoidHuffmanPair(const void *e) {
	assert(e);
	printHuffmanPair((const HuffmanPair *)e);
}

int printTN(const TreeNode *tn, void *buffer) {
	const HuffmanPair *uc = (const HuffmanPair *)tn->value;
	assert(uc && "Null value node !");
	printHuffmanPair(uc);
	printf("\n");
	return WALK_SUCCESS;
}

void printPQ(const PriorityQueue *pq) {
	printf("~~~~~~~~~~~~~~~~~\n");
	LLCell *cur = pq->first;
	while (cur != NULL) {
		const PQCell *curPQC = (const PQCell *)cur->value;
		const TreeNode *curTN = (const TreeNode *)curPQC->value;
		const HuffmanPair *curHP = (const HuffmanPair *)curTN->value;
		// printf("pqc:%p tn:%p  %p", curPQC, curTN, curHP);
		printHuffmanPair(curHP);
		if (cur == pq->first)
			printf(" <-- first ");
		if (cur == pq->last)
			printf(" <-- last ");
		printf("\n");
		cur = cur->next;
	}
	printf("\n");
}

void printVectorOfHP(const Vector *v) {
	printf("Vector (size : %d, capacity : %d): \n", size(v), capacity(v));
	for (int i = 0; i < size(v); i++) {
		const HuffmanPair *cc = v->values[i];
		printHuffmanPair(cc);
	}
}

int huffman_pair_cmp(const void *a, const void *b) {
	assert(a && b && "Arguments should not be null");
	const HuffmanPair *c = *(const HuffmanPair **)a;
	const HuffmanPair *d = *(const HuffmanPair **)b;
	assert(a && b && "Null values cannot be compared");
	return d->nbOccurrences - c->nbOccurrences;
}

void compress(FILE *src, char *filename) {
	unsigned char *buffer = malloc(sizeof(TAILLE_MAX));
	int *counters = calloc(ASCII_TABLE_SIZE, sizeof(int));

	while (!feof(src) && fgets(buffer, TAILLE_MAX, src) != NULL) {
		int i = 0;
		while (i < TAILLE_MAX) {
			if (buffer[i] == '\0')
				break;
			printf("%d '%c'\n", i, buffer[i]);
			counters[buffer[i]]++;
			if (buffer[i] == '\n')
				break;
			i++;
		}
	}

	Vector *v = malloc(sizeof(Vector));
	create(v, sizeof(HuffmanPair));
	for (unsigned int i = 0; i < ASCII_TABLE_SIZE; i++) {
		if (counters[i] > 0) {
			const HuffmanPair toAdd = {(unsigned char)i, counters[i]};
			add(v, &toAdd);
		}
	}
	qsort(v->values, size(v), sizeof(void *), huffman_pair_cmp);
	// printVectorOfHP(v);
	printf("----------------------\n");

	HuffmanPair **values = (HuffmanPair **)v->values;

	printf("---PRIORITY QUEUE FILLING---\n");

	PriorityQueue *pq = newPriorityQueue(sizeof(TreeNode));
	for (int i = 0; i < size(v); i++) {
		TreeNode *toAdd =
			newTreeNode(values[i], sizeof(HuffmanPair), NULL, NULL);
		addToPriorityQueue(pq, toAdd, values[i]->nbOccurrences);
	}

	printf("---PRIORITY QUEUE FILLED---\n");
	printPQ(pq);

	TreeNode *huffmanHeap = NULL;
	while (!isLLEmpty(pq)) {
		huffmanHeap = shiftFromPriorityQueue(pq);
		if (!isLLEmpty(pq)) {
			TreeNode *toMergeWith = shiftFromPriorityQueue(pq);
			const HuffmanPair *hpOne = (const HuffmanPair *)huffmanHeap->value;
			const HuffmanPair *hpTwo = (const HuffmanPair *)toMergeWith->value;
			assert(hpOne && hpTwo && "null!");
			const int priority = hpOne->nbOccurrences + hpTwo->nbOccurrences;
			printf("%d + %d = %d\n", hpOne->nbOccurrences, hpTwo->nbOccurrences,
				   priority);
			const HuffmanPair nonLeaf = {'@', priority};
			TreeNode *merged = newTreeNode(&nonLeaf, sizeof(HuffmanPair),
										   huffmanHeap, toMergeWith);
			addToPriorityQueue(pq, merged, priority);
		}
	}
	printf("vvvvvvvvvvvvvvvvvvvvvvvvv\n");
	prefixePrintInfo ppi = {0, printVoidHuffmanPair};
	walk(huffmanHeap, PREFIXE, prefixPrint, &ppi);
}

void uncompress(FILE *dest, char *filename);