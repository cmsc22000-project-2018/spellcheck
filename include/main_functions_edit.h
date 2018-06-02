#ifndef INCLUDE_MAIN_FUNCTIONS_EDIT_H
#define INCLUDE_MAIN_FUNCTIONS_EDIT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dictionary.h"

/*
 * Functions for Editing Strings
 */

/*
 * is_in_punct_array: determines if character is presented in hard coded punctuation array
 *
 * parameter: character
 *
 * return: returns true if a character is a punctuation char, false otherwise
 */

bool is_in_punct_array(char letter);

/* 
 * remove_prefix_punctuation: removes any punctuation characters
 * at the beginning of a string of alphabets
 *
 * parameter: word (string)
 *
 * return: void
 */
void remove_prefix_punctuation(char *word);

/*
 * remove_trailing_punctuation: removes any punctuation characters
 * that trail a string of alphabets
 *
 * parameter: word (string)
 *
 * return: void
 */
void remove_trailing_punctuation(char *word); 

/* 
 * remove_punctuation: combines remove_trailing_punctuation and remove_prefix_punctuation,
 * to remove trailing and prefix punctuation without modifying original word
 *
 * parameter: word (string)
 *
 * return: word (string) with removed surrounding punctuations
 */
char* remove_punctuation(char *word);

/*
 * underline_misspelled_sentence: given a list of misspelled words in order,
  underline them in sentence (will underline in line once per occurence in array)
 *
 * paramters:
 *      - array of misspelled words
 *      - sentence to be edited
 *
 * returns: underline for line
 */
char* underline_misspelled_sentence(char** misspelled, char* sentence, char* underline);

/*
 * add_to_misspelled: add an incorrect word to list of misspelled words
 *
 * parameters:
 *      - word
 *      - list of misspelled words
 *
 * returns: int (EXIT_SUCCESS OR FAILURE)
 */
int add_to_misspelled(char *word, char** misspelled);

/*
 * parse_string: generate char** array of misspelled words from a line, as well as an underline
 *				 highlighting those misspelled words to be printed in the terminal
 *
 * parameters:
 *      - string (line) to be parsed
 *      - dictionary
 *      - underline: string of ' ' and '^', highlighting misspelled words in sentence to be printed out in terminal
 *		  this is initialized in edit_batch and edit_interactive as a malloc'd array with length of edit target string.
 *      - misspelled: char** array of misspelled words in the line
 *
 * return: void
 */
void parse_string(char* string, dict_t *dict, char *underline, char** misspelled);

/*
 * correct_line: replace word in array with word suggestion chosen by user
 * parameters:
 *      - line to be edited
 *      - old word (misspelled)
 *      - new word (correction)
 * return: edited line 
 * //reference from https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c
 */
char* correct_line(char* line, char* old_word, char* new_word);

#endif