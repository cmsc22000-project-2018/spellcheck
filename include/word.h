#ifndef INCLUDE_WORD_H_
#define INCLUDE_WORD_H_
#include <stdio.h>
#include <strings.h>
#include "dictionary.h"
#include <stdbool.h>


/*
 * valid_word: checks that word is in dictionary
 * parameters: word, dictionary
 * returns: bool (true if in dictionary, false if not)
 * 
 */
bool valid_word(dict_t *dict, char* word);

/*
 * generate_suggestions: receives a dictionary, word, and an allocated array of suggestions
 * fills array of suggestions with words
 * note that this is currently hard-coded;
 * parameters: word, dictionary, array list to which suggestions are stored
 * returns: int (EXIT_SUCCESS OR FAILURE). FAILURE if no suggestions generated
 */
int generate_suggestions(char* word, dict_t* dict, char **suggestions);


#endif

