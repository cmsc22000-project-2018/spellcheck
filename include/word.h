/*
 * A module to handle each word and provide suggestions
 */

#ifndef INCLUDE_WORD_H_
#define INCLUDE_WORD_H_

#include "dictionary.h"
#include <stdbool.h>


/*
 * valid_word: checks that word is in dictionary
 *
 * parameters: word, dictionary
 *
 * returns: bool (true if in dictionary, false if not)
 */
bool valid_word(dict_t *dict, char* word);

/*
 * generate_suggestions - Returns a list of possible suggestions
 *
 * Parameters:
 *  - word: A string (word).
 *  - dict: A dictionary pointer. Must point to already allocated memory.
 *  - suggestions: An array of strings (words).
 *
 * returns string array representing suggestions. return NULL if not given.
 */
char** generate_suggestions(dict_t* dict, char* word);

#endif