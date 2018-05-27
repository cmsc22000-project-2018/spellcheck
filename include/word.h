/*
 * A module to handle each word and provide suggestions
 */

#ifndef INCLUDE_WORD_H_
#define INCLUDE_WORD_H_

#include "dictionary.h"

/*
 * valid_word - checks that word is in dictionary
 *
 * Parameters:
 *  - dict: A dictionary pointer. Must point to already allocated memory.
 *  - word: A string.
 *
 * Returns:
 * EXIT_FAILURE if it is not in dictionary
 * EXIT_SUCCESS if it is in dictionary
 */
int word_valid(dict_t *dict, char* word);

/*
 * generate_suggestions - Returns a list of possible suggestions
 *
 * Parameters:
 *  - dict: A dictionary pointer. Must point to already allocated memory.
 *  - word: A string (word).
 *  - suggestions: An array of strings (words).
 *  - max_edits: Number of maximum edits.
 *  - amount: Amount of suggestions.
 *
 * Returns:
 *  - int: EXIT_SUCCESS or EXIT_FAILURE (EXIT_FAILURE if no suggestions generated.)
 */
int generate_suggestions(char* word, dict_t* dict, char **suggestions);

#endif