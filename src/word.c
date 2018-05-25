/*
 * A module to handle each word and provide suggestions
 * 
 * See word.h for function documentation
 */

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
    assert(dict != NULL);

    if (dict_chars_exists(word) == -1 && *word != '\n') {
	    return dict_exists(dict, word);
    }

    // Assume word is correct as it represents punctuation
    return EXIT_SUCCESS;
}

/*
 * Helper function for generate_suggestions()
 *
 * word_check_cap - checks if a word has a type of capitalization
 *
 * Parameters:
 *  - word: A string (word).
 *
 * Returns:
 *  - -1: Error - Not a word.
 *  - 0: Not capitalized.
 *  - 1: First letter is capitalized (Note: "I" is included here).
 *  - 2: Every letter is capitalized.
 *  - 3: Inconsistent capitalization.
 */
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

	if (isupper(word[i])) {	// only first word, everything, or inconsistent
		int ncap = 1;	// number of capitalizations
		
        for (i++ ; i < len; i++) {
			if (isupper(word[i])) {
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
		if (isupper(word[i])) {
            return 3;
        }
    }

	// if control reaches here, no letters are capitalized
	return 0;
}

/*
 * Helper function for generate_suggestions()
 *
 * word_decap - Gets a string (word) and decapitalizes it
 *
 * Parameters:
 *  - word: A string (word).
 *
 * Returns:
 *  - char **: A string (word) that is decapitalized.
 */
char *word_decap(char *word) {
	int len = strlen(word);
	char *decap = strdup(word);

	for (int i = 0; i < len; i++) {
		if (isupper(word[i])) {
			decap[i] -= 'A' - 'a';
		}
    }

	return decap;
}

/*
 * Helper function for generate_suggestions()
 *
 * word_recap - Gets a decapitalized string (word) and recapitalizes it
 *
 * Parameters:
 *  - words: A string (word) array.
 *  - word_number: Number of words in the array.
 *  - capitalization: State of capitalization from word_check_cap().
 *
 * Returns:
 *  - char **: A string (word) array of recapitalized words.
 */
char **word_recap(char **words, int word_number, int capitalization) {
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