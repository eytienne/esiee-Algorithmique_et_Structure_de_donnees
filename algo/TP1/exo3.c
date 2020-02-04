#include <assert.h>
#include <stdlib.h>

typedef struct HeureS {
	int h;
	int min;
} Heure;

int factorielle(int n);

int pgcd(int a, int b);

int ppcm(int a, int b);

Heure *minutesToHour(int min);

void testA();

void testB();

int main(int argc, char const *argv[]) {
	testA();
	testB();
	return 0;
}

void testA() {

	assert(factorielle(0) == 1);
	assert(factorielle(5) == 120);

	assert(pgcd(30, 45) == 15);

	assert(ppcm(30, 45) == 90);
}

void testB() {
	Heure *hToTest = minutesToHour(85);
	assert(hToTest->h == 1);
	assert(hToTest->min == 25);
}

int factorielle(int n) {
	int ret = 1;
	for (int i = 2; i <= n; i++)
		ret *= i;
	return ret;
}

int pgcd(int a, int b) {
	while (b != 0) {
		int t = b;
		b = a % b;
		a = t;
	}
	return a;
}

int ppcm(int a, int b) { return abs(a * b) / pgcd(a, b); }

Heure *minutesToHour(int min) {
	Heure *hh = (Heure *)malloc(sizeof(Heure));
	hh->h = min / 60;
	hh->min = min % 60;
	return hh;
}