#ifndef INCLUDE_WORD_H_
#define INCLUDE_WORD_H_
#include <stdio.h>
#include <strings.h>
#include "dictionary.h"

typedef struct word {
	char *word;
        int is_misspelled; //0 if misspelled, 1 if no
} word;

int is_in_array(char* punctuation_array[], char* word);

int valid_word(char* word, dict_t *dict);

int generate_suggestions(char* word, dict_t* dict, char **suggestions);


#endif

