#include "compression.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	FILE *src = NULL;
	if (argc != 2) {
		fputs("Give the file to test compression with as argument!\n", stderr);
		exit(EXIT_FAILURE);
	}
	char *filename = argv[1];
	src = fopen(filename, "r");
	size_t len = strlen(filename);
	char *output = malloc(len + 4);
	strcpy(output, filename);
	strcat(output, ".bin");
	compress(src, output);
	fclose(src);
	return 0;
}
