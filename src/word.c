/*
 * A module to handle each word and provide suggestions
 * 
 * See word.h for function documentation
 */

#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "word.h"
#include "dictionary.h"
#include "log.c/src/log.h"

/* See word.h */
bool valid_word(dict_t *dict, char *shaved_word) {
    char *decap = word_lowercase(shaved_word);
    log_trace("(valid_word) Word is \"%s\", lowercased version is \"%s\".", shaved_word, decap);

    if ((dict_exists(dict, shaved_word) == EXIT_SUCCESS) ||
        dict_exists(dict, decap) == EXIT_SUCCESS) {
        log_trace("(valid_word) Returning true from valid_word().");
        return true;
    }

    else {
        log_trace("(valid_word) Returning false from valid_word().");
        return false;
    }
}

/* See word.h */
int word_check_cap(char *word) {
    int word_length = strlen(word);
    int i = 0;
    // Number of punctuations in the word
    int num_punct = 0;
    // Number of capitalizations
    int num_cap = 0;

    while (i < word_length) {
        if (ispunct(word[i])) {
            num_punct++;
        }

        i++;
    }

    // No alphabetical character in the word
    if (num_punct == word_length) {
        return NOT_WORD;
    }

    // Moves to the first letter, assuming punctuations like " and '
    i = 0;

    while (ispunct(word[i])) {
        i++;
    }

    // Only first word, everything, or inconsistent
    if (isupper(word[i])) {
        num_cap++;
        
        /*
         * Start counting capitalization after the first letter,
         * which is already counted in the if statement
         */
        for (i++; i < word_length; i++) {
            if (isupper(word[i])) {
                num_cap++;
            }
        }

        if (num_cap == 1) {
            return ONE_CAP;
        }

        if (num_cap == word_length - num_punct) {
            return ALL_CAPS;
        }

        // Inconsistent
        return SOME_CAPS;
    }

    // If control reaches here, then the first letter of the word is not capitalized
    for (i = 0; i < word_length; i++) {
        if (isupper(word[i])) {
            return SOME_CAPS;
        }
    }

    // If control reaches here, then no letters are capitalized
    return 0;
}

/* See word.h */
char *word_lowercase(char *word) {
    int i;
    int len = strlen(word);
    char *lower_word = strdup(word);

    for (i = 0; i < len; i++) {
        lower_word[i] = tolower(lower_word[i]);
    }

    return lower_word;
}

/* See word.h */
void words_restore_cap(char **words, int flag) {
    int i = 0;
    int j = 0;

    while (words[i] != NULL) {
        // If only the first character of the word should be capitalized
        if (flag == ONE_CAP) {
            words[i][0] = toupper(words[i][0]);
        }

        // If the whole word should be capitalized
        if (flag == ALL_CAPS) {
            int len = strlen(words[i]);

            j = 0;

            while (j < len) {
                words[i][j] = toupper(words[i][j]);
                
                j++;
            }
        }

        i++;
    }
}

/* See word.h */
char **generate_suggestions(dict_t *dict, char *word, int max_edits, int amount) {
    assert(max_edits > 0 && amount > 0);

	if (dict == NULL) {
        log_warn("(generate_suggestions) Returning NULL from generate_suggestions().");
        return NULL;
    }

    int sug_num = 0;
    int i = 0;;

    // Lowercases the inputted word
    log_debug("(generate_suggestions) Lowercase operation on '%s'.", word);
    char *lower_word = word_lowercase(word);
    log_debug("(generate_suggestions) Lowercased word is '%s'.", lower_word);

    // Generate a suggestion list for the lowercased word
    log_debug("(generate_suggestions) Entering dict_suggestions().");
    char **sug_list = dict_suggestions(dict, lower_word, max_edits, amount);
    log_debug("(generate_suggestions) Exiting dict_suggestions().");

    if (sug_list == NULL) {
        log_debug("(generate_suggestions) sug_list() returned NULL.");
        return NULL;
    }

    log_debug("first category is \"%s\"", sug_list[0]);

    // Capitalizes suggestions if necessary. i here is flag
    i = word_check_cap(word);
    log_debug("(generate_suggestions) Checking capitalization, flag %d.", i);
    
    if (i > 0) {
        words_restore_cap(sug_list, i);
    }

    // Counts number of suggestions returned (i here is sug_list()).
    i = 0;

    while (sug_list[i] != NULL) {
        sug_num++;
        i++;
    }
    log_debug("(generate_suggestions) sug_num() returned %d.", sug_num);

    // If no suggestions could be retrieved, returns failure
	if (sug_num == 0) {
		return NULL;
	}

    sug_list[amount] = NULL;

    return sug_list;
}