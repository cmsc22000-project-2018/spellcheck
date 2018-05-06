#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parser.h"

/* adapted from */

void next_token()
{
	size_t linemax = 2048;
	char* token = NULL;
	char buffer[linemax];

	if (token != NULL) {
		token = strtok(NULL, " \t\n");
	}

	while (token == NULL) {
		char* s = fgets(buffer, linemax, stdin);
		if (s==NULL) {
		
		assert(feof(stdin));
		break;
		}

		token = strtok(s, SEP);
	}
	
}

int read_string(char** s)
{
	*s = token;
	return token != NULL;
}
