#ifndef PGM_H
#define PGM_H

#include <stdlib.h>
#include <stdio.h>

typedef struct PGMInfos {
	int width, height;
	unsigned char maxLevel;
} PGMInfos;

PGMInfos *getPGMInfos(FILE *file);
int extractPGM(FILE *from, const char* to, int x, int y, int width, int height);

#endif