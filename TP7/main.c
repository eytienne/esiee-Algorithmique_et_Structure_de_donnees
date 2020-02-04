#include "lca.h"
#include "sda.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void exo2();
void printLCA(const LCA *sda);

int main(int argc, char const *argv[]) {
	exo2();
	return 0;
}

void exo2() {
	SDA *sda = SDAFunc.new();
	assert(sda != NULL);
	assert(sda->first == NULL);
	assert(SDAFunc.isEmpty(sda));

	Key key = "first";
	int val = 20;
	SDAFunc.put(sda, key, &val);
	printLCA(sda);
	key = "second";
	val = 30;
	SDAFunc.put(sda, key, &val);
	printLCA(sda);

	assert(SDAFunc.containsKey(sda, "first"));
	assert(!SDAFunc.containsKey(sda, "third"));

	Value v1 = SDAFunc.get(sda, "first");
	assert(v1 != NULL);
	printf("get : %d\n", *v1);
	assert(*v1 == 20);
	*v1 = 40;
	printLCA(sda);

	SDAFunc.clear(sda);
	assert(sda->first == NULL);
	printLCA(sda);
}

void printLCA(const SDA *sda) {
	LCACell *current = sda->first;
	printf("----------------------\n");
	while (current != NULL) {
		printf("%s : %d\n", current->key, *current->value);
		current = current->next;
	}
}