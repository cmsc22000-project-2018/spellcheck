#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* returns allocated array of strings, each of which are lines from the text file
 * this array can later be reproduced into a new file/overwrite the existing one
 */
char** lineparse_file(char* filename);

/* Returns next word in line */
char* get_word(char* line);

/* Parse command lines */
char *read_line();

char **split_line(char* line);
/* how to revert lines, preserving their punctuation? */
