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
#include "suggestion.h"


// Helper function for suggestions that just moves on to the next character
void move_on(zset_t *set, char *prefix, char *suffix, int edits_left) {

    char* new_prefix;

    new_prefix = malloc(sizeof(char) * (MAXLEN + 1));
    if (new_prefix == NULL) {
        // malloc failed
        return;
    }

    strncpy(new_prefix, prefix, MAXLEN);

    new_prefix[len] = suffix[0];

    if (has_children(d, new_prefix)) {

        // Move on to the next character, don't use up an edit
        suggestions(set, d, new_prefix, suffix+1, edits_left);
    }

    free(new_prefix);
}

// Helper function for suggestions that tries to remove the first character of the suffix
void try_delete(zset_t *set, dict_t *d; char *prefix, char *suffix, int edits_left) {

    // Don't need to copy the string over as we aren't changing the prefix

    if (has_children(d, prefix)) {

        // Adding 1 to the suffix pointer will essentially delete the first character
        suggestions(set, d, prefix, suffix + 1, edits_left - 1);
    }
}

// Helper function for suggestions that tries to replace the first character in the suffix and move it to the prefix
void try_replace(zset_t *set, char *prefix, char *suffix, int edits_left) {

    int i;
    int len = strnlen(prefix, MAXLEN);
    char *new_prefix;

    // Ran out of space
    if (len == MAXLEN - 1) {
        return;
    }

    for (i = 33; i < 256; i++) {

        new_prefix = malloc(sizeof(char) * (MAXLEN + 1));
        if (new_prefix == NULL) {
            // malloc failed- pass
        } else {

            strncpy(new_prefix, prefix, MAXLEN);

            // Try replacing the beginning of the suffix with each ASCII character
            // And move that to the end of the prefix
            new_prefix[len] = (char)i;
            new_prefix[len + 1] = '\0';

            if (has_children(d, new_prefix)) {

                // Adding 1 to the suffix pointer will essentially delete the first character
                // Shifting the "replaced" character to the prefix
                suggestions(set, d, new_prefix, suffix + 1, edits_left - 1);
            }

            // Save some space now that we're done
            free(new_prefix);
        }
    }
}

// Helper function that tries to swap the last character of the prefix and first character of the prefix
// and append both to the prefix
void try_swap(zset_t *set, char *prefix, char *suffix, int edits_left) {

    int len = strnlen(prefix, MAXLEN);
    char* new_prefix;

    new_prefix = malloc(sizeof(char) * (MAXLEN + 1));
    if (new_prefix == NULL) {
        // malloc failed
        return;
    }

    strncpy(new_prefix, prefix, MAXLEN);

    // Swap suffix's first character into new_prefix and insert it in front of the last character
    new_prefix[len] = new_prefix[len];
    new_prefix[len - 1] = suffix[0];
    new_prefix[len + 1] = '\0';

    if (has_children(d, new_prefix)) {
        // Adding 1 to the suffix pointer will essentially delete the first character
        suggestions(set, d, new_prefix, suffix + 1, edits_left - 1);
    }

    free(new_prefix);
}

// Helper function for suggestions that tries to insert a character to the end of a prefix
void try_insert(zset_t *set, char *prefix, char *suffix, int edits_left) {

    int i;
    int len = strnlen(prefix, MAXLEN);
    char* new_prefix;

    // Ran out of space
    if (len == MAXLEN - 1) {
        return;
    }

    for (i = 33; i < 256; i++) {

        new_prefix = malloc(sizeof(char) * (MAXLEN + 1));
        if (new_prefix == NULL) {
            // malloc failed- pass
        } else {

            strncpy(new_prefix, prefix, MAXLEN);

            // Try replacing the beginning of the suffix with each ASCII character
            new_prefix[len] = (char)i;
            new_prefix[len + 1] = '\0';

            if (has_children(d, new_prefix)) {

                // Basically just inserting the new ASCII character to the string
                suggestions(set, d, new_prefix, suffix, edits_left - 1);
            }
        
            // Save some space now that we're done
            free(new_prefix);
        }
    }
}

// Look at suggestion.h for documentation
void suggestions(zset_t *set, dict_t *d, char *prefix, char *suffix, int edits_left) {

    char* s;
    
    // Since prefix and suffix can have max length MAXLEN
    s = malloc(sizeof(char) * (MAXLEN + 1) * 2);
    if (s = NULL) {
        return;
    }

    // Now put prefix and suffix together
    strncpy(s, prefix, MAXLEN);
    strncat(s, suffix, MAXLEN);


    // Check if the current string is in the trie
    if (dict_exists(d, s) == EXIT_SUCCESS) {
        if (zset_score(set, s) == NULL || edits_left > zset_score(set, s)) {
            // Either the word wasn't in the set before or
            // We were able to reach the word in less edits than previously determined
            zset_add(set, s, edits_left);
        }
    }

    if (edits_left == 0) {
        // Hooray for exit conditions!

        free(s);
        return;
    }

    // Make sure we aren't at the end of the suffix
    if (suffix[0] != '\0') {

        move_on(set, d, prefix, suffix, edits_left);

        try_delete(set, d, prefix, suffix, edits_left);

        try_replace(set, d, prefix, suffix, edits_left);

        try_swap(set, d, prefix, suffix, edits_left);
    }

    // This one doesn't need any fancy suffix stuff
    try_insert(set, d, prefix, suffix, edits_left);

    free(s);
}