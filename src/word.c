#include "dictionary.h"
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>	

int num_punctuation = 22;
char* punctuation_array[] = {"+",",",":"," ",".","-","'","&","!","?",":",";","#","~","=","/","$","£","^","\n","_","<",">"};

// checks if punctuation exists within array
int is_in_array(char* punctuation_array[], char* word)
{
    int i = 0;
	for ( ; i < num_punctuation ; i++) {
		if (strcmp(punctuation_array[i], word) == 0) {
			//printf("comparing %s to %s", word, punctuation_array[i]);
			return 1;	}
	}
	return -1;
}

// checks if word is valid -- does not have erroneous punctuations within
int valid_word(char* word, dict_t* dict)
{
	 if (is_in_array(punctuation_array, word) == -1 && *word != '\n') {
	    return dict_exists(dict, word);

	}
	else {
		return EXIT_SUCCESS; //automatically assume word is correct as it represents punctuation
	}
}

// currently hard_coded; generates suggestions for a badly spelled word
int generate_suggestions(char* word, dict_t* dict, char **suggestions) {
//	assert (dict != NULL);

// initialize words - decapitalize if necessary
    suggestions[0] = "my";
    suggestions[1] = "me";

// generate suggestions: d, str, max_edits, edit_amount

// else
    return EXIT_FAILURE;
}
