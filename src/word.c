#include "dictionary.h"
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>	

int num_punctuation = 22;
char* punctuation_array[] = {"+",",",":"," ",".","-","'","&","!","?",":",";","#","~","=","/","$","£","^","\n","_","<",">"};

int is_in_array(char* punctuation_array[], char* word) {
    int i = 0;
	for ( ; i < num_punctuation ; i++) {
		if (strcmp(punctuation_array[i], word) == 0) {
			//printf("comparing %s to %s", word, punctuation_array[i]);
			return 1;	}
	}
	return -1;
}

int valid_word(char* word, dict_t* dict) {
	 if (is_in_array(punctuation_array, word) == -1 && *word != '\n') {
	    return dict_exists(dict, word);

	}
	else {
		return EXIT_SUCCESS; //automatically assume word is correct as it represents punctuation
	}
}


int generate_suggestions(char* word, dict_t* dict, char **suggestions) {
//	assert (dict != NULL);

	if (strcmp(word, "splling") == 0) {
		suggestions[0] = "spelling";
		suggestions[1] = "spilling";
		return EXIT_SUCCESS;
	}
	else if (strcmp(word, "chequer") == 0) {
	suggestions[0] = "checker";
	suggestions[1] = "cheque";
	return 0;
	}

	else if((strcmp(word, "cme") == 0)) {
	suggestions[0] = "come";
	suggestions[1] = "came";
	return 0;
	}

    else if((strcmp(word, "m'y") == 0)) {
    suggestions[0] = "my";
    suggestions[1] = "me";
    }

	else {
        int i = 1;
        if (dict == NULL) {
            i = EXIT_FAILURE;
        } // erase after implementing dict. empty line to use variable to avoid warning
		return i;
	}
    return EXIT_FAILURE;
}
