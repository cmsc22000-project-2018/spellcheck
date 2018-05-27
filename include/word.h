#ifndef INCLUDE_WORD_H_
#define INCLUDE_WORD_H_
#include <stdio.h>
#include <strings.h>
#include "dictionary.h"

/*
 * is_in_array: checks if a given punctuation is within a word
 * parameters: array of punctuations, word
 * returns: int
 * EXIT_FAILURE is if it is not in array
 * EXIT_SUCCESS is if it is
 */
int is_in_array(char* word);

/*
 * valid_word: checks that word is in dictionary
 * parameters: word, dictionary
 * returns: int (EXIT_SUCCESS OR FAILURE)
 * EXIT_FAILURE if it is not in array
 * EXIT_SUCCESS if it is in dictionary
 */
int valid_word(dict_t *dict, char* word);

/*
 * generate_suggestions: receives a dictionary, word, and an allocated array of suggestions
 * fills array of suggestions with words
 * note that this is currently hard-coded;
 * parameters: word, dictionary, array list to which suggestions are stored
 * returns: int (EXIT_SUCCESS OR FAILURE). FAILURE if no suggestions generated
 */
int generate_suggestions(char* word, dict_t* dict, char **suggestions);


#endif

