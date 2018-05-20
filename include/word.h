#ifndef INCLUDE_WORD_H_
#define INCLUDE_WORD_H_
#include <stdio.h>
#include <strings.h>
#include "dictionary.h"

/*
typedef struct word {
	char *word;
        int is_misspelled; //0 if misspelled, 1 if no
} word;
*/

/*
 * is_in_array: checks if a given punctuation is within a word
 * parameters: array of punctuations, word
 * returns: int (bool)
 */
int is_in_array(char* punctuation_array[], char* word);

/*
 * valid_word: checks that word is in dictionary
 * parameters: word, dictionary
 * returns: int (bool)
 */
int valid_word(char* word, dict_t *dict);

/*
 * generate_suggestions: return a list of suggestions
 * parameters: word, dictionary, array list to which suggestions are stored
 * returns: int (bool). FAILURE if no suggestions generated
 */
int generate_suggestions(dict_t* dict, char* word, char **suggestions, int max_edits, int amount);

// helpers for generate_suggestions

/*
 * ca_status - checks if a character is a letter & is capitalized
 * parameter: letter 
 * returns: boolean (0 if not capitalized, 1 if capitalized)
 */
//return positive if sth is capitalized
int cap_status(char l);

/*
 * check_cap - checks if a word has a type of capitalization
 * parameter: word
 * return cases:
 * -1 if not a word 
 * 0 if not capitalized
 * 1 if first letter is capitalized (note "I" is included here)
 * 2 if everything is capitalized
 * 3 if inconsistent
 */
int check_cap(char* word);

/*
 * word_decap - returns a decapitalized word
 * parameter: word
 * returns: decapitalized word
 */
char* word_decap(char* word);

/*
 * recap - recapitalize words
 * parameter: array of words, number of words in array, flag (from check_cap)
 * returns - recapitalized words
 */
char** recap(char** words); // int nsug, int flag);

#endif

