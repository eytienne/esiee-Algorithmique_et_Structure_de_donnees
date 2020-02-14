#include "compression.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *src = NULL;
	src = fopen("text.txt", "r");
	compress(src, "compressed.bin");
	fclose(src);
	return 0;
}
