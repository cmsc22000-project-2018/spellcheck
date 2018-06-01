#ifndef INCLUDE_MAIN_FUNCTIONS_HOME_H_
#define INCLUDE_MAIN_FUNCTIONS_HOME_H_

#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>

/*
 *	Main Page Functions:
 *		In the event that Spellcheck is not given a file to parse and edit, the main page will be printed out 
 *		such that the user can seek help, quit spellcheck, enter a filename, or enter a dictionary filename.
 *		These functions operate the main page.
 */

#define INTERACTIVE_MODE 3
#define VERBOSE_MODE 2
#define QUIET_MODE 1
#define QUIT -1

/*
 * help_page: Prints help page at request of user from main. Returns to main page via loop in main function
 * parameter: none 
 * return_values: none
 */
void help_page(bool *color);

/* 
 * fileexists: check if file with name, given by string, exists
 * parameter: string of file name, potential target for editing
 * return: bool, TRUE means exists, FALSE means not
 */
bool fileexists(const char *filename);

/*
 * change_mode: helper for main_page, determine input mode
 * parameter: command line input from main_page
 * return: number indicating mode
 * 			1 means quiet, 2 verbose, 3 interactive
 */
int change_mode(char *arg);

/*
 * main_page: prints out the shellstring main page and waits for user to respond with
 *			  commands to enter a file name, dictionary name, help page request, or quit.
 *			  Editing process begins when filename is entered.
 * parameters:
 *      - quit: pointer to boolean (TRUE means continue in main.c loop, FALSE means exit program)
 *		- flag indicating mode
 *			1 = QUIET_MODE, 2 = VERBOSE_MODE, 3 = INTERACTIVE_MODE
 *		- file_name: string indicating name of file to be parsed
 *		- dict_name: string indicating dictionary file name
 * return: void
 */
void main_page(bool *quit, int *mode, char *filename, char *dict, bool *color);

#endif
