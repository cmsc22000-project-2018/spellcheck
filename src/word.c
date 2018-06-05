/*
 * A module to handle each word and provide suggestions
 * 
 * See word.h for function documentation
 */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>	
#include <ctype.h>
#include "word.h"
#include "dictionary.h"
#include "log.c/src/log.h"
#include "dictionary.h"


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
        i++;
    }

    if (num_punct == word_length) {
        return -1; // no alphabet in word
    }

    // move to first letter, assuming punctuations like " and '
    i = 0;
    while (ispunct(word[i])) {
        i++;
    }

    if (isupper(word[i])) { // only first word, everything, or inconsistent
        num_cap++; // number of capitalizations
        
        // start counting capitalization after the first one, which is already counted in the
        // if statement
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

        return 3; // Inconsistent
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
void words_uppercase(char **words, int flag) {
    int i = 0;
    int j = 0;

    while (words[i] != NULL) {
        // If only the first character of the word should be capitalized
        if (flag == 1) {
            words[i][0] = toupper(words[i][0]);
        }

        // If the whole word should be capitalized
        if (flag == 2) {
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
bool valid_word(dict_t* dict, char* shaved_word) {
    char* decap = word_lowercase(shaved_word);
    log_trace("word is \"%s\", decap is \"%s\"", shaved_word, decap);

    if((dict_exists(dict, shaved_word) == EXIT_SUCCESS) || dict_exists(dict, decap) == EXIT_SUCCESS) {
        log_trace("valid_word returning true from valid_word");
        return true;
    } else {
        log_trace("valid_word returning false from valid_word");
        return false;
    }
}

/* See word.h */
char** generate_suggestions(dict_t *dict, char *word, int max_edits, int amount) {
    assert(max_edits > 0 && amount > 0);

	if (dict == NULL) {
        log_warn("returning NULL from generate_suggestions");
        return NULL;
    }

    int sug_num = 0;
    int i = 0;;

    // Lowercase the inputted word
    log_debug("lowercase operation on %s", word);
    char *lower_word = word_lowercase(word);
    log_debug("lower_word is %s", lower_word);

    // Generate a suggestion list for the lowercased word
    log_info("entering dict_suggestions");
    char **sug_list = dict_suggestions(dict, lower_word, max_edits, amount);
    log_info("exiting dict_suggestions");

    if (sug_list == NULL) {
        log_info("sug_list returned null");
        return NULL;
    }

    // Capitalize suggestions if necessary. i here is flag.
    i = word_check_cap(word);
    log_info("checking capitalization, flag %d", i);
    if (i > 0) {
        words_uppercase(sug_list, i);
    }


    // Count number of suggestions returned. i here is sug_list.
    i = 0;
    while (sug_list[i] != NULL) {
        sug_num++;
        i++;
    }
    log_debug("sug_num: %d", sug_num);

    // If no suggestions could be retrieved, return failure
	if (sug_num == 0) {
		return NULL;
	}

    sug_list[amount] = NULL;

    return sug_list;
}