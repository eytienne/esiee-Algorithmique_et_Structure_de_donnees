#include "pgm.h"
#include <stdio.h>
#include <string.h>

const size_t PGMMINBUFSIZE = 100;

char *resizeStringBuffer(char *buffer, size_t n);

PGMInfos *getPGMInfos(FILE *pFile) {
	char *readBuffer = resizeStringBuffer(NULL, 4);
	fgets(readBuffer, 4, pFile);
	sscanf(readBuffer, "%s", readBuffer);

	if (strcmp(readBuffer, "P5") != 0)
		goto invalidPGM;

	readBuffer = resizeStringBuffer(readBuffer, PGMMINBUFSIZE);
	fgets(readBuffer, PGMMINBUFSIZE, pFile);

	int i;
	for (i = 0; i < PGMMINBUFSIZE && readBuffer[i] != ' '; i++)
		if (readBuffer[i] < '0' || readBuffer[i] > '9')
			goto invalidPGM;
	++i;
	for (; i < PGMMINBUFSIZE && readBuffer[i] != '\n' && readBuffer[i] != '\0';
		 i++)
		if (readBuffer[i] < '0' || readBuffer[i] > '9')
			goto invalidPGM;

	int width = -1, height = -1;
	sscanf(readBuffer, "%d %d", &width, &height);

	readBuffer = resizeStringBuffer(readBuffer, PGMMINBUFSIZE);
	fgets(readBuffer, PGMMINBUFSIZE, pFile);
	for (i = 0;
		 i < PGMMINBUFSIZE && readBuffer[i] != '\n' && readBuffer[i] != '\0';
		 i++)
		if (readBuffer[i] < '0' || readBuffer[i] > '9')
			goto invalidPGM;
	int testRange = -1;
	sscanf(readBuffer, "%d", &testRange);

	if (testRange < 0 || testRange > 255)
		goto invalidPGM;

	unsigned char greyMaxLevel = (unsigned char)testRange;

	PGMInfos *ret = (PGMInfos *)malloc(sizeof(PGMInfos));
	ret->width = width;
	ret->height = height;
	ret->maxLevel = greyMaxLevel;
	fseek(pFile, 0, SEEK_SET);
	free(readBuffer);
	return ret;

invalidPGM:
	fseek(pFile, 0, SEEK_SET);
	free(readBuffer);
	return NULL;
}

char *resizeStringBuffer(char *buffer, size_t n) {
	char *newBuffer = realloc(buffer, n);
	if (newBuffer == NULL) {
		fputs("Reading buffer reallocation failed!\n", stderr);
		exit(2);
	}
	return newBuffer;
}

int extractPGM(FILE *from, const char *to, int x, int y, int width,
			   int height) {
	PGMInfos *infos = getPGMInfos(from);
	if (infos == NULL)
		return -1;
	FILE *toFile = fopen(to, "wb");
	if (toFile == NULL)
		return -2;

	fputs("P5\n", toFile);
	fprintf(toFile, "%d %d\n", width, height);
	fprintf(toFile, "%d\n", infos->maxLevel);

	char *currentLine = (char *)malloc(PGMMINBUFSIZE);

	for (int i = 0; i < 3; i++) { // skip pgm header
		fgets(currentLine, PGMMINBUFSIZE, from);
	}

	currentLine = resizeStringBuffer(currentLine, infos->width + 1);
	fseek(from, y * infos->width, SEEK_CUR);
	char *blankFill = NULL;
	for (int i = 0; i < height; i++) {
		if (!feof(from)) {
			fread(currentLine, 1, infos->width, from);
			char *portionToCopy = (char *)malloc(width);
			memcpy(portionToCopy, currentLine + x, width);
			fwrite(portionToCopy, 1, width, toFile);
		} else {
			if (blankFill == NULL) {
				blankFill = calloc(width, 1);
				if(blankFill == NULL)
					return -3;
			}
			fwrite(blankFill, 1, width, toFile);
		}
	}

	fclose(toFile);
	return 0;
}