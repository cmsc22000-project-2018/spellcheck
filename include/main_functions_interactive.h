#ifndef INCLUDE_MAIN_FUNCTIONS_INTERACTIVE_H_
#define INCLUDE_MAIN_FUNCTIONS_INTERACTIVE_H_

#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

/**
 * \file main_functions_interactive.h
 * Interactive mode functions for the shell.
 */

/**
 * \brief Returns a line which has been corrected by generating a clist of misspelled words, asks for correction choices from user through the command line, and replaces misspelled word with the user choices.
 * 
 * \param line: Line to be modified.
 * \param dict: Dictionary file being input.
 * \param linenumber: Number of lines.
 * \param returnflag: Flag to indicate if line being parsed is the last line.
 * \param color: Boolean to enable/disable the color functionality.
 * \return Modified line.
 */
char *edit_interactive(char *line, dict_t *dict, int linenumber, bool returnflag, bool *color);

/**
 * \brief Opens a file to parse and store it in a list, then edits each line, and returns the list.
 *
 * \param filename: File being input.
 * \param dictionary: Dictionary file being input.
 * \param quit: Pointer to boolean determining if the function should quit or not (true: continue in main.c loop, false: exit program).
 * \param color: Boolean to enable/disable the color functionality.
 * \return Array of strings (lines to be printed in the save page).
 */
char **interactive_mode(char *filename, dict_t *dict, bool *quit, bool *color);

#endif