#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "dictionary.h"

// checks
int word_chars_exists(dict_t* dict, char* word) {
/*    int num_punctuation = 22;
    char* punctuation_array[] = {"+",",",":"," ",".","-","'","&","!","?",":",";",
                                    "#","~","=","/","$","£","^","\n","_","<",">"};

*/
    int i;
    int len = strlen(word);

	for (i = 0; i < len ; i++) {
		if (dict_chars_exists(dict, word[i]) == EXIT_FAILURE) {
			return EXIT_SUCCESS;
        }
	}
	return EXIT_FAILURE;
}

// checks if word is valid -- does not have erroneous punctuations within
int valid_word(dict_t* dict, char* word) {
	 if (word_chars_exists(dict, word) == EXIT_FAILURE && *word != '\n') {
	    return dict_exists(dict, word);
	}
	else {
		return EXIT_SUCCESS; //automatically assume word is correct as it represents punctuation
	}
    return EXIT_SUCCESS;
}

// currently hard_coded; generates suggestions for a badly spelled word
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
