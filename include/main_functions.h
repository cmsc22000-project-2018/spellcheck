#ifndef INCLUDE_MAIN_FUNCTIONS_H
#define INCLUDE_MAIN_FUNCTIONS_H

#include "parser.h"
#include "dictionary.h"
#include "word.h"
/* 
	Order of functions:
		I. Saving files
		II. Functions for editing strings (lines)
		III. Interactive Mode
		IV. Batch Mode
		V. Main Page
 */


/*
	I. Saving Files
 */
/*
 * save_corrections: writes lines (lines) to a file with name (filename)
 * parameters: name of file (saving destination), array of strings to be printed in file
 * returns: void
 */
void save_corrections(char* filename, char** lines);

/*
 * save_page: prints save_page, accepting command line inputs until save_file name is accepted, or
 * user chooses to return to page / quit
 * parameters:
 *      - name of file (saving destination)
 *      - array of strings to be printed in file
 *      - a pointer to an int, which is a flag to main indicating whether spellcheck should exit
 * returns: void
 */
void save_page(char* filename, char** lines, int* quit);

/*
	II. Functions for editing strings
*/
/*
 * underline_misspelled: generate "^" as underlines for misspelled words
 * parameters:
 *      - word to be underlined
 *      - underline (character "^" is added to underline, which is a string to be printed
 *      - below the line
 * returns: void
 */
void underline_misspelled(char *word, char* underline);

/*
 * underline_misspelled: generate " " as underlines for non-misspelled words
 * parameters:
 *      - word to be underlined
 *      - underline (character " " is added to underline)
 * returns: void
 */
void underline_correct_spelling(char *word, char* underline);

/*
 * underline_misspelled_sentence: given a list of misspelled words in order, underline them in sentence
 * paramters:
 *      - array of misspelled words
 *      - sentence to be edited
 *      - element - number in char array indicating misspelled word
 * returns: underline for line
 */
char* underline_misspelled_sentence(char** misspelled, char* sentence, int element);

/*
 * add_to_misspelled: add an incorrect word to list of misspelled words
 * parameters:
 *      - word
 *      - list of misspelled words
 * returns: int (EXIT_SUCCESS OR FAILURE)
 */
int add_to_misspelled(char *word, char** misspelled);

/*
 * parse_string: parse string, generating underline and list of misspelled words
 * parameters:
 *      - string (line) to be parsed
 *      - dictionary
 *      - underline: function generates underline, tailored to array
 *      - misspelled: misspelled words in the line
 * return: int (EXIT_SUCCESS or FAILURE).
 */
int parse_string(char* string, dict_t *dict, char *underline, char** misspelled);

//reference from https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c
/*
 * correct_line: replace word in array
 * parameters:
 *      - line to be edited
 *      - old word (misspelled)
 *      - new word (correction)
 * return: edited line 
 */
char* correct_line(char* line, char* old_word, char* new_word);

//initialises each element in array (that stores misspelled words in a line) to NULL
/*
 * initialize_misspelled: initialize array to be used in edit_interactive/edit_batch
 * parameters:
 *      - malloced array of misspelled words from interactive_mode
 *      - length of array
 * return: int indicating success (EXIT_SUCCESS OR FAILURE)
 */
int initialize_misspelled(char **misspelled, int length);

/*
	III. Interactive Mode

*/

/*
 * edit_interactive: returns a line which has been corrected accepting inputs from user
 * parameters:
 *      - line - line to be edited
 *      - dict - dictionary
 *      - linenumber - number of line
 * return: edited line
 */
char* edit_interactive(char* line, dict_t* dict, int linenumber);

/*
 * interctive mode: open file, parse and edit
 * parameters:
 *      - filename - name of file to be parsed
 *      - dictionary
 *      - *quit - pointer to a flag indicating whether or not spellcheck should terminate
 *			note 0 means continue, 1 means quit
 * return: char** array of lines, to be printed in save page
 */
char** interactive_mode(char* filename, dict_t* dict, int* quit);

/* 
	IV. Batch Mode
 */
/*
 * edit_batch: returns a line which has been corrected with automatic suggestions
 * parameters:
 *      - line - string of line to be edited
 *      - dict - dictionary
 *      - verbosity - flag indicating whether or not to print output
 *			note 0 means quiet, 1 means verbose
 *      verbosity determines whether or not shell output exists 
 * return: string of filename, edited
 */
char* edit_batch(char* line, dict_t* dict, int verbosity);

/* 
 * batch_mode: operates batch mode
 * parameters: 
 *      - mode - name of file to be parsed
 *      - dict - dictionary
 *      - quit - flag indicating whether or not quit spellcheck after operation
 *			note 0 means continue, 1 means quit
 *      - verbosity - flag indicating whether or not to print output
 *			note 0 means quiet, 1 means verbose
 * return: char** array of lines, to be printed if quiet mode
 */
char** batch_mode(char* filename, dict_t* dict, int* quit, int verbosity);

/*
	V. Main Page
 */

/*
 * help_page: Prints help page at request of user from main. Returns to main page via loop in main function
 * parameter: none 
 * return_values: none
 */
void help_page();

/* 
 * fileexists: check if file with name, given by string, exists
 * parameter: filename
 * return: int (bool)
 			1 means exists, 0 means not
 */
int fileexists(const char* filename);

/*
 * change_mode: helper for main_page, determine input mode
 * parameter: command line input from main_page
 * return: number indicating mode
 * 			1 means quiet, 2 verbose, 3 interactive
 */
int change_mode(char* arg);

/*
 * main_page: operates main page
 		- prints out the main page and waits for user to respond with
 		  commands to enter a file name, dictionary name, help page
 		  request, or quit
 * parameters:
 *		- flag indicating whether or not spellcheck exits
 *			0 is continue, 1 is quit
 *		- flag indicating mode
 *			1 is quiet, 2 is verbose, 3 is 
 *		- file_name - file name / path
 *		- dict_name - dictionary file name / path
 * return: void
 */
void main_page(int* quit, int *mode, char* file_name, char* dict_name);


#endif
