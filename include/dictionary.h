/*
 * A dictionary structure built using tries
 */

#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_

#include "../api/include/trie.h"

/**
 * \file dictionary.h
 * A dictionary structure built using tries.
 */

#define MAXSTRLEN 60 ///< Maximum string length.

/**
 * \brief A dictionary and a instant lookup table of the characters contained in it.
 */
typedef struct {
    trie_t *dict; ///< A dictionary file.
} dict_t;

/**
 * \memberof dict_t
 * \brief Allocates a new dictionary.
 *
 * \return A pointer to the dictionary, or NULL if a dictionary cannot be allocated.
 */
dict_t *dict_new();

/**
 * \memberof dict_t
 * \brief Initializes a dictionary.
 *
 * \param d: A dictionary. Must point to a dictionary allocated with dict_new().
 * \return EXIT_SUCCESS on success, EXIT_FAILURE if an error occurs.
 */
int dict_init(dict_t *d);

/**
 * \memberof dict_t
 * \brief Frees the resources associated with a dictionary.
 *
 * \param d: A dictionary. Must point to a dictionary allocated with dict_new().
 * \return Always returns EXIT_SUCCESS.
 */
int dict_free(dict_t *d);

/**
 * \memberof dict_t
 * \brief Returns whether a character is in the character list.
 * 
 * \param d: A dictionary. Must point to a dictionary allocated with dict_new().
 * \param c: A character.
 * \return EXIT_SUCCESS if the character is contained in the dictionary, EXIT_FAILURE if it isn't.
 */
int dict_chars_exists(dict_t *d, char c);

/**
 * \memberof dict_t
 * \brief Updates the character list with potential new characters from a string.
 * 
 * \param d: A dictionary. Must point to a dictionary allocated with dict_new().
 * \param str: A string.
 * \return EXIT_SUCCESS on success, EXIT_FAILURE if an error occurs.
 */
int dict_chars_update(dict_t *d, char *str);

/**
 * \memberof dict_t
 * \brief Checks if a string is contained in a dictionary.
 *
 * \param d: A dictionary. Must point to a dictionary allocated with dict_new().
 * \param str: A string.
 * \return EXIT_SUCCESS if the word is in the dictionary, EXIT_FAILURE if the word is not in the dictionary or if an error occured.
 */
int dict_exists(dict_t *d, char *str);

/**
 * \memberof dict_t
 * \brief Adds a word to a dictionary.
 *
 * \param d: A dictionary. Must point to a dictionary allocated with dict_new().
 * \param str: A string.
 * \return EXIT_SUCCESS upon success, EXIT_FAILURE if word is already in dictionary or if an error occured.
 */
int dict_add(dict_t *d, char *str);

/**
 * \memberof dict_t
 * \brief Parses a file and adds all words to the dictionary.
 *
 * \param d: A dictionary. Must point to a dictionary allocated with dict_new().
 * \param file: File being input.
 * \return EXIT_SUCCESS on success, EXIT_FAILURE if an error occurs.
 */
int dict_read(dict_t *d, char *file);

/**
 * \memberof dict_t
 * \brief Returns the n closest words to a given string in a dictionary.
 * 
 * \param d: A dictionary. Must point to a dictionary allocated with dict_new().
 * \param str: A string. This will be the (misspelled) word to match.
 * \param max_edits: The maximum levenshtein distance the words in the set can have.
 * \param n: The number of strings to return.
 * \return The first n strings with the smallest distance, where ties are broken by alphabetical order. If there aren't enough matching strings, each remaining spot is set to NULL (NULL if there was an error).
 */
char **dict_suggestions(dict_t *d, char *str, int max_edits, int n);

#endif /* INCLUDE_DICTIONARY_H_ */