#include "../../my_c_lib/FileUtils.h"
#include "hzip.h"
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HZIP_EXTENSION ".hf"

#define MIN_ARGS 3
#define MAX_ARGS 7

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
	char *output_filename = NULL;

	int printTree = -1;
	int printTable = -1;

	int *options[] = {&printTree, &printTable};

	for (int i = 2; i < argc && i <= MAX_ARGS; i++) {
		if (strcmp(argv[i], "-o") == 0) {
			++i;
			if (!(i < argc && i <= MAX_ARGS)) {
				fputs("hzip: -o should be followed by <output_filename>.\n",
					  stderr);
				exit(EXIT_FAILURE);
			}
			char *output_path_given = getPath(argv[i]);
			if (!direxists(output_path_given)) {
				fprintf(stderr,
						"hzip: Invalid output filename '%s' : No such "
						"directory.\n",
						argv[i]);
				exit(EXIT_FAILURE);
			}
			output_filename = argv[i];
		} else if (strncmp(argv[i], "--", 2) == 0) {
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
				fputs("hzip: only one filename can be given.\n", stderr);
				exit(EXIT_FAILURE);
			}
			if (!fexists(argv[i])) {
				fprintf(stderr, "hzip: cannot access '%s': No such file.\n",
						argv[i]);
				exit(EXIT_FAILURE);
			}
			filename = argv[i];
		}
	}
	if (filename == NULL) {
		fputs("hzip: filename should be given.\n", stderr);
		exit(EXIT_FAILURE);
	}

	HuffmanTree ht = NULL;
	if (strcmp(argv[1], "compress") == 0) {
		FILE *src = fopen(filename, "r");
		if (output_filename == NULL) {
			size_t len = strlen(filename);
			output_filename = malloc(len + strlen(HZIP_EXTENSION));
			strcpy(output_filename, filename);
			strcat(output_filename, HZIP_EXTENSION);
		}
		ht = compress(src, output_filename);
		fclose(src);
	} else if (strcmp(argv[1], "uncompress") == 0) {
		if (output_filename == NULL) {
			char *ext = strstr(filename, HZIP_EXTENSION);
			if (ext != NULL) {
				size_t len = ext - filename;
				output_filename = malloc(len);
				strncpy(output_filename, filename, len);
			} else {
				size_t len = strlen(filename);
				const char *toConcat = " (extracted)";
				output_filename = malloc(len + strlen(toConcat));
				strcpy(output_filename, filename);
				output_filename[len] = '\0';
				strcat(output_filename, toConcat);
			}
		}
		FILE *dest = stdout;
		ht = uncompress(dest, output_filename);
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
	return 0;
}
