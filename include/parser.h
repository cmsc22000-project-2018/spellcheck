#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parser.h"

/* Parsing Functions for Parsing Input Files */

/* returns with pointer to array of strings, each of which represent a line in a given file */
/* current limit to each string is 1000 characters */
/* return NULL if file could not be opened */
char** lineparse_file(char* filename);

char* get_word(char* line);

/* Parsing functions for parsing command line inputs */
/* read a command line and return a string */
char* read_line();

/*
   reference: https://github.com/brenns10/lsh/blob/master/src/main.c
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **split_line(char *line);
