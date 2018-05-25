#ifndef INCLUDE_WORD_H_
#define INCLUDE_WORD_H_

#include <stdio.h>
#include <strings.h>
#include "dictionary.h"

/*
 * valid_word: checks that word is in dictionary
 * parameters: word, dictionary
 * returns: int (EXIT_SUCCESS OR FAILURE)
 */
int word_valid(dict_t *dict, char* word);

// helpers for generate_suggestions

/*
 * word_cap_status - checks if a character is a letter & is capitalized
 * parameter: letter 
 * returns: boolean (0 if not capitalized, 1 if capitalized)
 */
//return positive if sth is capitalized
int word_cap_status(char l);

/*
 * word_check_cap - checks if a word has a type of capitalization
 * parameter: word
 * return cases:
 * -1 if not a word 
 * 0 if not capitalized
 * 1 if first letter is capitalized (note "I" is included here)
 * 2 if everything is capitalized
 * 3 if inconsistent
 */
int word_check_cap(char *word);

/*
 * word_decap - returns a decapitalized word
 * parameter: word
 * returns: decapitalized word
 */
char* word_decap(char *word);

/*
 * word_recap - recapitalize words
 * parameter: array of words, number of words in array, flag (from check_cap)
 * returns - recapitalized words
 */
char** word_recap(char **words, int wnum, int flag); // int nsug, int flag);

/*
 * generate_suggestions: return a list of suggestions
 * parameters: word, dictionary, array list to which suggestions are stored
 * returns: int (EXIT_SUCCESS OR FAILURE). FAILURE if no suggestions generated
 */
int generate_suggestions(dict_t *dict, char *word, char **suggestions, int max_edits, int amount);

#endif