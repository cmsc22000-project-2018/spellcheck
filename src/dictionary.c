
/*
 * A dictionary data structure based on tries
 *
 * See dictionary.h for function documentation.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include "dictionary.h"
#include "log.c/src/log.h"

/* See dictionary.h */
dict_t* dict_new() {

    dict_t *d;
    int rc;

    d = malloc(sizeof(dict_t));

    if (d == NULL) {
        log_fatal("dict_new dictionary malloc failed");
        return NULL;
    }

    rc = dict_init(d);
    if (rc != EXIT_SUCCESS) {
        log_fatal("dict_new dictionary init failed");
        return NULL;
    }

    return d;
}

/* See dictionary.h */
int dict_init(dict_t *d) {
    assert(d != NULL);

    trie_t *t = trie_new("dict");
    if (t == NULL) {
        log_fatal("dict_init trie_new failed");
        return EXIT_FAILURE;
    }
    d->dict = t;

    char *char_list = (char*)calloc(sizeof(char), 256);
    if (char_list == NULL) {
        log_fatal("dict_init char_list calloc failed");
        return EXIT_FAILURE;
    }
    d->char_list = char_list;

    log_debug("dict_init char_list set");
    return EXIT_SUCCESS;
}

/* See dictionary.h */
int dict_free(dict_t *d) {
    assert(d != NULL);
    assert(d->dict != NULL);
    assert(d->char_list != NULL);

    free(d->char_list);
    trie_free(d->dict);
    free(d);

    log_debug("dict_free success");
    return EXIT_SUCCESS;
}   

int dict_chars_exists(dict_t *d, char c) {
    assert(d != NULL);
    assert(d->char_list != NULL);

    // Use the character as the index
    int index = (int)c;

    if (d->char_list[index] == '\0') {
        log_debug("dict_chars_exists returning EXIT_FAILURE");
        return EXIT_FAILURE;
    }

    log_debug("dict_chars_exists returning EXIT_SUCCESS");
    return EXIT_SUCCESS;
}

/* See dictionary.h */
int dict_chars_update(dict_t *d, char *str) {
    log_trace("string is %s", str);
    assert(d != NULL);
    assert(d->char_list != NULL);
    assert(str != NULL);
    
    int i;
    int len = strnlen(str, MAXSTRLEN);

    if (str[len] != '\0') {
        log_trace("dict_chars_update returning EXIT_FAILURE");
        return EXIT_FAILURE;
    }

    for (i = 0; i < len; i++) {
        
        // Use each character as a hash
        int index = (int)str[i];

        d->char_list[index] = str[i];
    }

    log_trace("dict_chars_update returning EXIT_SUCCESS");
    return EXIT_SUCCESS;
}

/* See dictionary.h */
int dict_exists(dict_t *d, char *str) {
    if (d == NULL || d->dict == NULL || str == NULL || str[0] == '\0') {
        log_trace("dict_exists returning EXIT_FAILURE");
        return EXIT_FAILURE;
    }

    log_debug("dict_exists entering trie_contains");
    int rc = trie_contains(d->dict, str);

    if (rc == 0) {
        log_trace("dict_exists returning EXIT_SUCCESS");
        return EXIT_SUCCESS;
    }

    log_trace("dict_exists returning EXIT_FAILURE");
    return EXIT_FAILURE;
}

/* See dictionary.h */
int dict_add(dict_t *d, char *str) {
    if (d == NULL || d->dict == NULL || str == NULL) {
        log_trace("dict_exists returning EXIT_FAILURE");
        return EXIT_FAILURE;
    }

    if (strnlen(str, MAXSTRLEN+1) == MAXSTRLEN+1) {
        log_trace("dict_exists returning EXIT_FAILURE");
        return EXIT_FAILURE;
    }

    // Attempt to add new characters to the dictionary character list
    if (dict_chars_update(d, str) == EXIT_FAILURE) {
        log_trace("dict_exists returning EXIT_FAILURE");
        return EXIT_FAILURE;
    }

    int rc = trie_insert(d->dict, str);

    if (rc == 0) {
        log_trace("dict_exists returning EXIT_FAILURE");
        return EXIT_SUCCESS;
    }

    log_trace("dict_exists returning EXIT_FAILURE");
    return EXIT_FAILURE;
}

/* See dictionary.h */
int dict_read(dict_t *d, char *file) {

    // From here: https://stackoverflow.com/questions/16400886/reading-from-a-file-word-by-word
    char buffer[MAXSTRLEN + 1];
    FILE *f = fopen(file, "r");
    log_debug("opened file %s", file);

    if (f == NULL) {
        log_trace("dict_exists returning EXIT_FAILURE");
        return EXIT_FAILURE;
    }

    while (fscanf(f, "%100s", buffer) == 1) {
        if (dict_add(d, buffer) != EXIT_SUCCESS) {
            log_trace("dict_exists returning EXIT_FAILURE");
            return EXIT_FAILURE;
        }
    }

    fclose(f);

    log_trace("dict_exists returning EXIT_SUCCESS");
    return EXIT_SUCCESS;
}
