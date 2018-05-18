#ifndef _SCFUNCTIONS_H
#define _SCFUNCTIONS_H

#include "parser.h"
#include "scfunctions.h"
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
/* writes lines (lines) to a file with name (filename) */
void save_corrections(char* filename, char** lines);

/* Prints save_page, accepting command line inputs until save_file name is accepted, or
 * user chooses to return to page / quit */
void save_page(char* filename, char** lines,int* quit);

/*
	II. Functions for editing strings
*/
// generate "^" as underlines for misspelled words
void underline_misspelled(char *tkn, char* underline);

// generate spaces as underlines under correct words
void underline_correct_spelling(char *tkn, char* underline);

// add an incorrect word to list of bad words
int add_to_badwords(char *badword, char** badwords);

//takes in a line, identifies incorrect words, and generates a string of underlines  
int parse_string(char* string, dict_t *dict, char *underline, char** badwords);

//reference from https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c
char* correct_line(char* line, char* old_word, char* new_word);

//initialises each element in array (that stores misspelled words in a line) to NULL
int initialize_badwords(char **badwords, int length);

/*
	III. Interactive Mode

*/

/* returns a line which has been corrected accepting inptus from user*/
char* edit_interactive(char* line, dict_t* dict, int linenumber);

/* interctive mode - open file, parse and work on later */
char** interactive_mode(char* filename, dict_t* dict, int* quit); //will pass in dictionary later

/* 
	IV. Batch Mode
 */
/* returns a line which has been corrected with automatic suggestions
 * verbosity determines whether or not shell output exists */
char* edit_batch(char* line, dict_t* dict, int verbosity);

/* operates batch mode */
char** batch_mode(char* filename, dict_t* dict, int* quit, int verbosity);

/*
	V. Main Page
 */


/* Prints help page. Returns to main page via loop in main function */
void help_page();

/* Check if file with name, given by string, exists */
int fileexists(const char* filename);

/* helper for main_page, determine input mode */
int change_mode(char* arg);

/* operates main page */
void main_page(int* quit, int *mode, char* file_name, char* dict_name);

//given a list of bad words in order, underline them in sentence
char* underline_misspelled_sentence(char** badwords, char* sentence, int element);

#endif
