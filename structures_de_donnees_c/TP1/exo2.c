#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR 100
const float CMPERINCH = 2.54;

/* coucou */
int toupper(int c) { return c >= 'a' && c <= 'z' ? c - 32 : c; }

int main() {
	char *prompted = (char *)malloc(MAX_CHAR);
	scanf("%s", prompted);
	char current;
	int i = 0;
	while (current = prompted[i]) {
		if (current == '.') {
			prompted[i + 1] = '\0';
			break;
		}
		prompted[i] = toupper(current);
		++i;
	}
	printf("%s\n", prompted);
}