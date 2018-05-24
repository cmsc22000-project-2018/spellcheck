
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
 * shell_error - Default error prompt string for the shell.
 *
 * Parameters:
 *  - error_text: String for the specific error text.
 *
 * Returns:
 *  - None.
 */
void shell_error(char* error_text);

/*
 * shell_error_usage - Error prompt regarding misusage of the program for the shell.
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - char *: String for the error text.
 */
char *shell_error_usage();

/*
 * shell_erorr_exit - Error prompt regarding exiting the program due to an error for the shell.
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - char *: String for the error text.
 */
char *shell_error_exit();

/*
 * shell_input - Input file confirmation prompt for the shell.
 *
 * Parameters:
 *  - input_file: String of the file input by the user.
 *  - mode: String for the mode being used (either quiet or verbose) 
 *
 * Returns:
 *  - None.
 */
void shell_input(char* input_file, char* mode);

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
 * shell_outro - Outro text for the shell.
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - None.
 */
void shell_outro();

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

#endif
