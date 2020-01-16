#include <stdio.h>
#include <stdlib.h>

int mode1();
int mode2();

void printResult(int arr[], int size);

int main(int argc, char const *argv[]) { return mode2(); }

int mode1() {
	int size = 0;
	printf("Quelle taille pour le tableau ? ");
	scanf("%d", &size);
	if (size * sizeof(int) > SIZE_MAX) {
		fprintf(stderr, "La taille saisie ne peut pas être supérieure à %ld",
				__INT_MAX__ / sizeof(int));
		return -1;
	}
	int *values = (int *)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		printf("Valeur n°%d : ", i + 1);
		scanf("%d", values + i);
	}
	printResult(values, size);
	return 0;
}

void printResult(int arr[], int length) {
	printf("Résultat : \n");
	for (int i = 0; i < length; i++) {
		printf("%d\n", arr[i]);
	}
}

int mode2() {
	int length = 0;
	int currentValue = 0;
	int *values = NULL;
	while (printf("Valeur n°%d : ", length + 1) && scanf("%d", &currentValue) &&
		   currentValue > 0) {
		int newLength = length + 1;
		int *newValues = (int *)realloc(values, newLength * sizeof(int));
		if (newValues == NULL) {
			fprintf(stderr,
					"Erreur à l'augmentation de la taille du tableau !");
			return -1;
		}
		values = newValues;
        length = newLength;
		values[length - 1] = currentValue;
	}
    printResult(values, length);
    return 0;
}
