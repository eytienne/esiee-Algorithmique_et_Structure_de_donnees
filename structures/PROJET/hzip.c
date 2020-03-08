#include "hzip.h"
#include "../../my_c_lib/BinarySequence.h"
#include "../../my_c_lib/PriorityQueue.h"
#include "../../my_c_lib/TreeNode.h"
#include "../../my_c_lib/Vector.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define ASCII_TABLE_SIZE 256

typedef struct HuffmanCode {
	unsigned char c;
	BinarySequence *code;
} HuffmanCode;

void printHuffmanPair(const HuffmanPair *hp) {
	printf("['%c',%u]", hp->c, hp->count);
}

void printHuffmanTree(const HuffmanTree ht) {
	walkExpert(ht, PREFIX, prefixPrint, printHuffmanPair);
}
void freeHuffmanCode(HuffmanCode *hc) {
	freeBinarySequence(hc->code);
	free(hc);
}

int __pickLeaves(const TreeNode *t, void *buffer, const BinarySequence *bs) {
	assert(buffer != NULL);
	Vector *leaves = buffer;
	if (isLeaf(t)) {
		const HuffmanPair *value = t->value;
		HuffmanCode newCode;
		newCode.c = value->c;
		newCode.code = newBinarySequence();
		bscpy(newCode.code, bs);
		add(leaves, &newCode);
	}
	return WALK_SUCCESS;
}

/**
 * INFIX traversal
 * @return : Vector of HuffmanCode
 */
