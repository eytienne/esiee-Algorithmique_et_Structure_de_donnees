#include "../../my_c_lib/ShallowStack.h"
#include <assert.h>

int main(int argc, char const *argv[]) {
	ShallowStack *s1 = newShallowStack();
	ShallowStack *s2 = newShallowStack();
	int values[] = {1, -2, 3, 10};
	assert(isSSEmpty(s1) && isSSEmpty(s2));
	sstack(s1, &values[0]);
	sstack(s2, &values[3]);
	assert(*(int *)top(s1) == 1 && *(int *)top(s2) == 10);
	sstack(s1, &values[1]);
	sstack(s2, &values[2]);
	assert(*(int *)top(s1) == -2 && *(int *)top(s2) == 3);
    unsstack(s1);
    unsstack(s2);
	assert(*(int *)top(s1) == 1 && *(int *)top(s2) == 10);
    unsstack(s1);
    unsstack(s2);
	assert(isSSEmpty(s1) && isSSEmpty(s2));
    freeShallowStack(s1);
    freeShallowStack(s2);
	return 0;
}
