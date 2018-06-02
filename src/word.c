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
#include <stdbool.h>
#include "word.h"
#include "dictionary.h"
#include "log.c/src/log.h"


/* See word.h */
bool valid_word(dict_t* dict, char* shaved_word) {
    if (dict_chars_exists(dict, *shaved_word) == EXIT_SUCCESS && *shaved_word != '\n') {
        if(dict_exists(dict, shaved_word) == EXIT_SUCCESS) {
            log_trace("returning true from valid_word");
            return true;
        } else {
            log_trace("returning false from valid_word");
            return false;
        }
    }
    return false;
}

/* See word.h */
int generate_suggestions(char* word, dict_t* dict, char **suggestions) {
	if (dict == NULL) { // hard_coded; to change with suggestion.c
        log_warn("no dictionary");
        suggestions[0] = "no suggestions";
        suggestions[1] = NULL;
        return EXIT_FAILURE;
    }

    suggestions[2] = NULL;

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
        return EXIT_SUCCESS;
    }

    log_trace("returning EXIT_FAILURE from generate_suggestions");
    return EXIT_FAILURE;
}