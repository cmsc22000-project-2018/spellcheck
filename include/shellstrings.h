/* 
 * String output functions to be used in the shell
*/

#ifndef INCLUDE_SHELLSTRINGS_H_
#define INCLUDE_SHELLSTRINGS_H_

#include <stdio.h>
#include <stdlib.h>
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
void shell_main_menu();

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
 * shell_edit_success - file editing success message
 *
 * Parameters:
 *  - None
 *
 * Returns:
 *  - None.
 */
void shell_edit_success();

/*
 * shell_print - Print edited text for viewing
 *
 * Parameters:
 * 	- None.
 *
 * Returns:
 * 	- None.
 */
 void shell_print(char** lines);

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
 * shell_erorr_dict - Error prompt regarding invalid dictionary file input for the shell.
 *
 * Parameters:
 *  - dict_file: String for the name of the inputted dictionary file.
 *
 * Returns:
 *  - char *: String for the error text.
 */
char *shell_error_dict(char *dict_file);

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
 * shell_start_interactive - prints out interactive starting message
 *
 * Parameters:
 *  - file, dictionary, mode names
 *
 * Returns:
 *  - None.
 */
void shell_start_interactive(char* file_name, char* dict_name, char* md);


/*
 * shell_modename - prints out mode name (verbose, quiet or interactive)
 * 
 * Accepts flag int
 *      note 1 is quiet, 2 is batch, 3 is interactive
 */
char* shell_modename(int mode);

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
void shell_interactive_line_print(int lnum, char* line, char* underline, int returnflag);

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
void shell_interactive_replacements(char* word, char** sug, int flag);

/*
 * shell_save_message - save message
 *
 * Parameters:
 *  - None
 *
 * Returns:
 *  - None.
 */
void shell_save_message();

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
 * shell_verbose_start - verbose chart print 
 *
 * Parameters:
 *  - line number
 *	- misspelled word
 *	- generated suggestions
 *
 * Returns:
 *  - None.
 */
void shell_verbose_chart(int lnum, char* misspelled, char** suggestions);


#endif
