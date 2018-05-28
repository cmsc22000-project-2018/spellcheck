/*
 * Main function library for the shell
 */

#ifndef INCLUDE_MAIN_FUNCTIONS_H_
#define INCLUDE_MAIN_FUNCTIONS_H_

#include "parser.h"
#include "dictionary.h"
#include "word.h"

/* 
 * Order of functions:
 *   I. Saving files
 *   II. Functions for editing strings (lines)
 *   III. Interactive Mode
 *   IV. Batch Mode
 *   V. Main Menu
 */

/*
 * I. Saving Files
 */

/*
 * save_corrections - Writes lines to a file
 *
 * Parameters:
 *  - filename: File being input
 *  - lines: Array of strings.
 *
 * Returns:
 *  - Nothing (Modifies the file that was input).
 */
void save_corrections(char *filename, char **lines);

/*
 * save_page - Prints the save page, going through command line inputs
 * until the program exits through saving or discarding changes
 *
 * Parameters:
 *  - filename: File being input
 *  - lines: Array of strings.
 *  - quit: Pointer to int (Flag to main() indicating whether spellcheck should exit).
 *
 * Returns:
 *  - Nothing (Saves to file).
 */
void save_page(char *filename, char **lines, int *quit);

/*
 * II. Functions for editing strings
 */

/*
 * is_in_punct_array - determines if charater is a punctuation
 * parameter: character
 * return: returns EXIT_SUCCESS if a character is a punctuation char
 */

int is_in_punct_array(char letter);

/* 
 * remove_prefix_punctuation - removes any punctuation characters
 * at the beginning of a string of alphabets
 * parameter: word (string)
 * return: EXIT_SUCCESS if word has no punctuation characters or
 *		   if word has been successfully shaved of prefix punctuations
 */
int remove_prefix_punctuation(char *word); 


/*
 * remove_trailing_punctuation - removes any punctuation characters
 * that trail a string of alphabets
 * parameter: word (string)
 * return: EXIT_SUCCESS if word has no punctuation characters or
 *		   if word has been successfully shaved of trailing punctuations
 */
int remove_trailing_punctuation(char *word); 

/* 
 * remove_punctuation - combines remove_trailing_punctuation and remove_prefix_punctuation,
 * to remove trailing and prefix punctuation without modifying original word
 * parameter: word (string)
 * return: word (string) with removed surrounding punctuations
 */
char* remove_punctuation(char *word);

/*
 * underline_misspelled - Generates '^' under misspelled words
 *
 * Parameters:
 *  - word: String (word) to be underlined.
 *  - underline: String (word).
 *
 * Returns:
 *  - Nothing ('^' is added to underline).
 */
void underline_misspelled(char *word, char *underline);

/*
 * underline_correct_spelling - Generates ' ' as underlines for non-misspelled words
 *
 * Parameters:
 *  - word: String (word) to be underlined.
 *  - underline: String (word).
 *
 * Returns:
 *  - Nothing (' ' is added to underline).
 */
void underline_correct_spelling(char *word, char *underline);

/*
 * underline_misspelled_sentence - Given a list of misspelled words in order,
 *                                 underlines them in a sentence
 *
 * Paramters:
 *  - misspelled: Array of string (misspelled words).
 *  - sentence: String (Sentence to be edited).
 *
 * Returns:
 *  - char *: String (Sentence) underline for the line.
 */
char *underline_misspelled_sentence(char **misspelled, char *sentence, char *underline);

/*
 * add_to_misspelled - Adds a misspelled word to a list of misspelled words
 *
 * Parameters:
 *  - word: A string (word).
 *  - misspelled: Array of string (misspelled words).
 *
 * Returns:
 *  - int: EXIT_SUCCESS or EXIT_FAILURE.
 */
int add_to_misspelled(char *word, char **misspelled);

