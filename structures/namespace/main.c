#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char *src = "0123456789";
	char *str2 = NULL;
	char *str3 = (char *)malloc(1);
	char *str4 = (char *)malloc(0);
	char *str42 = (char *)malloc(0);
	char str5[] = "0003456788";
	strcpy(str2, src);
	strcpy(str3, src);
	strcpy(str4, src);
	strcpy(str5, src);
	printf("str2: %s\n", str2);
	printf("str3: %s\n", str3);
	printf("str4: %s, str42: %s\n", str4, str42);
	printf("str5: %s\n", str5);
	return 0;
}