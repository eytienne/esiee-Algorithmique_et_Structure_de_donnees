#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

const float CMPERINCH = 2.54;

void conversion() {
	printf("Entrez une longueur : ");
	char prompted;
	float value;
	scanf("%f%s", &value, &prompted);
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
	prompted = toupper(prompted);
	float cm =
			  (prompted == 'P' ? value * CMPERINCH
							   : prompted == 'M' ? value * 100
												 : prompted == 'C' ? value : 0),
		  pc = (prompted == 'P' ? value : cm / CMPERINCH);
	printf("%g p = %g cm\n", pc, cm);
}

int main(char *argv, int argc) { conversion(); }