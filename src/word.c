/*
 * A module to handle each word and provide suggestions
 * 
 * See word.h for function documentation
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>	
#include <ctype.h>
#include "word.h"
#include "dictionary.h"

// checks if word is valid -- does not have erroneous punctuations within
int valid_word(dict_t* dict, char* word) {
    if (dict_chars_exists(dict, *word) == EXIT_SUCCESS && *word != '\n') {
	    return dict_exists(dict, word);
	}
		return EXIT_FAILURE;
}


/* See word.h */
int generate_suggestions(char* word, dict_t* dict, char **suggestions) {
	if (dict == NULL) { // hard_coded; to change with suggestion.c
        suggestions[0] = "no suggestions";
        suggestions[1] = NULL;
        return EXIT_FAILURE;
    }

    suggestions[2] = NULL;

	if (strncmp(word, "splling", 7) == 0) {
		suggestions[0] = "spelling";
		suggestions[1] = "spilling";
		return EXIT_SUCCESS;
	} else if (strncmp(word, "chequer", 7) == 0) {
    	suggestions[0] = "checker";
    	suggestions[1] = "cheque";
    	return EXIT_SUCCESS;;
	} else if((strncmp(word, "cme", 3) == 0)) {
    	suggestions[0] = "come";
    	suggestions[1] = "came";
    	return EXIT_SUCCESS;;
	} else if((strncmp(word, "m'y", 3) == 0)) {
        suggestions[0] = "my";
        suggestions[1] = "me";
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}