#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	printf("Bonjour !\nVeuillez saisir le premier nombre : ");
	int n1, n2;
	scanf("%d", &n1);
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {
	}
	printf("Veuillez saisir le deuxième nombre : ");
    scanf("%d", &n2);
	while ((c = getchar()) != '\n' && c != EOF) {
	}
	printf("Quelle opération appliquer : ");
	char op;
	scanf("%1c", &op);
	switch (op) {
	case '+':
		printf("%d + %d = %d\n", n1, n2, n1 + n2);
		break;
	case '-':
		printf("%d - %d = %d\n", n1, n2, n1 - n2);
		break;
	case '*':
		printf("%d * %d = %d\n", n1, n2, n1 * n2);
		break;
	case '/':
		printf("%d / %d = %g\n", n1, n2, (float)n1 / n2);
		break;
	default:
        printf("Opération invalide !\n");
		break;
	}
	return 0;
}
