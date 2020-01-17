#include <stdio.h>
#include <stdlib.h>

int mode1();
int mode2();
int mode3();

void printResult(int arr[], int size);

int main(int argc, char const *argv[]) { return mode3(); }

int mode1() {
	int size = 0;
	printf("Quelle taille pour le tableau ? ");
	scanf("%d", &size);
	if (size * sizeof(int) > __INT_MAX__) {
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
		length += 1;
		int *newValues = (int *)realloc(values, length * sizeof(int));
		if (newValues == NULL) {
			fprintf(stderr,
					"Erreur à l'augmentation de la taille du tableau !");
			return -1;
		}
		values = newValues;
		values[length - 1] = currentValue;
	}
	printResult(values, length);
	return 0;
}

int mode3() {
	int length = 0;
	int *values = NULL;
	int currentIndex = 0;
	while (1) {
		printf("Index : ");
		scanf("%d", &currentIndex);
		if (currentIndex < 0)
			break;
		if (currentIndex >= length) {
			int newLength = currentIndex + 1;
			int *newValues = (int *)realloc(values, newLength * sizeof(int));
			if (newValues == NULL) {
				fprintf(stderr,
						"Erreur à l'augmentation de la taille du tableau !");
				return -1;
			}
			values = newValues;
			for (int i = length; i < newLength; i++)
				values[i] = 0;
			length = newLength;
		}
		int currentValue = 0;
		printf("Valeur : ");
		scanf("%d", &currentValue);
		values[currentIndex] = currentValue;
	}
	printResult(values, length);
	return 0;
}