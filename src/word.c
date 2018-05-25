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
    int word_length = strlen(word);
    int i = 0;
    int num_punct = 0;
    int num_cap = 0;

    while (i < word_length) {
        if (ispunct(word[i])) num_punct++; // number of punctuations in word
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

/*
 * Helper function for generate_suggestions()
 *
 * words_lowercase - Gets a string (word) array and lowercases each string (word)
 *
 * Parameters:
 *  - word: A string (word).
 *
 * Returns:
 *  - None (Modifies the given string (word) array).
 */
void words_lowercase(char **words) {
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

/*
 * Helper function for generate_suggestions()
 *
 * words_recap - Gets a string (word) array and capitalizes each string (word)
 *
 * Parameters:
 *  - words: A string (word) array.
 *
 * Returns:
 *  - None (Modifies the given string (word) array).
 */
void words_capitalize(char **words) {
    int i = 0;
    int j = 0;

    while (i < sizeof(words)) {
        while (j < strlen(words[i])) {
            if (isupper(words[i][j]) == 0) {
                toupper(words[i][j]);
            }

            j++;
        }

        i++;
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