Vector *pickLeaves(const TreeNode *root) {
	Vector *leaves = newVector(sizeof(HuffmanCode));
	walkExpert(root, INFIX, __pickLeaves, leaves);
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
		printf("'%c' -> ", cur->c);
		printBinarySequence(cur->code);
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

typedef struct TraversalInfo {
	int last;
	BinarySequence *traversal;
} TraversalInfo;

int __getTraversal(const TreeNode *tn, void *buffer, const BinarySequence *bs) {
	const HuffmanPair *hp = tn->value;
	TraversalInfo *ti = buffer;
	if (ti->last < bs->length)
		for (int i = ti->last; i < bs->length; i++)
			addZero(ti->traversal);
	else if (ti->last > bs->length) {
		for (int i = ti->last; i > bs->length; i--)
			addOne(ti->traversal);
	}
	ti->last = bs->length;
}

HuffmanTree compress(FILE *src, char *filename) {
	unsigned char buffer[BUFSIZ] = {0};
	int counters[ASCII_TABLE_SIZE] = {0};
	size_t sizeOfText = 0;
	while (!feof(src) &&
		   fread((char *)buffer, sizeof(unsigned char), BUFSIZ, src) > 0) {
		size_t i = 0;
		for (; i < BUFSIZ; i++) {
			if (buffer[i] == '\0')
				break;
			counters[buffer[i]]++;
		}
		sizeOfText += i;
	}

	Vector *v = newVector(sizeof(HuffmanPair));
	for (unsigned int i = 0; i < ASCII_TABLE_SIZE; i++) {
		if (counters[i] > 0) {
			const HuffmanPair toAdd = {(unsigned char)i, counters[i]};
			add(v, &toAdd);
		}
	}
	unsigned char sizeOfTable = size(v);

	qsort(v->values, size(v), sizeof(void *), huffman_pair_cmp);
	HuffmanPair **values = (HuffmanPair **)v->values;

	PriorityQueue *pq = newPriorityQueue(sizeof(TreeNode));
	for (int i = 0; i < size(v); i++) {
		TreeNode *toAdd =
			newTreeNode(values[i], sizeof(HuffmanPair), NULL, NULL);
		addToPriorityQueue(pq, toAdd, values[i]->count);
		free(toAdd);
	}
	freeVector(v, NULL);

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

	FILE *output_stream = fopen(filename, "w");

	fwrite(&sizeOfText, sizeof(size_t), 1, output_stream);
	fwrite(&sizeOfTable, sizeof(unsigned char), 1, output_stream);

	BinarySequence *codes[ASCII_TABLE_SIZE] = {NULL};
	Vector *leaves = pickLeaves(huffmanHeap);
	HuffmanCode *cur = NULL;
	while (forEach(leaves, (const void **)&cur)) {
		fputc(cur->c, output_stream);
		codes[cur->c] = cur->code;
	}

	TraversalInfo ti = {0, newBinarySequence()};
	walkExpert(huffmanHeap, INFIX, __getTraversal, &ti);
	addOne(ti.traversal);

	int bytesToCopy =
		ti.traversal->length / 8 + (ti.traversal->length % 8 != 0);
	fwrite(ti.traversal->bits, sizeof(unsigned char), bytesToCopy,
		   output_stream);
	rewind(src);

	BinarySequence *toWrite = newBinarySequence();
	int j = 0;
	while (!feof(src) &&
		   fread((char *)buffer, sizeof(unsigned char), BUFSIZ, src) > 0) {
		for (size_t i = 0; i < BUFSIZ; i++) {
			if (buffer[i] == '\0')
				break;
			assert(codes[buffer[i]] != NULL);
			bscat(toWrite, codes[buffer[i]]);
			if (toWrite->length * 8 >= BUFSIZ) {
				BinarySequence *reset = newBinarySequence();
				int flushed = toWrite->length / 8;
				fwrite(toWrite->bits, sizeof(unsigned char), flushed,
					   output_stream);
				reset->length = toWrite->length % 8;
				if (toWrite->length % 8 != 0) {
					reset->bits = malloc(1);
					reset->bits[0] = toWrite->bits[flushed];
				}
				freeBinarySequence(toWrite);
				toWrite = reset;
			}
			++j;
		}
	}
	fwrite(toWrite->bits, sizeof(unsigned char),
		   (toWrite->length / 8) + (toWrite->length % 8 != 0), output_stream);
	if (ferror(output_stream))
		printf("Error Writing to myfile.txt\n");
	fclose(output_stream);
	rewind(src);
	return huffmanHeap;
}

void printByte(unsigned char c) {
	BinarySequence *bs = newBinarySequence();
	bs->bits = malloc(1);
	bs->bits[0] = c;
	bs->length = 8;
	printBinarySequence(bs);
	freeBinarySequence(bs);
}

HuffmanTree uncompress(FILE *dest, char *filename) {
	FILE *input_stream = fopen(filename, "r");

	size_t sizeOfText = 0;
	unsigned char sizeOfTable = 0;
	fread(&sizeOfText, sizeof(size_t), 1, input_stream);
	fread(&sizeOfTable, sizeof(unsigned char), 1, input_stream);

	unsigned char *leavesValues = malloc(sizeOfTable + 1);
	fread(leavesValues, sizeof(unsigned char), sizeOfTable, input_stream);
	leavesValues[sizeOfTable] = '\0';

	// huffman tree reconstitution

	HuffmanPair nonLeaf = {'@', 0};

	ShallowStack *parents = newShallowStack();
	TreeNode *ht = newTreeNode(&nonLeaf, sizeof(HuffmanPair), NULL, NULL);
	sstack(parents, ht);
	unsigned char charsPut = 0;
	unsigned char curPath = '\0';
	while (charsPut < sizeOfTable && !isSSEmpty(parents) &&
		   !feof(input_stream)) {
		fread(&curPath, sizeof(unsigned char), 1, input_stream);
		for (size_t i = 0; i < 8 && charsPut < sizeOfTable; i++) {
			if (isSSEmpty(parents) || charsPut >= sizeOfTable)
				break;
			if (curPath & (1 << i)) {
				TreeNode *cur = (TreeNode *)unsstack(parents);
				if (isLeaf(cur)) {
					HuffmanPair *curValue = cur->value;
					assert(curValue != NULL);
					curValue->c = leavesValues[charsPut++];
				}
			} else {
				TreeNode *cur = (TreeNode *)top(parents);
				if (cur->left == NULL) {
					cur->left =
						newTreeNode(&nonLeaf, sizeof(HuffmanPair), NULL, NULL);
					sstack(parents, cur->left);
				} else if (cur->right == NULL) {
					cur->right =
						newTreeNode(&nonLeaf, sizeof(HuffmanPair), NULL, NULL);
					sstack(parents, cur->right);
				} else {
					printf("INCONSISTENT\n");
				}
			}
		}
	}
	free(leavesValues);

	if (charsPut < sizeOfTable) {
		fprintf(stderr,
				"Corrupted hzip file: uncomplete encoding table (%d/%d)\n",
				charsPut, sizeOfTable);
	}

	size_t decoded = 0;
	unsigned char buffer[BUFSIZ] = {0};
	TreeNode *navigator = NULL;
	while (!feof(input_stream) && decoded < sizeOfText) {
		fread(buffer, sizeof(unsigned char), BUFSIZ, input_stream);
		for (size_t i = 0; i < BUFSIZ && decoded < sizeOfText; i++) {
			unsigned char j = 0;
			for (; j < 8 && decoded < sizeOfText; j++) {
				if (navigator == NULL)
					navigator = ht;
				int isOne = buffer[i] & (1 << j);
				if (isOne)
					navigator = navigator->right;
				else
					navigator = navigator->left;
				HuffmanPair *navigatorValue = navigator->value;
				if (isLeaf(navigator)) {
					fputc(navigatorValue->c, dest);
					navigatorValue->count++;
					decoded++;
					navigator = ht;
				}
				// as postfix at the end
				// else {
				// 	navigatorValue->count =
				// 		(navigator->left
				// 			 ? ((HuffmanPair *)navigator->left->value)->count
				// 			 : 0) +
				// 		(navigator->right
				// 			 ? ((HuffmanPair *)navigator->right->value)->count
				// 			 : 0);
				// }
			}
		}
	}

	return ht;
}