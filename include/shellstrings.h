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

/**
 * \brief String printing library for the shell
 */

/**
 * \memberof shellstrings
 * \brief Default text input prompt string for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_prompt(bool *color);

/**
 * \memberof shellstrings
 * \brief Main menu text for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_main_menu(bool *color);

/**
 * \memberof shellstrings
 * \brief Modification save text for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_save(bool *color);

/**
 * \memberof shellstrings
 * \brief File editing success message for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_edit_success(bool *color);

/**
 * \memberof shellstrings
 * \brief Modified text priting for the shell.
 *
 * \param lines: Array of strings, each representing a modified line.
 */
 void shell_print(char **lines);

/**
 * \memberof shellstrings
 * \brief File input confirmation prompt for the shell.
 *
 * \param filename: File being input.
 * \param status: Type of file being input (text file, dictionary, etc).
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_input(char *filename, char *status, bool *color);

/**
 * \memberof shellstrings
 * \brief Default error prompt for the shell.
 *
 * \param error_text: String for the specific error text.
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_error(char *error_text, bool *color);

/**
 * \memberof shellstrings
 * \brief Command line usage instructions screen for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_usage(bool *color);

/**
 * \memberof shellstrings
 * \brief Help page screen for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_help(bool *color);

/**
 * \memberof shellstrings
 * \brief Interactive starting message for the shell.
 *
 * \param filename: File being input.
 * \param dict: Dictionary file being input.
 * \param md: Mode (Quiet Batch, Verbose Batch, or Interactive).
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_start_interactive(char *filename, char *dict, char *md, bool *color);


/**
 * \memberof shellstrings
 * \brief Mode name printing (Verbose Batch, Quiet Batch, or Interactive).
 * 
 * \param mode: Flag for mode (1: Quiet Batch, 2: Verbose Batch, 3: Interactive).
 * \return String of the mode name.
 */
char *shell_modename(int mode);

/**
 * \memberof shellstrings
 * \brief Line printing and misspelling underlining for the shell.
 *
 * \param lnum: Number of lines.
 * \param line: String of the line being modified.
 * \param underline: String of underlines, highlighting misspelled words.
 * \param returnflag: Flag to indicate if line being parsed is the last line.
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_interactive_line_print(int lnum, char *line, char *underline, bool returnflag, bool *color);

/**
 * \memberof shellstrings
 * \brief Interactive word replacement for the shell/
 *
 * \param word: String (Word) being modified/replaced.
 * \param sug: Array of string pointers (List of suggestions).
 * \param flag: Flag indicating whether suggestion generation succeeded or not.
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_interactive_replacements(char *word, char **sug, int flag, bool *color);

/**
 * \memberof shellstrings
 * \brief Modification chart printing for the Verbose Batch Mode.
 *
 * \param lnum: Number of lines.
 * \param line: A line to calculate character position of misspelled word(s).
 * \param misspelled: A misspelled word.
 * \param suggestions: Array of string pointers (generated suggestions).
 */
void shell_verbose_chart(int lnum, char* line, char *misspelled, char **suggestions);

/**
 * \memberof shellstrings
 * \brief Save message screen for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_save_message(bool *color);

#endif