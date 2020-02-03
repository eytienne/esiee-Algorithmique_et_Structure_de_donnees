#include "lca.h"
#include "sda.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	LCA *sda = SDAFunc.new();
	assert(sda != NULL);
	assert(sda->first == NULL);
	assert(SDAFunc.isEmpty(sda));

	Key key = "first";
	int val = 20;
	SDAFunc.put(sda, key, &val);
	key = "second";
	val = 30;
	SDAFunc.put(sda, key, &val);
	printf("%s : %d\n", sda->first->key, *sda->first->value);

	return 0;
}
