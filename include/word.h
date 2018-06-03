/*
 * A module to handle each word and provide suggestions
 */

#ifndef INCLUDE_WORD_H_
#define INCLUDE_WORD_H_

#include "dictionary.h"
#include <stdbool.h>

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
 * \brief Returns a list of possible suggestions.
 *
 * \param word: A string (word).
 * \param dict: A dictionary pointer. Must point to already allocated memory with dict_new().
 * \param suggestions: Array of strings (list of suggestions).
 * \return EXIT_SUCCESS or EXIT_FAILURE (EXIT_FAILURE if no suggestions generated).
 */
int generate_suggestions(char* word, dict_t* dict, char **suggestions);

#endif