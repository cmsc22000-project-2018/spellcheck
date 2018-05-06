#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parser.h"

#define MAXCHAR 1000	// maximum characters in a line?
#define INITLINE 50

void array_resize(char** array, size_t alen)
{
	alen = 2*alen;
	array=realloc(array,alen*sizeof(char*));
}

char** lineparse_file(char* filename, int* numline, int* size)
{
	int n=0;
	size_t i=INITLINE;

	char str[MAXCHAR];
	char* lines[i];
	lines=malloc(i*sizeof(char*));
	if (lines == NULL) {
		fprintf(stderr,"parse_file: malloc failed\n");
		exit(0);
	}
	
	FILE *f = fopen(filename, "r");

	if (f==NULL) {
		return NULL;
	}

	while(fgets(str,MAXCHAR,f) != NULL) {
		array[n]=strdup(str);
		n++;
		if (n=>i) {
			array_resize(lines,i);
		}
	}

	fclose(f);
	size=i;			// for freeing purposes?
	return lines;
}

char* get_word(char* line)
{
	return strtok(line," ,.-\n\t\"\'");
}
