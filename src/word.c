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
bool valid_word(dict_t* dict, char* shaved_word) {
    if (dict_chars_exists(dict, *shaved_word) == EXIT_SUCCESS && *shaved_word != '\n') {
        if(dict_exists(dict, shaved_word) == EXIT_SUCCESS) {
            log_trace("valid_word returning true from valid_word");
            return true;
        }
    }
    log_trace("returning false from valid_word");
    return false;
}

/* See word.h */
<<<<<<< HEAD
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
    int i = 0;
    int len = strlen(word);
    char *lower_word = strdup(word);

    while (i < len) {
        lower_word[i] = tolower(lower_word[i]);

        i++;
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
int generate_suggestions(dict_t *dict, char *word, char **suggestions, int max_edits, int amount) {
    assert(max_edits > 0 && amount > 0);

	if (dict == NULL) {
        // No change if no dictionary
        suggestions[0] = word;
        
=======
int generate_suggestions(char* word, dict_t* dict, char **suggestions) {
	if (dict == NULL) { // hard_coded; to change with suggestion.c
        log_warn("generate_suggestions no dictionary");
        suggestions[0] = "no suggestions";
        suggestions[1] = NULL;
>>>>>>> origin/dev
        return EXIT_FAILURE;
    }

    // Lowercase the inputted word
    //char *lower_word = word_lowercase(word);

    // Generate a suggestion list for the lowercased word
    //char **sug_list = dict_suggestions(dict, lower_word, max_edits, amount);

    char* sug_list[5] = {"a", "b", "c", "d", "e"};

    // Capitalize suggestions if necessary
    int flag = word_check_cap(word);

    if (flag > 0) {
        words_uppercase(sug_list, flag);
    }

    // Count number of suggestions returned
    int sug_num = 0;
    int i = 0;;
    while (sug_list[i] != NULL) {
        sug_num++;
    }

    // If no suggestions could be retrieved, return failure
	if (sug_num == 0) {
		return EXIT_FAILURE;
	}

    sug_list[sug_num] = NULL;
    // Copy the suggested words into the inputted suggestions array
    i = 0;
    while (sug_list[i] != NULL) {
        suggestions[i] = strdup(sug_list[i]);
        i++;
    }

    // Free each string
    int j;
    for (j = 0; j < sug_num; j++) {
    	free(sug_list[j]);
    }

    // Free the string array
    free(sug_list);

    return EXIT_SUCCESS;
}
