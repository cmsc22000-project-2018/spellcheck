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

/* returns with pointer */
char** lineparse_file(char* filename)
{
	FILE *f = fopen(filename, "r");

	if (f==NULL) {
		return NULL;
		// when this happens, exit accordingly and restart
	}

	unsigned int n=0;
	size_t i=INITLINE;
	char str[MAXCHAR];		// consider resizing?
	char** lines;
	lines = malloc(i*sizeof(char*));

	char* temp = fgets(str,MAXCHAR,f);
	while(temp != NULL) {
		lines[n]=strdup(str);
		n++;
		if (n >= i) {
			array_resize(lines,i);
		}
		temp = fgets(str,MAXCHAR,f);	// warning - 1 empty line will end this
	}
	while(n<i) {
		lines[n]=NULL;
		n++;
	}

	fclose(f);
	return lines;
}

char* get_word(char* line)
{
	return strtok(line," ,.-\n\t\"\'!?()");	// more?
}

/* source: https://github.com/brenns10/lsh/blob/master/src/main.c */
#define BUFFERSIZE 256
char* read_line()
{
	char input[BUFFERSIZE];
	char* rval;
	memset(input,'\0',BUFFERSIZE);
	char* t = fgets(input,BUFFERSIZE,stdin);

	int n = strlen(input);
	rval = strdup(input);
	if (input[n-1]=='\n')
		rval[n-1] = '\0';

	return rval;
}

#define SPLIT_BUFFER 16	// reconsider
char **split_line(char *line)
{
	char** rval;
	rval = malloc(SPLIT_BUFFER*sizeof(char));
	int i=0;
	for(; rval[i]!=NULL; i++) {
		rval[i]=strtok(line," \t");
	}

	return rval;
}
