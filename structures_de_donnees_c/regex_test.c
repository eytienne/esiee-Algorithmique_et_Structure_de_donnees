#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	int err;
	regex_t preg;
	const char *str_request = ".";
	const char *str_regex = "([0-9]+.?|.[0-9]+|[0-9]+.[0-9]+)";

	err = regcomp(&preg, str_regex, REG_EXTENDED);
	if (err == 0) {
		int match;
		size_t nmatch = 0;
		regmatch_t *pmatch = NULL;

		nmatch = preg.re_nsub;
		pmatch = malloc(sizeof(*pmatch) * nmatch);
		if (pmatch) {
			match = regexec(&preg, str_request, nmatch, pmatch, 0);
			regfree(&preg);
			if (match == 0) {
				char *site = NULL;
				int start = pmatch[0].rm_so;
				int end = pmatch[0].rm_eo;
				size_t size = end - start;

				site = malloc(sizeof(*site) * (size + 1));
				if (site) {
					strncpy(site, &str_request[start], size);
					site[size] = '\0';
					printf("%s\n", site);
					free(site);
				}
			} else if (match == REG_NOMATCH) {
				printf("%s n'est pas un double\n", str_request);
			}
		}
	}
	return (EXIT_SUCCESS);
}