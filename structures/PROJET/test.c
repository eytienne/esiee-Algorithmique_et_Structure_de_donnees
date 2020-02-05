#include <openssl/md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void md5_hash_from_string(char *string, char *hash) {
	int i;
	char unsigned md5[MD5_DIGEST_LENGTH] = {0};

	MD5((const unsigned char *)string, strlen(string), md5);

	for (i = 0; i < MD5_DIGEST_LENGTH; i++) {
		sprintf(hash + 2 * i, "%02x", md5[i]);
	}
}

int main() {
	char string[255] = "a";
	char md5_hash[2 * MD5_DIGEST_LENGTH + 1] = "";
	md5_hash_from_string(string, md5_hash);
	printf("%s\n", md5_hash);

	return 0;
}