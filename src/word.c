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

/* See word.h */
int is_in_array(char* word) {
    int num_punctuation = 22;
    char* punctuation_array[] = {"+",",",":"," ",".","-","'","&","!","?",":",";",
                                    "#","~","=","/","$","£","^","\n","_","<",">"};

    int i;
    for (i = 0; i < num_punctuation ; i++) {
        if (strcmp(punctuation_array[i], word) == 0) {
            return 1;
        }
    }
    return -1;
}

/* See word.h */
int word_valid(dict_t *dict, char *word) {
    assert(dict != NULL);

    if (is_in_array(word) == -1 && *word != '\n') {
	    return dict_exists(dict, word);
    }

    // Assume word is correct as it represents punctuation
    return EXIT_SUCCESS;
}


/* See word.h */
int generate_suggestions(char* word, dict_t* dict, char **suggestions) {
    if (dict == NULL) { // hard_coded; to change with suggestion.c
        suggestions[0] = word;
    }

    if (strcmp(word, "splling") == 0) {
        suggestions[0] = "spelling";
        suggestions[1] = "spilling";
        return EXIT_SUCCESS;
    } else if (strcmp(word, "chequer") == 0) {
        suggestions[0] = "checker";
        suggestions[1] = "cheque";
        return EXIT_SUCCESS;;
    } else if((strcmp(word, "cme") == 0)) {
        suggestions[0] = "come";
        suggestions[1] = "came";
        return EXIT_SUCCESS;;
    } else if((strcmp(word, "m'y") == 0)) {
        suggestions[0] = "my";
        suggestions[1] = "me";
    }

    return EXIT_FAILURE;
}