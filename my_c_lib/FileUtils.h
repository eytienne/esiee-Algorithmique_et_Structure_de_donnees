#ifndef FILE_UTILS_H
#define FILE_UTILS_H

int direxists(const char *folder);

int fexists(const char *filename);

const char *basename(const char *filename);

char *getPath(const char *filename);

#endif