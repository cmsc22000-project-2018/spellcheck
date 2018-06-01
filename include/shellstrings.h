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
 *  - None.
 *
 * Returns:
 *  - None.
 */
void shell_prompt(bool *color);

/*
 * shell_intro - Introduction text for the shell.
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - None.
 */
void shell_main_menu(bool *color);

/*
 * shell_save - Modification saving text for the shell.
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - None.
 */
void shell_save(bool *color);

/*
 * shell_edit_success - file editing success message
 *
 * Parameters:
 *  - None
 *
 * Returns:
 *  - None.
 */
void shell_edit_success(bool *color);

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
 *              this is a string because shell_input is used
 *              to print a confirmation message on the screen
 *
 * Returns:
 *  - None.
 */
void shell_input(char *filename, char *status, bool *color);

/*
 * shell_error - Default error prompt string for the shell.
 *
 * Parameters:
 *  - error_text: String for the specific error text.
 *
 * Returns:
 *  - None.
 */
void shell_error(char *error_text, bool *color);

/*
 * shell_error_format - Error prompt regarding an input error for the shell
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - char *: String for the error text.
 */
char *shell_error_input();

/*
 * shell_error_format - Error prompt regarding a format error
 * of the command line input for the shell.
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - char *: String for the error text.
 */
char *shell_error_format();

/*
 * shell_erorr_dict - Error prompt regarding invalid dictionary file input for the shell.
 *
 * Parameters:
 *  - dict: String for the name of the inputted dictionary file.
 *
 * Returns:
 *  - char *: String for the error text.
 */
char *shell_error_dict(char *dict);

/*
 * shell_erorr_filename - Error prompt regarding invalid text file input for the shell.
 *
 * Parameters:
 *  - filename: String for the name of the inputted dictionary file.
 *
 * Returns:
 *  - char *: String for the error text.
 */
char *shell_error_file(char *filename);

/*
 * shell_error_exit - Error prompt regarding the shell exiting
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - char *: String for the error text.
 */
char *shell_error_exit();

/*
 * shell_error_parse - Error prompt regarding the parse operation for he shell
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - char *: String for the error text.
 */
char *shell_error_parse();

/*
 * shell_error_suggestion - Error prompt regarding the suggestion operation for he shell
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - char *: String for the error text.
 */
char *shell_error_suggestion();

/*
 * shell_help - Default text input prompt string for the shell.
 *
 * Parameters:
 *  - None.
 *
 * Returns:
 *  - None.
 */
void shell_help(bool *color);

/*
 * shell_start_interactive - prints out interactive starting message
 *
 * Parameters:
 *  - file, dictionary, mode names
 *
 * Returns:
 *  - None.
 */
void shell_start_interactive(char *filename, char *dict, char *md, bool *color);


/*
 * shell_modename - prints out mode name (verbose, quiet or interactive)
 * 
 * Accepts flag int
 *      note 1 is quiet, 2 is batch, 3 is interactive
 */
char *shell_modename(int mode);

/*
 * shell_interactive_line_print: prints line, underlining errors
 *
 * Parameters:
 *  - lnum: line number
 *	- line: string of the line being edited
 *	- underline: string of underlines, highlighting error words
 *  - returnflag: if the line is the final line, an additional newline character must be printed
 *		to avoid 
 * Returns:
 *  - None.
 */
void shell_interactive_line_print(int lnum, char *line, char *underline, int returnflag, bool *color);

/*
 * shell_interactive_replacements
 *
 * Parameters:
 *  - word being replaced
 *  - list of suggestions
 *  - flag indicating whether suggestion generation succeeded or not
 *
 * Returns:
 *  - None.
 */
void shell_interactive_replacements(char *word, char **sug, int flag, bool *color);

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
void shell_verbose_chart(int lnum, char *misspelled, char **suggestions);

/*
 * shell_save_message - save message
 *
 * Parameters:
 *  - None
 *
 * Returns:
 *  - None.
 */
void shell_save_message(bool *color);

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