/*
 * parse_string - Parses a string, generates underline and a list of misspelled words
 *
 * Parameters:
 *  - string: String (line) to be parsed.
 *  - dict: Dictionary file.
 *  - underline: String (word).
 *  - misspelled: Array of string (misspelled words in the line).
 *
 * Returns:
 *  - int: EXIT_SUCCESS or EXIT_FAILURE.
 */
int parse_string(char *string, dict_t *dict, char *underline, char **misspelled);

/*
 * correct_line - Replaces a word in a string array
 *
 * Source: https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c
 *
 * Parameters:
 *  - line: String (line to be edited).
 *  - old_word: String (Misspelled word).
 *  - new_word: String (Corrected word).
 *
 * Returns:
 *  - char *: String (Edited line with corrections).
 */
char *correct_line(char *line, char *old_word, char *new_word);

/*
 * III. Interactive Mode
 */

/*
 * edit_interactive - Returns a string (line) corrected by inputs from the user
 *
 * Parameters:
 *  - line: String (Line to be edited).
 *  - dict: Dictionary file.
 *  - linenumber: Number of lines.
 *  - returnflag: Integer as flag.
 *
 * Returns:
 *  - char *: String (Edited line).
 */
char *edit_interactive(char *line, dict_t *dict, int linenumber, int returnflag);

/*
 * interctive mode - Takes a file, parses and edits it
 *
 * Parameters:
 *  - filename: File being input.
 *  - dict - Dictionary file.
 *  - quit - Pointer to a flag indicating whether or not spellcheck should terminate
 *			 (0: Continue, 1: Quit).
 *
 * Returns:
 *  - char **: Array of string pointers (lines to be printed in save page).
 */
char **interactive_mode(char *filename, dict_t *dict, int *quit);

/* 
 * IV. Batch Mode
 */

/*
 * edit_batch - Returns a line that has been corrected with suggestions
 *
 * Parameters:
 *  - line - String (Line to be edited).
 *  - dict - Dictionary file.
 *  - verbosity - Flag indicating whether or not to print output
 *	              (0: Quiet, 1: Verbose).
 *
 * Returns:
 *  - char **: String (Edited file).
 */
char *edit_batch(char *line, dict_t *dict, int verbosity, int lnum);

/* 
 * batch_mode - Operates batch mode
 *
 * Parameters: 
 *  - filename - File being input.
 *  - dict - Dictionary file.
 *  - quit - Pointer to a flag indicating whether or not spellcheck should terminate
 *           (0: Continue, 1: Quit).
 *  - verbosity - Flag indicating whether or not to print output
 *                (0: Quiet, 1: Verbose).
 *
 * Returns:
 *  - char**: Array of strings (lines to be printed).
 */
char **batch_mode(char *filename, dict_t *dict, int *quit, int verbosity);

/*
 * V. Main Menu
 */

/*
 * help_page - Prints the help page.
 *
 * Parameters:
 *  - None.
 * 
 * Returns:
 *  - None.
 */
void help_page();

/* 
 * fileexists - Checks if the file being input exists or not
 *
 * Parameters:
 *  - filename: File being input.
 *
 * Returns:
 *  - int: Pseudoboolean - 1: Exists, 0: Does not exist.
 */
int fileexists(const char *filename);

/*
 * Helper function for main_page()
 *
 * change_mode - Determines input mode
 *
 * Parameters:
 *  - arg: String (Command line input from main_page()).
 *
 * Returns:
 *  - int: Number indicating mode - 1: Quiet, 2: Verbose, 3: Interactive.
 */
int change_mode(char *arg);

/*
 * main_page - Operates main page
 *
 * Parameters:
 *  - filename - File being input.
 *  - dict - Dictionary file.
 *  - quit - Pointer to a flag indicating whether or not spellcheck should terminate
 *           (0: Continue, 1: Quit).
 *	- mode - Flag indicating mode (1: Quiet, 2: Verbose, 3: Interactive).
 *
 * Returns:
 *  - Nothing.
 */
void main_page(char *filename, char *dict, int *quit, int *mode);

#endif