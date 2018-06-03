#ifndef INCLUDE_MAIN_FUNCTIONS_BATCH_H_
#define INCLUDE_MAIN_FUNCTIONS_BATCH_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dictionary.h"

/**
 * \file main_functions_batch.h
 * Batch mode functions.
 * In this mode, the program either generates a list of suggestions, printing out the list into the command line, or it generates a linked list of corrected lines, ready to be printed out to the command line or to be saved to a specific destination.
 */

/**
 * \brief Returns a line that has been corrected with automatic suggestions.
 *
 * \param line: String of line to be modified.
 * \param dict: Dictionary file being input.
 * \param verbosity: Flag indicating whether to print output or not (1: Quiet Batch Mode, 2: Verbose Batch Mode).
 * \return Modified string of line.
 */
char *edit_batch(char *line, dict_t *dict, int verbosity, int lnum);

/**
 * \brief Batch Mode function.
 *
 * \param filename: File being input.
 * \param dict: Dictionary file being input.
 * \param quit: Pointer to boolean determining if the function should quit or not (true: continue in main.c loop, false: exit program).
 * \param verbosity: Flag indicating whether to print output or not (1: Quiet Batch Mode, 2: Verbose Batch Mode).
 * \return Array of pointers to strings (lines to be printed if Verbose Batch Mode).
 */
char **batch_mode(char *filename, dict_t *dict, bool *quit, int verbosity);

#endif