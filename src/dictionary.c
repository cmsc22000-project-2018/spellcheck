
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
#include <time.h>
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
    time_t current_time;
    char* c_time_string;

    current_time = time(NULL);
    c_time_string = ctime(&current_time);

    trie_t* t = trie_new(c_time_string);
    if (t == NULL) {
        log_fatal("dict_init trie_new failed");
        return EXIT_FAILURE;
    }
    d->dict = t;
    
    return EXIT_SUCCESS;
}

/* See dictionary.h */
dict_t* dict_official() {

    dict_t *d;
    int rc;

    d = malloc(sizeof(dict_t));

    if (d == NULL) {
        log_fatal("dict_new dictionary malloc failed");
        return NULL;
    }

    trie_t* t = trie_new("dictionary");
    if (t == NULL) {
        log_fatal("dict_init trie_new failed");
        return EXIT_FAILURE;
    }
    d->dict = t;

    return d;
}

/* See dictionary.h */
int dict_free(dict_t *d) {
    assert(d != NULL);
    assert(d->dict != NULL);

    trie_free(d->dict);
    free(d);

    return EXIT_SUCCESS;
}

/* See dictionary.h */
int dict_exists(dict_t *d, char *str) {
    if (d == NULL || d->dict == NULL || str == NULL || str[0] == '\0') {
        log_trace("dict_exists returning EXIT_FAILURE");
        return EXIT_FAILURE;
    }

    log_debug("dict_exists entering trie_contains, word is %s", str);
    int rc = trie_contains(d->dict, str);

    if (rc == 0) {
        return EXIT_SUCCESS;
    }

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

    int rc = trie_insert(d->dict, str);

    if (rc == 0) {
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
        log_trace("dict_read returning EXIT_FAILURE");
        return EXIT_FAILURE;
    }

    while (fscanf(f, "%100s", buffer) == 1) {
        if (dict_add(d, buffer) != EXIT_SUCCESS) {
            log_trace("dict_read returning EXIT_FAILURE");
            return EXIT_FAILURE;
        }
    }

    fclose(f);

    return EXIT_SUCCESS;
}

/* See dictionary.h */
char **dict_suggestions(dict_t *d, char *str, int max_edits, int n) {
    if (d == NULL || d->dict == NULL || str == NULL) {
        log_trace("dict_suggestions returning EXIT_FAILURE");
        return NULL;
    }

    char **results = trie_approx(d->dict, str, max_edits, n);

    return results;
}