#include "hzip.h"
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MIN_ARGS 3
#define MAX_ARGS 7

#ifdef _WIN32
#define FILE_SEPARATOR '\\'
#else
#define FILE_SEPARATOR '/'
#endif

static int fexists(const char *filename) {
	return !access(filename, F_OK);
}

static char *basename(const char *filename) {
	return strrchr(filename, FILE_SEPARATOR);
}

static int option_cmp(const void *a, const void *b) {
	assert(a && b);
	const int *c = *(int **)a;
	const int *d = *(int **)b;
	assert(c && d);
	return *c - *d;
}

static void printHelp() {
	char *args[] = {"cat", "hzip.help", NULL};
	int ret = execvp(args[0], args);
}

int main(int argc, char *argv[]) {

	FILE *src = NULL;
	if (argc < MIN_ARGS || argc > MAX_ARGS) {
		printHelp();
		exit(EXIT_FAILURE);
	}

	char *filename = NULL;
	char *output_path = NULL;

	int printTree = -1;
	int printTable = -1;

	int *options[] = {&printTree, &printTable};

	for (int i = 2; i < argc && i <= MAX_ARGS; i++) {
		if (strncmp(argv[i], "--", 2) == 0) {
			if (strcmp(argv[i] + 2, "help") == 0) {
				printHelp();
				exit(EXIT_SUCCESS);
			} else if (strcmp(argv[i] + 2, "tree") == 0) {
				printTree = i;
			} else if (strcmp(argv[i] + 2, "table") == 0) {
				printTable = i;
			} else {
				fprintf(
					stderr,
					"hzip: '%s' is not a valid option. See 'hzip --help'.\n",
					argv[i] + 2);
				exit(EXIT_FAILURE);
			}
		} else {
			if (filename != NULL) {
				fputs("hzip: only one filename can be given\n", stderr);
				exit(EXIT_FAILURE);
			}
			if (!fexists(argv[i])) {
				fprintf(stderr, "hzip: cannot access '%s': No such file\n",
						argv[i]);
				exit(EXIT_FAILURE);
			}
			filename = argv[i];
		}
	}
	if (filename == NULL) {
		fputs("hzip: filename should be given\n", stderr);
		exit(EXIT_FAILURE);
	}

	size_t len = strlen(filename);
	char *output =
		malloc(len + 4); // 4 = length of ".hf" + 1 for the null-terminator
	strcpy(output, filename);
	strcat(output, ".hf");

	HuffmanTree ht = NULL;
	if (strcmp(argv[1], "compress") == 0) {
		FILE *src = fopen(filename, "r");
		ht = compress(src, output_path);
		fclose(src);
	} else if (strcmp(argv[1], "uncompress") == 0) {
		FILE *dest = stdout;
		ht = uncompress(dest, output_path);
		fclose(dest);
	} else {
		fprintf(stderr,
				"hzip: '%s' is not a hzip command. See 'hzip --help'.\n",
				argv[1]);
		exit(EXIT_FAILURE);
	}

	qsort(options, sizeof(options) / sizeof(int *), sizeof(int *), option_cmp);
	for (int i = 0; i < sizeof(options) / sizeof(int *); i++) {
		if (*options[i] < 0)
			continue;

		if (options[i] == &printTree) {
			printHuffmanTree(ht);
		} else if (options[i] == &printTable) {
			printHuffmanTable(ht);
		}
	}

	freeTreeNode(ht, NULL);
	free(output);
	return 0;
}
