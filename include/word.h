/*
 * A module to handle each word and provide suggestions
 */

#ifndef INCLUDE_WORD_H_
#define INCLUDE_WORD_H_

#include "dictionary.h"

int is_in_array(char* word);

/*
 * valid_word - checks that word is in dictionary
 *
 * Parameters:
 *  - dict: A dictionary pointer. Must point to already allocated memory.
 *  - word: A string.
 *
 * Returns:
 *  - int: EXIT_SUCCESS or EXIT_FAILURE
 */
int word_valid(dict_t *dict, char* word);

/*
 * Helper function for generate_suggestions()
 *
 * word_check_cap - checks if a word has a type of capitalization
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
 * words_lowercase - Gets a string (word) array and lowercases each string (word)
 *
 * Parameters:
 *  - word: A string (word).
 *
 * Returns:
 *  - None (Modifies the given string (word) array).
 */
char *words_lowercase(char *words);

/*
 * Helper function for generate_suggestions()
 *
 * words_recap - Gets a string (word) array and capitalizes each string (word)
 *
 * Parameters:
 *  - words: A string (word) array.
 *
 * Returns:
 *  - None (Modifies the given string (word) array).
 */
void words_capitalize(char **words, int flag);

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
int generate_suggestions(dict_t *dict, char *word, char **suggestions, int max_edits, int amount);

#endif