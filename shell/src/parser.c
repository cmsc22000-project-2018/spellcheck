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
	char* lines;
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
		lines[n]=strdup(str);
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

/* source: https://github.com/brenns10/lsh/blob/master/src/main.c */

#define LSH_RL_BUFSIZE 1024
/**
   @brief Read a line of input from stdin.
   @return The line from stdin.
 */
char *lsh_read_line(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **lsh_split_line(char *line)
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
