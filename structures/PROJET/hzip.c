#include "hzip.h"
#include "../../my_c_lib/PriorityQueue.h"
#include "../../my_c_lib/TreeNode.h"
#include "../../my_c_lib/Vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_MAX 1000
#define ASCII_TABLE_SIZE 256

typedef struct HuffmanCode {
	unsigned char c;
	BinaryPath *code;
} HuffmanCode;

void printHuffmanPair(const HuffmanPair *hp) {
	printf("['%c',%u]", hp->c, hp->count);
}

void printHuffmanTree(const HuffmanTree ht) {
	walkExpert(ht, PREFIXE, prefixPrint, printHuffmanPair);
}
void freeHuffmanCode(HuffmanCode *hc) {
	freeBinaryPath(hc->code);
	free(hc);
}

int __pickLeaves(const TreeNode *t, void *buffer, const BinaryPath *bp) {
	assert(buffer != NULL);
	Vector *leaves = buffer;
	if (isLeaf(t)) {
		const HuffmanPair *value = t->value;
		HuffmanCode newCode;
		newCode.c = value->c;
		newCode.code = newBinaryPath();
		bpcpy(newCode.code, bp);
		add(leaves, &newCode);
	}
	return WALK_SUCCESS;
}

/**
 * @return : Vector of HuffmanCode
 */
Vector *pickLeaves(const TreeNode *root) {
	Vector *leaves = newVector(sizeof(HuffmanCode));
	walkExpert(root, PREFIXE, __pickLeaves, leaves);
	return leaves;
}

int huffman_code_cmp(const void *a, const void *b) {
	assert(a && b);
	const HuffmanCode *c = *(const HuffmanCode **)a;
	const HuffmanCode *d = *(const HuffmanCode **)b;
	assert(c && d);
	return c->c > d->c ? 1 : c->c < d->c ? -1 : 0;
}

void printHuffmanTable(const HuffmanTree ht) {
	Vector *leaves = pickLeaves(ht);
	qsort(leaves->values, size(leaves), sizeof(void *), huffman_code_cmp);
	const HuffmanCode *cur = NULL;
	while (forEach(leaves, (const void **)&cur)) {
		printf("'%c' %d -> ", cur->c, cur->c);
		printBinaryPath(cur->code);
		printf("\n");
	}
	freeVector(leaves, (void (*)(void *))freeHuffmanCode);
}

void printPQ(const PriorityQueue *pq) {
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
	return d->count - c->count;
}

HuffmanTree compress(FILE *src, char *filename) {
	unsigned char buffer[TAILLE_MAX] = {0};
	int counters[ASCII_TABLE_SIZE] = {0};

	while (!feof(src) && fgets((char *)buffer, TAILLE_MAX, src) != NULL) {
		int i = 0;
		while (i < TAILLE_MAX) {
			if (buffer[i] == '\0')
				break;
			printf("%c", buffer[i]);
			counters[buffer[i]]++;
			if (buffer[i] == '\n')
				break;
			i++;
		}
	}
	printf("\n----------------------\n");

	Vector *v = newVector(sizeof(HuffmanPair));
	for (unsigned int i = 0; i < ASCII_TABLE_SIZE; i++) {
		if (counters[i] > 0) {
			const HuffmanPair toAdd = {(unsigned char)i, counters[i]};
			add(v, &toAdd);
		}
	}
	qsort(v->values, size(v), sizeof(void *), huffman_pair_cmp);
	// printVectorOfHP(v);

	HuffmanPair **values = (HuffmanPair **)v->values;

	PriorityQueue *pq = newPriorityQueue(sizeof(TreeNode));
	for (int i = 0; i < size(v); i++) {
		TreeNode *toAdd =
			newTreeNode(values[i], sizeof(HuffmanPair), NULL, NULL);
		addToPriorityQueue(pq, toAdd, values[i]->count);
		free(toAdd);
	}
	freeVector(v, NULL);
	// printPQ(pq);

	TreeNode *huffmanHeap = NULL;
	while (!isPQEmpty(pq)) {
		huffmanHeap = shiftFromPriorityQueue(pq);
		if (!isPQEmpty(pq)) {
			TreeNode *toMergeWith = shiftFromPriorityQueue(pq);
			const HuffmanPair *hpOne = (const HuffmanPair *)huffmanHeap->value;
			const HuffmanPair *hpTwo = (const HuffmanPair *)toMergeWith->value;
			assert(hpOne && hpTwo);
			const int priority = hpOne->count + hpTwo->count;
			const HuffmanPair nonLeaf = {'@', priority};
			TreeNode *merged = newTreeNode(&nonLeaf, sizeof(HuffmanPair),
										   huffmanHeap, toMergeWith);
			addToPriorityQueue(pq, merged, priority);
			free(merged);
		}
	}
	freePriorityQueue(pq, NULL);

	return huffmanHeap;
}

HuffmanTree uncompress(FILE *dest, char *filename){

}