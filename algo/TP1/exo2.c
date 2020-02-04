#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int isEven();

int main(int argc, char const *argv[]) {

	// a)
	assert(isEven(4));
	assert(!isEven(5));

	// b)
	if (argc != 2) {
		fprintf(stderr, "Fournissez un nombre en argument !\n");
		return -1;
	}
	int n = atoi(argv[1]);
	printf("Diviseurs de %d :\n", n);
	for (int i = 1; i <= n / 2; i++)
		if (n % i == 0)
			printf("%d\n", i);
	printf("%d\n", n);

	return 0;
}

// a)
int isEven(int n) { return n % 2 == 0; }