#ifndef INCLUDE_MAIN_FUNCTIONS_HOME_H_
#define INCLUDE_MAIN_FUNCTIONS_HOME_H_

#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>

/**
 * \file main_functions_home.h
 * Home page functions for the shell.
 */

#define INTERACTIVE_MODE 3 ///< Interactive Mode
#define VERBOSE_MODE 2 ///< Verbose Batch Mode
#define QUIET_MODE 1 ///< Verbose Quiet Mode
#define QUIT -1 ///< Quit Program

/**
 * \brief Prints the help page from the main page.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void help_page(bool color);

/**
 * \brief Checks whether the file input exists.
 *
 * \param filename: File being input.
 * \return Boolean (true if file exists, false if it does not).
 */
bool fileexists(const char *filename);

/**
 * \brief Helper function for main_page(), determines the input mode.
 *
 * \param arg: Command line input from main_page().
 * \param color: Boolean to enable/disable the color functionality.
 * \return Mode (1: Quiet Batch Mode, 2: Verbose Batch Mode, 3: Interactive Mode).
 */
int change_mode(char *arg, bool color);

/**
 * \brief Prints out the main page and waits for the user to input commands. Editing process begins after a file is input.
 *
 * \param quit: Pointer to boolean determining if the function should quit or not (true: continue in main.c loop, false: exit program).
 * \param mode: Mode (Quiet Batch, Verbose Batch, or Interactive).
 * \param filename: File being input.
 * \param dict: Dictionary file being input.
 * \param color: Boolean to enable/disable the color functionality.
 */
void main_page(bool *quit, int *mode, char *filename, char *dict, bool *color);

#endif