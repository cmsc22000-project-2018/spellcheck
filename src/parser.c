#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

#define MAXCHAR 1025	// limit is 1024
#define INITLINE 200
#define READ_BUFFERSIZE 256
#define LSH_TOK_BUFFERSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

/* Parsing Functions for Parsing Input Files */

/* returns with pointer to array of strings, each of which represent a line in a given file */
/* current limit to each string is 1000 characters */
/* return NULL if file could not be opened */
char** parse_file(char* filename)
{
	FILE *f = fopen(filename, "r");

	if (f == NULL) {
		return NULL;
	}

    // initialization
	int n = 0;
	int i = INITLINE;
	char str[MAXCHAR];
	char** lines;
	lines = calloc(i, sizeof(char*));
	if (lines == NULL) {
		fprintf(stderr, "lineparse_file: malloc failed\n");
		exit(0);
	}

    // read each line into a string. This size is currently limited at 1025 lines (1024, including terminating char).
    // resize if necessary while reading file
	while(fgets(str, MAXCHAR, f) != 0) {
		lines[n] = strdup(str);
		n++;
	}
	while(n < i) {  // initialize the rest of the lines, which do not hold new characters
		lines[n] = NULL;
		n++;
	}

	fclose(f);
	return lines;
}

/* Parsing functions for parsing command line inputs */
/* read a command line and return a string */
char* parse_read_line()
{
	char input[READ_BUFFERSIZE];
	char* rval;
	memset(input, '\0', READ_BUFFERSIZE);
	char* i = fgets(input, READ_BUFFERSIZE, stdin);
    assert(i != NULL);      // even empty lines will probably have '\0; test to see if works

	int n = strlen(input);
	rval = strdup(input);
	if (input[n-1] == '\n')
		rval[n-1] = '\0';

	return rval;
}

/*
   reference: https://github.com/brenns10/lsh/blob/master/src/main.c
   Split a line into tokens (very naively), and return null-terminated array of tokens.
 */
char **parse_split_line(char *line)
{
  int bufsize = LSH_TOK_BUFFERSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

    // convert input line into an array of strings, each of which represents a line. similar to argc argv in main
  token = strtok(line, LSH_TOK_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= bufsize) {
      bufsize += LSH_TOK_BUFFERSIZE;
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