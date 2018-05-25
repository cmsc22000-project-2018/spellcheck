#include "dictionary.h"
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>	
#include <ctype.h>
#include "suggestion.h"
#include "dictionary.h"

/* See word.h */
int word_valid(dict_t *dict, char *word) {
    if (dict_chars_exists(word) == -1 && *word != '\n') {
	    return dict_exists(dict, word);
    }

    else {
        // Assume word is correct as it represents punctuation
        return EXIT_SUCCESS;
    }
}

/* See word.h */
int word_cap_status(char l) {
    int status = (!ispunct(l) && l >= 'A' && l <= 'Z');
    
    return status;
}

/* See word.h */
int word_check_cap(char *word) {
    int len = strlen(word);
    int i = 0;
    int npunct = 0;

    while (i < len) {
        if (ispunct(word[i])) npunct++; // number of punctuations in word
    }

	if (npunct == len) {
        return -1; // no alphabet in word
    }

	// move to first letter, assuming punctuations like " and '
	while (ispunct(word[i])) {
        i++;
    }

	if (word_cap_status(word[i])) {	// only first word, everything, or inconsistent
		int ncap = 1;	// number of capitalizations
		
        for (i++ ; i < len; i++) {
			if (word_cap_status(word[i])) {
                ncap++;
            }
        }

		if (ncap == 1) {
            return 1;
        }

		if (ncap == len - npunct) {
            return 2;
        }

		return 3;	// inconsistent
	}

	// if control reaches here, then first letter of word is not capitalized
	for (i = 0; i < len; i++) {
		if (word_cap_status(word[i])) {
            return 3;
        }
    }

	// if control reaches here, no letters are capitalized
	return 0;
}

/* See word.h */
char *word_decap(char *word) {
	int len = strlen(word);
	char *decap = strdup(word);

	for (int i = 0; i < len; i++) {
		if (word_cap_status(word[i])) {
			decap[i] -= 'A' - 'a';
		}
    }

	return decap;
}

/* See word.h */
char **word_recap(char **words, int wnum, int flag) // int nsug, int flag)
{
//	switch(flag)
	return words;	// temporary
	/* @firat
	int i = 0;
	while (i < nsug) {
		if () {

		}
	}ssss
	*/
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