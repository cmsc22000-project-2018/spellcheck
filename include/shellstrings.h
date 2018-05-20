
/* 
 * String output functions to be used in the shell
*/

#ifndef INCLUDE_SHELLSTRINGS_H_
#define INCLUDE_SHELLSTRINGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Colors to be used in strings for the shell strings */
#define RESET       "\033[0m"               // Reset color
#define RED         "\033[31m"              // Red 
#define GREEN       "\033[32m"              // Green
#define YELLOW      "\033[33m"              // Yellow
#define BLUE        "\033[34m"              // Blue
#define WHITE       "\033[37m"              // White
#define BOLDRED     "\033[1m\033[31m"       // Bold Red
#define BOLDGREEN   "\033[1m\033[32m"       // Bold Green
#define BOLDYELLOW  "\033[1m\033[33m"       // Bold Yellow
#define BOLDBLUE    "\033[1m\033[34m"       // Bold Blue
#define BOLDWHITE   "\033[1m\033[37m"       // Bold White

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

void shell_usage();

#endif
