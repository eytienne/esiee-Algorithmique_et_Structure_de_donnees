#include "../../my_c_lib/BinarySequence.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {

	unsigned char test[2];
	test[1] = 17;
	test[0] = 129;
	printf("%hhu\n", test[0] >> 1);
	printf("%hhu\n", test[1] >> 1);

	BinarySequence *bs = newBinarySequence();
	printBinarySequence(bs);
	printf("\n");

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			addZero(bs);
			printBinarySequence(bs);
			printf("\n");
		}
		addOne(bs);
		printBinarySequence(bs);
		printf("\n");

		addZero(bs);
		printBinarySequence(bs);
		printf("\n");
		for (int j = 0; j < 4; j++) {
			addOne(bs);
			printBinarySequence(bs);
			printf("\n");
		}
	}

	BinarySequence *bsCopy = newBinarySequence();

	for (int i = 0; i < 16; i++) {
		shorten(bs);
		printBinarySequence(bs);
		printf("\n");
		if (i == 3) {
			bscpy(bsCopy, bs);
			printBinarySequence(bsCopy);
			printf("\n");
		}
		if (i == 11) {
			printBinarySequence(bsCopy);
			printf(" (copy)\n");
			bscat(bsCopy, bs);
			printBinarySequence(bsCopy);
			printf(" (copy)\n");
		}
		if (i == 14) {
			printBinarySequence(bsCopy);
			printf(" (copy)\n");
			bscat(bsCopy, bs);
			printBinarySequence(bsCopy);
			printf(" (copy)\n");
		}
	}

	freeBinarySequence(bs);
	return 0;
}
