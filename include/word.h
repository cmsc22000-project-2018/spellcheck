/*
 * A module to handle each word and provide suggestions
 */

#ifndef INCLUDE_WORD_H_
#define INCLUDE_WORD_H_

#include "dictionary.h"
#include <stdbool.h>

#define NOT_WORD -1 ///< String is not a word.
#define NO_CAP 0 ///< String is not capitalized.
#define ONE_CAP 1 ///< First letter of string is not capitalized
#define ALL_CAPS 2 ///< All words are capitalized
#define SOME_CAPS 3 ///< String capitalization is Inconsistent

/**
 * \file word.h
 * A module to handle each word and provide suggestions.
 */

/**
 * \brief Checks that a word is in a dictionary.
 *
 * \param dict: A dictionary pointer. Must point to already allocated memory with dict_new().
 * \param word: A string (word).
 * \return Boolean (true if in dictionary, false if not).
 */
bool valid_word(dict_t *dict, char* word);

/**
 * \brief Checks that word is in dictionary
 *
 * \param word: A string (word).
 * \param dict: A dictionary pointer. Must point to already allocated memory with dict_new().
 *
 * \return bool (true if in dictionary, false if not)
 */
bool valid_word(dict_t *dict, char* word);

/**
 * \brief Checks if a word has a type of capitalization.
 *
 * \param word: A string (word).
 *
 * \return NOT_WORD: Error - Not a word.
 * \return NO_CAP: Not capitalized.
 * \return ONE_CAP: First letter is capitalized.
 * \return ALL_CAPS: Every letter is capitalized.
 * \return SOME_CAPS: Inconsistent capitalization.
 */
int word_check_cap(char *word);

/**
 * \brief Gets a string (word) and lowercases it.
 *
 * \param word: A string (word).
 *
 * \return Lowercased version of the string (word).
 */
char *word_lowercase(char *word);

/**
 * \brief Gets a string (word) array and uppercases each string (word).
 *
 * \param words: A string (word) array.
 * \param flag: Capitalization state from word_check_cap().
 *
 * \return None (Modifies the given string (word) array).
 */
void words_restore_cap(char **words, int flag);

/**
 * \brief Returns a list of possible suggestions.
 *
 * \param dict: A dictionary pointer. Must point to already allocated memory.
 * \param word: A string (word).
 * \param max_edits: Levenshtein distance of the string (word).
 * \param amount: Amount of suggestions.
 *
 * \return String array representing suggestions. return NULL if not given.
 */
char** generate_suggestions(dict_t *dict, char *word, int max_edits, int amount);

#endif