#ifndef INCLUDE_MAIN_FUNCTIONS_BATCH_H_
#define INCLUDE_MAIN_FUNCTIONS_BATCH_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dictionary.h"

/* 
 * Batch Mode Functions
 * In this mode, the program either:
 *	- generates a list of suggestions, printing the list out into the command line or
 *	- generates a linked list of corrected lines of a file, ready to be printed to
 *  the command line or saved to a specific destination.
 */

/*
 * edit_batch: returns a line which has been corrected with automatic suggestions
 * parameters:
 *  - line: string of line to be edited
 *  - dict: dictionary
 *  - verbosity: flag indicating whether or not to print output
 *    Per definitions in main_functions_home.h, 1 = QUIET_MODE, 2 = VERBOSE_MODE
 *    verbosity determines whether or not shell output exists 
 *  - lnum: line number
 * return: edited string of line
 */
char *edit_batch(char *line, dict_t *dict, int verbosity, int lnum);

/* 
 * batch_mode: operates batch mode
 *
 * parameters: 
 *  - mode: name of file to be parsed and corrected
 *  - dict: dictionary
 *  - quit: pointer to boolean (TRUE means continue in main.c loop, FALSE means exit program)
 *  - verbosity: flag indicating whether or not to print output
 *	  Per definitions in main_functions_home.h, 1 = QUIET_MODE, 2 = VERBOSE_MODE
 *
 * return: char** array of lines, to be printed if quiet mode
 */
char **batch_mode(char *filename, dict_t *dict, bool *quit, int verbosity);

#endif