/*
 * A module to generate suggestions for a word
 */

#ifndef INCLUDE_SUGGESTION_H_
#define INCLUDE_SUGGESTION_H_

#include "zset_api.h"
#include "dictionary.h"

// The maximum length of a string we're willing to process
// Longest word in english dictionary is 45 letters lol
#define MAXLEN 60

/*
 * Sees if there are any words in a dictionary that contain a given prefix
 * NOTE- awaiting the actual function from support tools
 * 
 * Parameters: 
 *  - d: A dictionary. Must point to a dictionary allocated with dict_new
 *  - s: A string. The prefix to check
 * 
 * Returns:
 *  - 0 if there is aword in the dictionary with the prefix
 *  - 1 otherwise
*/
int has_children(dict_t *d, char *s);

/*
 * Does a fuzzy sting match on all the words in a dictionary
 * 
 * Parameters:
 *  - set: A Redis Sorted Set. Must point to a zset allocated with zset_new()
 *  - d: A dictionary. Must point to a dictionary allocated with dict_new
 *  - prefix: A prefix of a word. Must be contained in a dictionary or ""
 *  - suffix: A suffix of a word. Can also be ""
 *  - edits_left: The maximum levenshtein distance a word can be from prefix+suffix
 * 
 * Returns:
 *  - 0 for success, or a positive integer n for the number of errors encountered
 * 
 */
int suggestions(zset_t *set, dict_t *d, char *prefix, char *suffix, int edits_left);

/*
 * Creates a redis sorted set of spelling suggestions for a word using suggestions
 * 
 * Parameters:
 *  - d: A dictionary. Must point to a dictionary allocated with dict_new
 *  - str: A string. This will be the (misspelled) word to match
 *  - max_edits: the maximum levenshtein distance the words in the set can have
 * 
 * Returns:
 *  - A pointer to the sorted set containing the words or
 *  - NULL if there was an error
 * 
 */
zset_t* suggestion_set_new(dict_t *d, char *str, int max_edits);

/*
 * Given a redis sorted set, takes the highest n scoring strings out of it
 * 
 * Parameters:
 *  - set:  A Redis Sorted Set. Must point to a zset allocated with zset_new()
 *          Also must have been passed through suggestions
 *  - n: the amount of strings to return. Strings are the ones with the smallest
 *          distance and ties broken by reverse alphabetic order
 * 
 * Returns:
 *  - The first n strings matching above, or NULL if there was an error
 *  - If there ween't enough matching strings, NULL is returned in each remaining spot
 */
char** suggestion_set_first_n(zset_t *set, int n);

/*
 * Returns the n closest words to a given string in a dictionary
 * 
 * Parameters:
 *  - d: A dictionary. Must point to a dictionary allocated with dict_new
 *  - str: A string. This will be the (misspelled) word to match
 *  - max_edits: the maximum levenshtein distance the words in the set can have
 *  - the amount of strings to return. Strings are the ones with the smallest
 *          distance and ties broken by reverse alphabetic order
 * 
 * Returns: 
 *  - The first n strings matching above, or NULL if there was an error
 *  - If there ween't enough matching strings, NULL is returned in each remaining spot
 * 
 */
char** suggestion_list(dict_t *d, char *str, int max_edits, int amount);

#endif