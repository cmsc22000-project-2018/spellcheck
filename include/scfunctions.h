#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
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

void save_corrections(char* filename, char** lines)

void save_page(char* filename, char** lines,int* quit)

/*
	II. Functions for editing strings
*/

void underline_misspelled(char *tkn, char* underline);

void underline_correct_spelling(char *tkn, char* underline);

void add_to_badwords(char *badword, char** badwords);

//takes in a line, identifies incorrect words, and generates a string of underlines  
void parse_string(char* string, dict_t *dict, char *underline, char** badwords);

//reference from https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c
char* correct_line(char* line, char* old_word, char* new_word);

//initialises each element in array (that stores misspelled words in a line) to NULL
void initialize_badwords(char *badwords, int length);

/*
	III. Interactive Mode

*/

/* Functions needed for interactive mode */
char* edit_interactive(char* line, dict_t* dict);

/* interctive mode - open file, parse and work on later */
void interactive_mode(char* filename, int* quit) //will pass in dictionary later

/* 
	IV. Batch Mode
 */

char* edit_batch(char* line, dict_t* dict, int verbosity);

void batch_mode(char* filename, dict_t* dict, int* quit, int verbosity);

/*
	V. Main Page
 */


/* Prints help page. Returns to main page via loop in main function */
void help_page();

/* Check if file with name, given by string, exists */
int fileexists(const char* filename);

/* helper for main_page, determine input mode */
int mode(char* arg);

void main_page(int* quit, int *mode, char* file_name, char* dict_name);
