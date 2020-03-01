#ifndef HZIP_H
#define HZIP_H

#include "../../my_c_lib/TreeNode.h"
#include <stdio.h>

typedef TreeNode *HuffmanTree;

typedef struct HuffmanPair {
	unsigned char c;
	unsigned int count;
} HuffmanPair;

HuffmanTree compress(FILE *src, char *filename);

HuffmanTree uncompress(FILE *dest, char *filename);

void printHuffmanTree(const HuffmanTree ht);

void printHuffmanTable(const HuffmanTree ht);

#endif