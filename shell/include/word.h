#ifndef _WORD_H
#define _WORD_H
#include <stdio.h>
#include <strings.h>


typedef struct word {
	char *word;
        int is_misspelled; //0 if misspelled, 1 if no
} word;


int valid_word(char* word, dict_t *dict);
int generate_suggestions(char* word, dict_t* dict, char **suggestions);


#endif

