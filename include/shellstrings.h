#ifndef INCLUDE_SHELLSTRINGS_H_
#define INCLUDE_SHELLSTRINGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define RESET       "\033[0m"               ///< Resets printf() color to white.
#define RED         "\033[31m"              ///< Changes printf() color to red.
#define YELLOW      "\033[33m"              ///< Changes printf() color to yellow.
#define BLUE        "\033[34m"              ///< Changes printf() color to blue.
#define GREEN       "\033[32m"              ///< Changes printf() color to green.
#define WHITE       "\033[37m"              ///< Changes printf() color to white.
#define BOLDRED     "\033[1m\033[31m"       ///< Changes printf() color to bold red.
#define BOLDYELLOW  "\033[1m\033[33m"       ///< Changes printf() color to bold yellow.
#define BOLDBLUE    "\033[1m\033[34m"       ///< Changes printf() color to bold blue.
#define BOLDGREEN   "\033[1m\033[32m"       ///< Changes printf() color to bold green.
#define BOLDWHITE   "\033[1m\033[37m"       ///< Changes printf() color to bold white.

/**
 * \file shellstrings.h
 * String printing library for the shell.
 */

/**
 * \brief Default text input prompt string for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_prompt(bool *color);

/**
 * \brief Main menu text for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_main_menu(bool *color);

/**
 * \brief Modification save text for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_save(bool *color);

/**
 * \brief File editing success message for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_edit_success(bool *color);

/**
 * \brief Modified text priting for the shell.
 *
 * \param lines: Array of strings, each representing a modified line.
 */
 void shell_print(char **lines);

/**
 * \brief File input confirmation prompt for the shell.
 *
 * \param filename: File being input.
 * \param status: Type of file being input (text file, dictionary, etc).
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_input(char *filename, char *status, bool *color);

/**
 * \brief Default error prompt for the shell.
 *
 * \param error_text: String for the specific error text.
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_error(char *error_text, bool *color);

/**
 * \brief Command line usage instructions screen for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_usage(bool *color);

/**
 * \brief Help page screen for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_help(bool *color);

/**
 * \brief Interactive starting message for the shell.
 *
 * \param filename: File being input.
 * \param dict: Dictionary file being input.
 * \param md: Mode (Quiet Batch, Verbose Batch, or Interactive).
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_start_interactive(char *filename, char *dict, char *md, bool *color);


/**
 * \brief Mode name printing (Verbose Batch, Quiet Batch, or Interactive).
 * 
 * \param mode: Flag for mode (1: Quiet Batch, 2: Verbose Batch, 3: Interactive).
 * \return String of the mode name.
 */
char *shell_modename(int mode);

/**
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
 * \brief Interactive word replacement for the shell/
 *
 * \param word: String (Word) being modified/replaced.
 * \param sug: Array of strings (list of suggestions).
 * \param flag: Flag indicating whether suggestion generation succeeded or not.
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_interactive_replacements(char *word, char **sug, int flag, bool *color);

/**
 * \brief Modification chart printing for the Verbose Batch Mode.
 *
 * \param lnum: Number of lines.
 * \param line: A line to calculate character position of misspelled word(s).
 * \param misspelled: A misspelled word.
 * \param suggestions: Array of strings (list of generated suggestions).
 */
void shell_verbose_chart(int lnum, char* line, char *misspelled, char **suggestions);

/**
 * \brief Save message screen for the shell.
 *
 * \param color: Boolean to enable/disable the color functionality.
 */
void shell_save_message(bool *color);

#endif