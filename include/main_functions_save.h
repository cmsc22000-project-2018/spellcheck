#ifndef INCLUDE_MAIN_FUNCTIONS_SAVE_H_
#define INCLUDE_MAIN_FUNCTIONS_SAVE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * \file main_functions_save.h
 * Save page functions for the interactive mode of the shell.
 */

/**
 * \brief Writes lines to a file.
 *
 * \param filename: File being input (Save destination).
 * \param lines: Array of strings to be written to the file.
 */
void save_corrections(char *filename, char **lines);

/**
 * \brief Prints the save page, accepting command line inputs until the user saves modifications (The user can choose between saving to a file, returning to editing, or exiting the program).
 *
 * \param filename: File being input.
 * \param lines: Array of strings to be written to the file.
 * \param quit: Pointer to boolean determining if the function should quit or not (true: continue in main.c loop, false: exit program).
 * \param color: Boolean to enable/disable the color functionality.
 */
void save_page(char *filename, char **lines, bool *quit, bool color);

#endif