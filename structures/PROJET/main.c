#include "compression.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *src = NULL;
	if (argc != 2) {
		fputs("Give the file to test compression with as argument!\n", stderr);
		exit(EXIT_FAILURE);
	}
	src = fopen(argv[1], "r");
	compress(src, "compressed.bin");
	fclose(src);
	return 0;
}
