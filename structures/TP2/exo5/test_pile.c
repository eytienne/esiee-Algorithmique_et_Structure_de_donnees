
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../../my_c_lib/ShallowStack.h"

int main() {

	ShallowStack *pile = newShallowStack();

	assert(isSSEmpty(pile));

	char *toStack = "ABC";
	sstack(pile, toStack);
	assert(!isSSEmpty(pile));
	assert(*(char *)top(pile) == 'A');

	sstack(pile, toStack + 1);
	assert(!isSSEmpty(pile));
	assert(*(char *)top(pile) == 'B');

	sstack(pile, toStack + 2);
	assert(!isSSEmpty(pile));
	assert(*(char *)top(pile) == 'C');

	unsstack(pile);
	assert(!isSSEmpty(pile));
	assert(*(char *)top(pile) == 'B');
	unsstack(pile);
	assert(!isSSEmpty(pile));
	assert(*(char *)top(pile) == 'A');
	unsstack(pile);
	assert(isSSEmpty(pile));

	printf("Tests passed!\n");
	freeShallowStack(pile);

	return EXIT_SUCCESS;
}
