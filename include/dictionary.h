/*
 * A dictionary structure built using tries
 */

#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_

#include "../api/include/trie.h"

#define MAXSTRLEN 60

/* A dictionary and a instant lookup table of the characters contained in it */
typedef struct {
    trie_t *dict;
} dict_t;


/*
 * Allocates a new dictionary.
 *
 * Parameters:
 *  - none
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
 *  - EXIT_SUCCESS on success, EXIT_FAILURE if an error occurs
 */
int dict_init(dict_t *d);


/*
 * Allocates a new dictionary. Uses the official dictionary from the redis server
 *
 * Parameters:
 *  - none
 *
 * Returns:
 *  - A pointer to the dictionary, or NULL if a dictionary
 *    cannot be allocated
 */
dict_t* dict_official();


/*
 * Frees the resources associated with a dictionary
 *
 * Parameters:
 *  - d: A dictionary. Must point to a dictionary allocated with dict_new
 *
 * Returns:
 *  - Always returns EXIT_SUCCESS.
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
 *  - EXIT_SUCCESS if the word is in the dictionary
 *  - EXIT_FAILURE if the word is not in the dictionary or if an error occured
 */
int dict_exists(dict_t *d, char *str);

/*
 * Adds a word to a dictionary
 *
 * Parameters:
 *  - str: A string
 *  - d: A dictionary
 *
 * Returns:
 *  - EXIT_SUCCESS upon success
 *  - EXIT_FAILURE if word is already in dictionary or if an error occured
 */
int dict_add(dict_t *d, char *str);

/*
 * Parses a file and adds all words to the dictionary
 *
 * Parameters:
 *  - d: A dictionary. Must point to already allocated memory.
 *  - file: A filename string.
 *
 * Returns:
 *  - EXIT_SUCCESS on success, 
 *  - EXIT_FAILURE if an error occurs
 */
int dict_read(dict_t *d, char *file);

/*
 * Returns the n closest words to a given string in a dictionary.
 * 
 * Parameters:
 *  - d: A dictionary. Must point to a dictionary allocated with dict_new
 *  - str: A string. This will be the (misspelled) word to match
 *  - max_edits: the maximum levenshtein distance the words in the set can have
 *  - n: the number of strings to return. 
 * 
 * Returns:
 *  - The first n strings with the smallest distance, where ties are broken by alphabetical order.
 *    If there aren't enough matching strings, each remaining spot is set to NULL.
 *  - NULL if there was an error
 */
char **dict_suggestions(dict_t *d, char *str, int max_edits, int n);


#endif /* INCLUDE_DICTIONARY_H_ */
