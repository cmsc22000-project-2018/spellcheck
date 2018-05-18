/*
 * A dictionary structure built using tries
 */

#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_

#include "mock_trie.h"

#define MAXLEN 100

/* A dictionary and a instant lookup table of the characters contained in it */
typedef struct {
    trie_t *dict;
    char *char_list;
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
 *  - EXIT_SUCCESS on success, EXIT_FAILURE if an error occurs
 */
int dict_init(dict_t *d);


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
 * Returns whether a character is in the character list
 * 
 * Parameters:
 *  - d: A dictionary. Must point to a dictionary allocated with dict_new
 *  - c: A character
 * 
 * Returns:
 *  - EXIT_SUCCESS if the character is contained in the dictionary
 *  - EXIT_FAILURE if it isn't
 */
int dict_chars_exists(dict_t *d, char c);

/*
 * Updates the character list with potential new characters from a string
 * 
 * Parameters:
 *  - d: A dictionary. Must point to a dictionary allocated with dict_new
 *  - str: a string
 * 
 * Returns:
 *  - EXIT_SUCCESS on success, 
 *  - EXIT_FAILURE if an error occurs
 */
int dict_chars_update(dict_t *d, char *str);

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


#endif /* INCLUDE_POINT_H_ */
