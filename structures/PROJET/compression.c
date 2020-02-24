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

typedef struct HuffmanCode {
	unsigned char c;
	BinaryPath *code;
} HuffmanCode;

void printHuffmanPairChar(const HuffmanPair *hp) {
	printf("'%c'", hp->c);
}

void printHuffmanPair(const HuffmanPair *hp) {
	printf("['%c',%u]", hp->c, hp->nbOccurrences);
	// printf("%p['%c',%u]", hp, hp->c, hp->nbOccurrences);
}

void printVoidHuffmanPair(const void *e) {
	assert(e);
	printHuffmanPair((const HuffmanPair *)e);
}

int printTN(const TreeNode *tn, void *buffer) {
	const HuffmanPair *uc = (const HuffmanPair *)tn->value;
	assert(uc && "Null value node !");
	if (isLeaf(tn))
		printHuffmanPair(uc);
	printf("\n");
	return WALK_SUCCESS;
}

int __printLeavesWithBPaths(const TreeNode *t, void *buffer,
							const BinaryPath *bp) {
	assert(buffer != NULL);
	void (*printer)(const void *) = (void (*)(const void *))buffer;

	if (isLeaf(t)) {
		printer(t->value);
		printf(" -> ");
		printBinaryPath(bp);
		printf("\n");
	}

	return WALK_SUCCESS;
}

int __pickLeaves(const TreeNode *t, void *buffer, const BinaryPath *bp) {
	assert(buffer != NULL);
	Vector *leaves = buffer;
	// if (isLeaf(t)) {
		HuffmanCode *newCode = malloc(sizeof(HuffmanCode));
		const HuffmanPair *value = t->value;
		newCode->c = value->c;
		printf("'%c' -> ", newCode->c);
		newCode->code = malloc(sizeof(BinaryPath));
		bpcpy(newCode->code, bp);
		printBinaryPath(bp);
		printf("\n");
		add(leaves, newCode);
	// }
	return WALK_SUCCESS;
}

Vector *pickLeaves(TreeNode *root) {
	Vector *leaves = newVectorExpert(sizeof(HuffmanCode));
	walkExpert(root, PREFIXE, __pickLeaves, leaves);
	return leaves;
}

int ucharcmp(const void *a, const void *b) {
	return *(unsigned char *)a - *(unsigned char *)b;
}

int printLeavesWithBPaths(const TreeNode *root) {

	// walkExpert(root, PREFIXE, __printLeavesWithBPaths, printHuffmanPairChar);
	Vector *leaves = pickLeaves(root);
	// qsort(leaves, size(leaves), leaves->sizeofEach, ucharcmp);
	// printf("coucou\n");
	// for (size_t i = 0; i < size(leaves); i++) {
	// 	const HuffmanCode *cur = leaves->values[i];
	// 	printf("%c -> ", cur->c);
	// 	printBinaryPath(cur->code);
	// }
}

void printPQTN(const PriorityQueue *pq) {
	LLCell *cur = pq->parent->first;
	while (cur != NULL) {
		const PQCell *curPQC = (const PQCell *)cur->value;
		const TreeNode *curTN = (const TreeNode *)curPQC->value;
		const HuffmanPair *curHP = (const HuffmanPair *)curTN->value;
		printHuffmanPair(curHP);
		cur = cur->next;
	}
	printf("\n");
}

void printPQ(const PriorityQueue *pq) {
	printf("~~~~~~~~~~~~~~~~~\n");
	LLCell *cur = pq->parent->first;
	while (cur != NULL) {
		const PQCell *curPQC = (const PQCell *)cur->value;
		const TreeNode *curTN = (const TreeNode *)curPQC->value;
		const HuffmanPair *curHP = (const HuffmanPair *)curTN->value;
		printHuffmanPair(curHP);
		if (cur == pq->parent->first)
			printf(" <-- first ");
		if (cur == pq->parent->last)
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
		printf("\n");
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

	while (!feof(src) && fgets((char *)buffer, TAILLE_MAX, src) != NULL) {
		int i = 0;
		while (i < TAILLE_MAX) {
			if (buffer[i] == '\0')
				break;
			printf("%c", buffer[i]);
			// printf("%d '%c'\n", i, buffer[i]);
			counters[buffer[i]]++;
			if (buffer[i] == '\n')
				break;
			i++;
		}
	}
	printf("\n");

	Vector *v = newVector(sizeof(HuffmanPair));
	for (unsigned int i = 0; i < ASCII_TABLE_SIZE; i++) {
		if (counters[i] > 0) {
			const HuffmanPair toAdd = {(unsigned char)i, counters[i]};
			add(v, &toAdd);
		}
	}
	qsort(v->values, size(v), sizeof(void *), huffman_pair_cmp);
	printVectorOfHP(v);
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
	while (!isPQEmpty(pq)) {
		printf("________________________________________\n");
		huffmanHeap = shiftFromPriorityQueue(pq);
		if (!isPQEmpty(pq)) {
			TreeNode *toMergeWith = shiftFromPriorityQueue(pq);
			const HuffmanPair *hpOne = (const HuffmanPair *)huffmanHeap->value;
			const HuffmanPair *hpTwo = (const HuffmanPair *)toMergeWith->value;
			assert(hpOne && hpTwo && "null!");
			const int priority = hpOne->nbOccurrences + hpTwo->nbOccurrences;
			const HuffmanPair nonLeaf = {'@', priority};
			TreeNode *merged = newTreeNode(&nonLeaf, sizeof(HuffmanPair),
										   huffmanHeap, toMergeWith);
			walkExpert(merged, PREFIXE, prefixPrint, printHuffmanPair);
			addToPriorityQueue(pq, merged, priority);
		}
	}
	printf("\nvvvvvvvvvvvvvvvvvvvvvvvvv\n");

	printLeavesWithBPaths(huffmanHeap);
}

void uncompress(FILE *dest, char *filename);