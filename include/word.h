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
 * generate_suggestions: receives
 * parameters: word, dictionary, array list to which suggestions are stored
 * returns: int (bool). FAILURE if no suggestions generated
 */
int generate_suggestions(char* word, dict_t* dict, char **suggestions);


#endif

