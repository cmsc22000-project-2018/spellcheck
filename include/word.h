/*
 * A module to handle each word and provide suggestions
 */

#ifndef INCLUDE_WORD_H_
#define INCLUDE_WORD_H_

#include "dictionary.h"
#include <stdbool.h>

/*
 * Helper function for word_valid()
 *
 * is_in_array - Checks if a given punctuation is within a word
 * 
 * Parameters:
 *  - word: A string (word).
 *
 * Returns:
 *  - 0: Punctuation is not in the array.
 *  - 1: Punctuation is in the array.
 */
int is_in_array(char *word);

/*
 * word_valid: checks that word is in dictionary
 * parameters: word, dictionary
 * returns: bool (true if in dictionary, false if not)
 * 
 */
bool word_valid(dict_t *dict, char* word);

/*
 * Helper function for generate_suggestions()
 *
 * word_check_cap - Checks if a word has a type of capitalization.
 *
 * Parameters:
 *  - word: A string (word).
 *
 * Returns:
 *  - -1: Error - Not a word.
 *  - 0: Not capitalized.
 *  - 1: First letter is capitalized (Note: "I" is included here).
 *  - 2: Every letter is capitalized.
 *  - 3: Inconsistent capitalization.
 */
int word_check_cap(char *word);

/*
 * Helper function for generate_suggestions()
 *
 * word_lowercase - Gets a string (word) and lowercases it.
 *
 * Parameters:
 *  - word: A string (word).
 *
 * Returns:
 *  - char *: Returns the lowercased version of the string (word).
 */
char *word_lowercase(char *word);

/*
 * Helper function for generate_suggestions()
 *
 * words_uppercase - Gets a string (word) array and uppercases each string (word).
 *
 * Parameters:
 *  - words: A string (word) array.
 *  - flag: Capitalization state from word_check_cap().
 *
 * Returns:
 *  - None (Modifies the given string (word) array).
 */
void words_uppercase(char **words, int flag);

/*
 * generate_suggestions - Returns a list of possible suggestions.
 *
 * Parameters:
 *  - dict: A dictionary pointer. Must point to already allocated memory.
 *  - word: A string (word).
 *  - suggestions: An array of strings (words).
 *  - max_edits: Levenshtein distance of the string (word).
 *  - amount: Amount of suggestions.
 *
 * Returns:
 *  - int: EXIT_SUCCESS or EXIT_FAILURE (EXIT_FAILURE if no suggestions generated).
 */
int generate_suggestions(dict_t *dict, char *word, char **suggestions, int max_edits, int amount);

#endif