#include "dictionary.h"
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>	
#include "suggestion.h"

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
int generate_suggestions(dict_t* dict, char* word, char** suggestions, int max_edits, int amount)
{
	if (dict == NULL) {
        suggestions[0] = word; // no change if no dictionary
        return EXIT_FAILURE;
    }

// capitalize, set flag if necessary


// get dictionary
    char** sug = suggestion_list(dict, word, max_edits, amount);

// check suggestion number is appropriate
    int i = 0;
    while (sug[amount] != NULL) i++;
    printf("no. of suggestions generated is %d\n", i);

// decapitalize if necessary

// copy into suggestions
    int i;
    for (i = 0; i < amount; i++) {
        suggestions[i] = strdup(sug[i]);
    }	// free?

    return EXIT_SUCCESS;
}
