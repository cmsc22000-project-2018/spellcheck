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

	while(fgets(str,MAXCHAR,f) != 0) {
		lines[n]=strdup(str);
		n++;
		if (n >= i) {
			array_resize(lines,i);
		}
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
	fgets(input,BUFFERSIZE,stdin);

	int n = strlen(input);
	rval = strdup(input);
	if (input[n-1]=='\n')
		rval[n-1] = '\0';

	return rval;
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
/**
	reference: https://github.com/brenns10/lsh/blob/master/src/main.c
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **split_line(char *line)
{
  int bufsize = LSH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFSIZE;
      tokens_backup = tokens;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
		free(tokens_backup);
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, LSH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}


/*
#define SPLIT_BUFFER 16	// reconsider
char **split_line(char *line)
{
	char** rval;
	rval = malloc(SPLIT_BUFFER*sizeof(char));
	for(int i=0; rval[i]!=NULL; i++) {
		rval[i]=strtok(line," ");
	}

	return rval;
}
*/
