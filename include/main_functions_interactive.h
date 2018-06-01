#ifndef INCLUDE_MAIN_FUNCTIONS_INTERACTIVE_H_
#define INCLUDE_MAIN_FUNCTIONS_INTERACTIVE_H_

#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

/*
 * Interactive Mode:
 * In this mode, the program generates suggestions for corrections to misspelled words,
 * then accepts choices from the user to correct the contents of the file.
 */

/*
 * edit_interactive: returns a line which has been corrected by generating a char** list of
 * misspelled words, asking for correction choices from user through the command line and
 * replacing misspelled word with user choices
 * parameters:
 *      - line: line to be edited
 *      - dict: dictionary
 *      - linenumber: number of line
 *		- returnflag: indicates if line being parsed is the last line (true if last line)
 *			in this case, there is a formatting issue in printing out the line that needs to be resolved,
 *			because the text file that was read does not have a newline character
 *			at the end of the line.
 * return: edited line
 */
char *edit_interactive(char *line, dict_t *dict, int linenumber, bool returnflag, bool* color);

/*
 * interactive_mode: open file to parse and store in list, edit each line, then return list
 * parameters:
 *      - filename: name of file to be parsed and corrected
 *      - dictionary: dictionary for searching 
 *      - quit: pointer to boolean (TRUE means continue in main.c loop, FALSE means exit program)
 *      - color: pointer to boolean (TRUE means print in colors, FALSE means print without colors)
 * return: char** array of lines, to be printed in save page
 */
char **interactive_mode(char *filename, dict_t *dict, bool *quit, bool* color);

#endif