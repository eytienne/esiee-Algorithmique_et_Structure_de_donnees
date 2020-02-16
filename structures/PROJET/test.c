#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char string[5] = "abcd";
	int value = 99 << 8 | 'c' << 0;
	printf("%s\n", string);
	memcpy(string, &value, sizeof(int));
	printf("%s\n", string);
	return 0;
}