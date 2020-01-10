#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void play();

int main() {
	srand(time(NULL)); // Initialization, should only be called once.
	play();
}

void play() {
	int toGuess = rand() % 99 + 1;
	int try
		= -1;
	int nbTries = 0;
	printf("Devinez ! ");
	while (try != toGuess) {
		scanf("%d", &try);
		if (try < toGuess)
			printf("Plus grand !\n");
		else if (try > toGuess)
			printf("Plus petit !\n");
		++nbTries;
	}
	printf("Deviné en %d coup(s) !\n", nbTries);
}