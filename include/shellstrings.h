
/* 
 * String output functions to be used in the shell
*/

#ifndef INCLUDE_SHELLSTRINGS_H_
#define INCLUDE_SHELLSTRINGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * shell_prompt - Default text input prompt string for the shell.
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - None.
 */
void shell_prompt();

/*
 * shell_intro - Introduction text for the shell.
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - None.
 */
void shell_intro();

/*
 * shell_save - Modification saving text for the shell.
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - None.
 */
void shell_save();

/*
 * shell_print - Print edited text for viewing
 *
 * Parameters:
 * 	- lines: string array, each representing edited line of file.
 *
 * Returns:
 * 	- None.
 */
 void shell_print(char** lines);


/*
 * shell_error - Error message printing function for shell, with a string input for specific error
 *
 * Parameters:
 *  - error_text: String for the specific error text.
 *
 * Returns:
 *  - None.
 */
void shell_error(char* error_text);

/*
 * shell_input - Input file confirmation prompt for the shell.
 *
 * Parameters:
 *  - input_file: String of the file input by the user.
 *  - status: String for the file type - dictionary or 
 *				this is a string because shell_input is used
 *				to print a confirmation message on the screen
 *
 * Returns:
 *  - None.
 */
void shell_input(char* input_file, char* status);

/*
 * shell_help - Default text input prompt string for the shell.
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - None.
 */
void shell_help();

/*
 * shell_usage - command line usage instructions
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - None.
 */
void shell_usage();

/*
 * shell_verbose_chart - verbose chart print 
 *
 * Parameters:
 *	- lnum: line number
 *	- misspelled: misspelled word
 *	- suggestions: char** array of generated suggestions
 *
 * Returns:
 *  - None.
 */
void shell_verbose_chart(int lnum, char* misspelled, char** suggestions);


#endif
