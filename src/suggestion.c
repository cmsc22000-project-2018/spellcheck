/*
 * A series of functions to generate spelling suggestions
 * 
 * See duggestion.h for function documentation
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include "suggestion.h"
#include "zset_api.h"

// TEMPORARY UNTIL WE GET has_children AND TRIES
#include "mock_trie.h"

int has_children(dict_t *d, char *s) {

    int i = 0;
    int len = strnlen(s, MAXLEN);
    trie_t *t = d->dict;

    while (i < TRIE_LEN && t->words[i] != NULL) {
        
        if (strncmp(s, t->words[i], len) == 0) {
            return EXIT_SUCCESS;
        }

        i++;
    }

    return EXIT_FAILURE;
}

// Helper function for suggestions that just moves on to the next character
int move_on(zset_t *set, dict_t *d, char *prefix, char *suffix, int edits_left) {

    int rc = 0;
    int len = strnlen(prefix, MAXLEN);
    char* new_prefix;

    new_prefix = malloc(sizeof(char) * (MAXLEN + 1));
    if (new_prefix == NULL) {
        return rc + EXIT_FAILURE;
    }

    strncpy(new_prefix, prefix, MAXLEN);

    new_prefix[len] = suffix[0];

    if (has_children(d, new_prefix) == EXIT_SUCCESS) {

        // Move on to the next character, don't use up an edit
        rc += suggestions(set, d, new_prefix, suffix + 1, edits_left);
    }

    // Save some space now that we're done
    free(new_prefix);

    return rc + EXIT_SUCCESS;
}

// Helper function for suggestions that tries to remove the first character of the suffix
int try_delete(zset_t *set, dict_t *d, char *prefix, char *suffix, int edits_left) {

    int rc = 0;

    // Don't need to copy the string over as we aren't changing the prefix

    if (has_children(d, prefix) == EXIT_SUCCESS) {

        // Adding 1 to the suffix pointer will essentially delete the first character
        rc += suggestions(set, d, prefix, suffix + 1, edits_left - 1);
    }

    return rc + EXIT_SUCCESS;
}

// Helper function for suggestions that tries to replace the first character in the suffix and move it to the prefix
int try_replace(zset_t *set, dict_t *d, char *prefix, char *suffix, int edits_left) {

    int i;
    int rc = 0;
    int len = strnlen(prefix, MAXLEN);
    char *new_prefix;

    // Ran out of space
    if (len == MAXLEN - 1) {
        return rc + EXIT_FAILURE;
    }

    for (i = 1; i < 256; i++) {

        char c = (char)i;

        if (dict_chars_exists(d, c) == EXIT_SUCCESS) {

            new_prefix = malloc(sizeof(char) * (MAXLEN + 1));
            if (new_prefix == NULL) {
                return rc + EXIT_FAILURE;
            } else {

                strncpy(new_prefix, prefix, MAXLEN);

                // Try replacing the beginning of the suffix with each ASCII character
                // And move that to the end of the prefix
                new_prefix[len] = c;
                new_prefix[len + 1] = '\0';

                if (has_children(d, new_prefix) == EXIT_SUCCESS) {

                    // Adding 1 to the suffix pointer will essentially delete the first character
                    // Shifting the "replaced" character to the prefix
                    rc += suggestions(set, d, new_prefix, suffix + 1, edits_left - 1);
                }

                // Save some space now that we're done
                free(new_prefix);
            }
        }
    }

    return rc + EXIT_SUCCESS;
}

// Helper function that tries to swap the last character of the prefix and first character of the prefix
// and append both to the prefix
int try_swap(zset_t *set, dict_t * d, char *prefix, char *suffix, int edits_left) {

    int rc = 0;
    int len = strnlen(prefix, MAXLEN);
    char* new_prefix;

    if (len == 0 || strnlen(suffix, MAXLEN) == 0) {
        return rc + EXIT_SUCCESS;
    }

    new_prefix = malloc(sizeof(char) * (MAXLEN + 1));
    if (new_prefix == NULL) {
        return rc + EXIT_FAILURE;
    }

    strncpy(new_prefix, prefix, MAXLEN);

    // Swap suffix's first character into new_prefix and insert it in front of the last character
    new_prefix[len] = new_prefix[len - 1];
    new_prefix[len - 1] = suffix[0];
    new_prefix[len + 1] = '\0';

    if (has_children(d, new_prefix) == EXIT_SUCCESS) {
        // Adding 1 to the suffix pointer will essentially delete the first character
        rc += suggestions(set, d, new_prefix, suffix + 1, edits_left - 1);
    }

    // Save some space now that we're done
    free(new_prefix);

    return rc + EXIT_SUCCESS;
}

// Helper function for suggestions that tries to insert a character to the end of a prefix
int try_insert(zset_t *set, dict_t *d, char *prefix, char *suffix, int edits_left) {

    int i;
    int rc = 0;
    int len = strnlen(prefix, MAXLEN);
    char* new_prefix;

    // Ran out of space
    if (len == MAXLEN - 1) {
        return rc + EXIT_FAILURE;
    }

    for (i = 1; i < 256; i++) {

        char c = (char)i;

        if (dict_chars_exists(d, c) == EXIT_SUCCESS) {
            
            new_prefix = malloc(sizeof(char) * (MAXLEN + 1));
            if (new_prefix == NULL) {
                return rc + EXIT_FAILURE;
            } else {

                strncpy(new_prefix, prefix, MAXLEN);

                // Try adding on a new character
                new_prefix[len] = c;
                new_prefix[len + 1] = '\0';

                if (has_children(d, new_prefix) == EXIT_SUCCESS) {

                    // Basically just inserting the new ASCII character to the string
                    rc += suggestions(set, d, new_prefix, suffix, edits_left - 1);
                } 
            
                // Save some space now that we're done
                free(new_prefix);
            }
        }
    }

    return rc + EXIT_SUCCESS;
}

// Look at suggestion.h for documentation
int suggestions(zset_t *set, dict_t *d, char *prefix, char *suffix, int edits_left) {

    char* s;
    int rc = 0;
    
    // Since prefix and suffix can have max length MAXLEN
    s = malloc(sizeof(char) * (MAXLEN + 1) * 2);
    if (s == NULL) {
        return rc + EXIT_FAILURE;
    }

    // Now put prefix and suffix together
    strncpy(s, prefix, MAXLEN);
    strncat(s, suffix, MAXLEN);

    // Check if the current string is in the trie
    if (dict_exists(d, s) == EXIT_SUCCESS) {

        // Might have to update first comparison if value of zset_score changes
        if (edits_left >= zset_score(set, s)) {

            // Either the word wasn't in the set before or
            // We were able to reach the word in less edits than previously determined

            zset_add(set, s, edits_left);
        }
    }

    if (edits_left <= 0) {
        // Hooray for exit conditions!

        free(s);
        return rc;
    }

    // Make sure we aren't at the end of the suffix
    if (suffix[0] != '\0') {

        rc += move_on(set, d, prefix, suffix, edits_left);

        rc += try_delete(set, d, prefix, suffix, edits_left);

        rc += try_replace(set, d, prefix, suffix, edits_left);

        rc += try_swap(set, d, prefix, suffix, edits_left);
    }

    // This one doesn't need any fancy suffix stuff
    rc += try_insert(set, d, prefix, suffix, edits_left);

    free(s);

    return rc;
}

zset_t* suggestion_set_new(dict_t *d, char *str, int max_edits) {

    assert(d != NULL);
    assert(str != NULL);

    zset_t *set = zset_new(str);

    if (suggestions(set, d, "", str, max_edits) != 0) {
        return NULL;
    }

    return set;
}

char** suggestion_set_first_n(zset_t *set, int n) {
    assert(set != NULL);

    int i;
    int flag = 0;

    // Get items in decreasing edit distance
    char **list = zset_revrange(set, 0, n-1);

    char **results = (char**)malloc(sizeof(char*) * n);
    if (results == NULL) {
        return NULL;
    }

    // Since len(list) could be less than amount, make a new list with 
    // NULL for any unsuccessful items
    for (i = 0; i < n; i++) {
        if (flag == 1) {
            results[i] = NULL;
        } else {
            if (list[i] == NULL) {
                flag = 1;
                results[i] = NULL;
            } else {
                results[i] = (char*)malloc(sizeof(char) * (MAXLEN + 1));
                if (results[i] == NULL) {
                    return NULL;
                }

                strncpy(results[i], list[i], MAXLEN);
                free(list[i]);
            }
        }
    }

    free(list);

    return results;
}

char** suggestion_list(dict_t *d, char *str, int max_edits, int amount) {

    assert(d != NULL);
    assert(str != NULL);

    zset_t *set = suggestion_set_new(d, str, max_edits);

    if (set == NULL) {
        return NULL;
    }

    char **results = suggestion_set_first_n(set, amount);

    // Remove all the items from the results
    // If this doesn't happen you start getting the weirdest bugs
    // Trust me
    // Many hours were spent trying to figure out why random behavior 
    // was happening in completely unrelated functions
    zset_remrangebyrank(set, 0, -1);

    free(set);

    return results;
}
