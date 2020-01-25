#include <stdio.h>
#include <stdlib.h>

void call(void (*func)(const void *), void *param) { func(param); }

void display(const void *i) { printf("%d\n", *(int *)i); }

int main(int argc, char const *argv[]) {
	int ii = 23;
	call(display, &ii);
	return 0;
}
