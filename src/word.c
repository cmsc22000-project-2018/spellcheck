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
#include "suggestion.h"

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
int word_check_cap(char *word) {
    int word_length = strlen(word);
    int i = 0;
    int num_punct = 0;
    int num_cap = 0;

    while (i < word_length) {
        if (ispunct(word[i])) {
            num_punct++; // number of punctuations in word
        }
    }

	if (num_punct == word_length) {
        return -1; // no alphabet in word
    }

	// move to first letter, assuming punctuations like " and '
	while (ispunct(word[i])) {
        i++;
    }

	if (isupper(word[i])) {	// only first word, everything, or inconsistent
		num_cap++; // number of capitalizations
		
        for (i++ ; i < word_length; i++) {
			if (isupper(word[i])) {
                num_cap++;
            }
        }

		if (num_cap == 1) {
            return 1;
        }

		if (num_cap == word_length - num_punct) {
            return 2;
        }

		return 3; // inconsistent
	}

	// if control reaches here, then first letter of word is not capitalized
	for (i = 0; i < word_length; i++) {
		if (isupper(word[i])) {
            return 3;
        }
    }

	// if control reaches here, no letters are capitalized
	return 0;
}

/* See word.h */
char *words_lowercase(char *words) {
    int i = 0;
    int j = 0;

    while (i < sizeof(words)) {
        while (j < strlen(words[i])) {
            if (islower(words[i][j]) == 0) {
                tolower(words[i][j]);
            }

            j++;
        }

        i++;
    }
}

/* See word.h */
void words_capitalize(char **words, int flag) {
    int i = 0;
    int j = 0;

    while (i < sizeof(words)) {
        if (flag == 1) {
            toupper(words[i][0]);
        }

        if (flag == 2) {
            while (j < strlen(words[i])) {
                if (isupper(words[i][j]) == 0) {
                    toupper(words[i][j]);
                }

                j++;
            }

            i++;
        }
    }
}

/* See word.h */
int generate_suggestions(dict_t *dict, char *word, char **suggestions, int max_edits, int amount) {
	if (dict == NULL) {
        suggestions[0] = word; // no change if no dictionary
        return EXIT_FAILURE;
    }

/*
// capitalize, set flag if necessary
    int flag = check_cap(word);
    char* decap_word = word_decap(word);
*/

// get dictionary
    char **sug = suggestion_list(dict, word, max_edits, amount); // change word to decap_word later

// check suggestion number is appropriate
    int i = 0;
    while (sug[i] != NULL) {
        i++;
    }
/*
// recapitalize suggestions if necessary
    if (flag > 0) sug = recap(sug) // nsug, flag); // needs to be loop!
*/

    // count number of valid suggestions returned.
    // If not requested number, return exit_failure
	if (i < amount) {
		return EXIT_FAILURE;
	}


    // copy into suggestions
    for (i = 0; i < amount; i++) {
        suggestions[i] = strdup(sug[i]);
    }

    //free
    for (int j = 0; j < i; j++) {
    	free(sug[j]);
    }

    free(sug);

    return EXIT_SUCCESS;
}