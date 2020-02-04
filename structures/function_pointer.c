#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void helloWorld(int cpt) {
	printf("Hello world! %d\n", cpt);
	if (cpt++ < 3)
		helloWorld(cpt);
}

void delay(int delay, void (*func)(int), int param) {
	sleep(delay);
	func(param);
}

int main(int argc, char const *argv[]) {
	delay(1, helloWorld, 0);
	return 0;
}
