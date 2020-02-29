#ifndef COMPRESSION_H
#define COMPRESSION_H

#include "../../my_c_lib/TreeNode.h"
#include <stdio.h>

typedef TreeNode *HuffmanTree;

HuffmanTree compress(FILE *src, char *filename);

void uncompress(FILE *dest, char *filename);

#endif