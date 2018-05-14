#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parser.h"

#define MAXCHAR 1025	// limit is 1024
#define INITLINE 50
#define BUFFERSIZE 256
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

/* helper function: resizes array in lineparse if given file is too large */
int parse_array_resize(char** array, size_t *len)
{
    assert(*len > 0);
    *len = 2 * (*len);

    char** new = malloc(sizeof(char*) * (*len));
    memcpy(new, array, (*len) * sizeof(char*));

    array = new;
    size_t i = *len / 2;
    for ( ; i < *len; i++) array[i] = NULL;

    return EXIT_SUCCESS;
}

/* returns with pointer to array of strings, each of which represent a line in a given file */
/* current limit to each string is 1000 characters */
/* return NULL if file could not be opened */
char** parse_file(char* filename)
{
	FILE *f = fopen(filename, "r");

	if (f == NULL) {
		return NULL;
	}

	unsigned int n = 0;
	size_t i = INITLINE;
	char str[MAXCHAR];		// consider resizing?
	char** lines;
	lines = malloc(i * sizeof(char*));
	if (lines == NULL) {
		fprintf(stderr, "lineparse_file: malloc failed\n");
		exit(0);
	}

	while(fgets(str, MAXCHAR, f) != 0) {
        if (i < n) parse_array_resize(lines, &i);
		lines[n] = strdup(str);
		n++;
	}

	while(n < i) {
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
/*    char input[BUFFERSIZE];
	char* rval;
	memset(input, '\0', BUFFERSIZE);
	char* i = fgets(input, 128, stdin);
    assert(i != NULL);      // even empty lines will have '\0';

	int n = strlen(input);
	rval = strdup(input);
	if (input[n-1] == '\n')
		rval[n-1] = '\0';

	return rval; */
    char input[BUFFERSIZE];
    int i = scanf("%s", input);
    assert(!(i < 0));

    char* rval = strdup(input);

    return rval;
}

/*
   reference: https://github.com/brenns10/lsh/blob/master/src/main.c
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **parse_split_line(char *line)
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
