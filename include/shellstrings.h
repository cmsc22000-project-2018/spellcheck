/* 
 * String output functions to be used in the shell
*/

#ifndef INCLUDE_SHELLSTRINGS_H_
#define INCLUDE_SHELLSTRINGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define RESET       "\033[0m"               // Reset color
#define RED         "\033[31m"              // Red
#define YELLOW      "\033[33m"              // Yellow
#define GREEN       "\033[32m"              // Green
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
 *  - color: if true, print colored string.
 *
 * Returns:
 *  - None.
 */
void shell_prompt(bool color);

/*
 * shell_intro - Introduction text for the shell.
 *
 * Parameters:
 *  - color: if true, print colored string.
 *
 * Returns:
 *  - None.
 */
void shell_main_menu(bool color);

/*
 * shell_save - Modification saving text for the shell.
 *
 * Parameters:
 *  - color: if true, print colored string.
 *
 * Returns:
 *  - None.
 */
void shell_save(bool color);

/*
 * shell_edit_success - file editing success message
 *
 * Parameters:
 *  - color: if true, print colored string.
 *
 * Returns:
 *  - None.
 */
void shell_edit_success(bool color);

/*
 * shell_print - Print edited text for viewing
 *
 * Parameters:
 * 	- lines: string array, each representing edited line of file.
 *
 * Returns:
 * 	- None.
 */
 void shell_print(char **lines);

/*
 * shell_input - Input file confirmation prompt for the shell.
 *
 * Parameters:
 *  - input_file: String of the file input by the user.
 *  - status: String for the file type - dictionary or 
 *    this is a string because shell_input is used
 *    to print a confirmation message on the screen
 *  - color: if true, print colored string.
 *
 * Returns:
 *  - None.
 */
void shell_input(char *filename, char *status, bool color);

/*
 * shell_error - Default error prompt string for the shell
 *
 * Parameters:
 *  - error_text: String for the specific error text.
 *  - color: if true, print colored string.
 *
 * Returns:
 *  - None.
 */
void shell_error(char *error_text, bool color);

/*
 * shell_usage - command line usage instructions
 *
 * Parameters:
 *  - color: if true, print colored string.
 *
 * Returns:
 *  - None.
 */
void shell_usage(bool color);

/*
 * shell_help - Default text input prompt string for the shell.
 *
 * Parameters:
 *  - color: if true, print colored string.
 *
 * Returns:
 *  - None.
 */
void shell_help(bool color);

/*
 * shell_start_interactive - prints out interactive starting message
 *
 * Parameters:
 * - file: name of file.
 * - dict: name of dictionary file.
 * - md: prints out name of mode, if the user chooses -v flag.
 * - color: if true, print colored string.
 *
 * Returns:
 * - None.
 */
void shell_start_interactive(char *filename, char *dict, char *md, bool color);


/*
 * shell_modename - prints out mode name (verbose, quiet or interactive)
 * 
 * Parameters: 
 * - mode: integer representing chosen mode. This can be QUIET_MODE, VERBOSE_MODE or INTERACTIVE_MODE
 * 
 * Returns:
 * - string containing name of mode.
 */
char *shell_modename(int mode);

/*
 * shell_interactive_line_print: prints line, underlining errors
 *
 * Parameters:
 *  - lnum: line number
 *  - line: string of the line being edited
 *  - underline: string of underlines, highlighting error words
 *  - returnflag: indicates if line being parsed is the last line (true if it is the last line)
 *    in this case, there is a formatting issue; the text file that was read does not have a newline character
 *    at the end of the file.
 *  - color: if true, print colored string.
 * Returns:
 *  - None.
 */
void shell_interactive_line_print(int lnum, char *line, char *underline, bool returnflag, bool color);

/*
 * shell_interactive_replacements
 *
 * Parameters:
 *  - word: word being replaced
 *  - sug: list of suggestions
 *  - color: if true, print colored string.
 *
 * Returns:
 *  - None.
 */
void shell_interactive_replacements(char *word, char **sug, bool color);

/*
 * shell_verbose_chart - verbose chart print 
 *
 * Parameters:
 *  - lnum: line number
 *  - line: line, to calculate character position of misspelled word
 *  - misspelled: misspelled word
 *  - suggestions: char** array of generated suggestions
 *
 * Returns:
 *  - None.
 */
void shell_verbose_chart(int lnum, char* line, char *misspelled, char **suggestions);

/*
 * shell_save_message - save message
 *
 * Parameters:
 *  - color: if true, print colored string.
 *
 * Returns:
 *  - None.
 */
void shell_save_message(bool color);

#endif