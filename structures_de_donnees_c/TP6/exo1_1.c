#include "pgm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void throwInvalidPGMFile();

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		fputs("Put the filename as argument\n", stderr);
		exit(1);
	}

	FILE *pFile;
	pFile = fopen(argv[1], "rb");
	if (pFile == NULL) {
		fputs("File error\n", stderr);
		exit(1);
	}

	PGMInfos *infos = getPGMInfos(pFile);
	if (infos == NULL) {
		throwInvalidPGMFile();
	} else {
		printf("Valid PGM file : dimensions : %d %d\n", infos->width,
			   infos->height);
	}

	fclose(pFile);
	return 0;
}

void throwInvalidPGMFile() {
	fputs("Invalid PGM file!\n", stderr);
	exit(2);
}
