#ifndef INCLUDE_MAIN_FUNCTIONS_SAVE_H_
#define INCLUDE_MAIN_FUNCTIONS_SAVE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
 * Save Page Functions: after the editing process is over, the result of the edit must be written
 * into a given file, or printed out into the terminal.
 */

/*
 * save_corrections: writes lines (lines) to a file with name (filename)
 *
 * parameters:
 *		- filename: string indicating name of file (saving destination)
 *		- lines: array of strings to be printed in file
 *
 * returns: void
 */
void save_corrections(char *filename, char **lines);

/*
 * save_page: prints save_page, accepting command line inputs until user prints file, 
 * user indicates file saving destination, user chooses to return to editing, or user decides to exit
 *
 * parameters:
 *      - filename: string indicating name of file (saving destination)
 *      - lines: array of strings to be printed in file
 *      - quit: pointer to boolean (TRUE means continue in main.c loop, FALSE means exit program)
 *
 * returns: void
 */
void save_page(char *filename, char **lines, bool *quit, bool* color);

#endif