#include "pgm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
	if (argc != 3) {
		fputs("Put the filenames as arguments\n", stderr);
		exit(1);
	}

	FILE *pFile;
	pFile = fopen(argv[1], "rb");
	if (pFile == NULL) {
		fputs("File error\n", stderr);
		exit(1);
	}

	int ext = extractPGM(pFile, argv[2], 80, 80, 40, 40);
	if (ext != 0) {
		fputs("Extraction failed!\n", stderr);
	} else {
		printf("Extraction succeeded!\n");
	}

	fclose(pFile);
	return 0;
}
