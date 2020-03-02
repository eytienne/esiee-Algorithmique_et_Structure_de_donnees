#include "FileUtils.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <direct.h>
#elif defined __linux__
#include <sys/stat.h>
#endif

int direxists(const char *folder) {
	struct stat sb;
	return stat(folder, &sb) == 0 && S_ISDIR(sb.st_mode);
}

int fexists(const char *filename) {
	return !access(filename, F_OK);
}

#ifdef _WIN32
#define FILE_SEPARATOR '\\'
#else
#define FILE_SEPARATOR '/'
#endif

const char *basename(const char *filename) {
	const char *lastSep = strrchr(filename, FILE_SEPARATOR);
	return lastSep ? lastSep : filename;
}

char *getPath(const char *filename) {
	char *lastSep = strrchr(filename, FILE_SEPARATOR);
	size_t len;
	char *path;
	if (lastSep != NULL) {
		len = lastSep - filename;
		path = malloc(len);
		strncpy(path, filename, len);
	} else {
		path = "./";
	}
	return path;
}