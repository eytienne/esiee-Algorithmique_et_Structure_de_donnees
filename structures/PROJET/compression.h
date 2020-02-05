#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdio.h>

void compress(FILE *src, char *filename);

void uncompress(FILE *dest, char *filename);

#endif