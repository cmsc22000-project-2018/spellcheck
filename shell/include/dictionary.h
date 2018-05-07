/*
 * A dictionary structure built using tries
 */

#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_

#include "mock_trie.h"

/* A point in two-dimensional space */
typedef struct {
    trie_t *dict;
} dict_t;


/*
 * Allocates a new dictionary.
 *
 * Parameters:
 *  - dict: A filename of a dictionary file
 *
 * Returns:
 *  - A pointer to the dictionary, or NULL if a dictionary
 *    cannot be allocated
 */
dict_t* dict_new();


/*
 * Initializes a dictionary
 *
 * Parameters:
 *  - d: A dictionary. Must point to already allocated memory.
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs
 */
int dict_init(dict_t *d);


/*
 * Frees the resources associated with a dictionary
 *
 * Parameters:
 *  - d: A dictionary. Must point to a dictionary allocated with dict_new
 *
 * Returns:
 *  - Always returns 0.
 */
int dict_free(dict_t *d);


/*
 * Checks if a string is contained in a dictionary
 *
 * Parameters:
 *  - str: A string
 *  - d: A dictionary
 *
 * Returns:
 *  - 1 if the word is in the dictionary
 *  - 0 if the word is not in the dictionary
 *  - -1 if there was an error
 */
int in_dict(char *str, dict_t *d);

/*
 * Adds a word to a dictionary
 *
 * Parameters:
 *  - str: A string
 *  - d: A dictionary
 *
 * Returns:
 *  - 1 upon success
 *  - 0 if word is already in dictionary
 *  - -1 if there was an error
 */
int add_to_dict(char *str, dict_t *d);

/*
 * Parses a file and adds all words to the dictionary
 *
 * Parameters:
 *  - d: A dictionary. Must point to already allocated memory.
 *  - file: A filename string.
 *
 * Returns:
 *  - 1 on success, 0 if an error occurs, -1 if partial error (only able to add some words)
 */
int read_to_dict(char *file, dict_t *d);


#endif /* INCLUDE_POINT_H_ */
