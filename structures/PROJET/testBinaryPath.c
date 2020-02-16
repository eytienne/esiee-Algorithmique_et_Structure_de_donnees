#include "../../my_c_lib/BinaryPath.h"
#include <stdio.h>

int main(int argc, char const *argv[]) {
	// for (unsigned char i = 0; i < 10; i++) {
	// 	for (int j = 7; j >= 0; j--) {
	// 		printf("%hhu ", ((i >> j) & 1) != 0);
	// 	}
	// 	printf("\n");
	// }

	unsigned char test[2];
	test[1] = 17;
	test[0] = 129;
	printf("%hhu\n", test[0] >> 1);
	printf("%hhu\n", test[1] >> 1);

	BinaryPath *bp = newBinaryPath();
	printBinaryPath(bp);

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			goToLeft(bp);
			printBinaryPath(bp);
		}
		goToRight(bp);
		printBinaryPath(bp);

		goToLeft(bp);
		printBinaryPath(bp);
		for (int j = 0; j < 4; j++) {
			goToRight(bp);
			printBinaryPath(bp);
		}
	}

	for (int i = 0; i < 16; i++) {
		goBack(bp);
		printBinaryPath(bp);
	}

	return 0;
}
