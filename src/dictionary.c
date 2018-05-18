
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

/* See dictionary.h */
dict_t* dict_new() {

    dict_t *d;
    int rc;

    d = malloc(sizeof(dict_t));

    if (d == NULL) {
        return NULL;
    }

    rc = dict_init(d);
    if (rc != EXIT_SUCCESS) {
        return NULL;
    }

    return d;
}

/* See dictionary.h */
int dict_init(dict_t *d) {
    assert(d != NULL);

    trie_t *t = trie_new();
    if (t == NULL) {
        return EXIT_FAILURE;
    }
    d->dict = t;

    char *char_list = (char*)calloc(sizeof(char), 256);
    if (char_list == NULL) {
        return EXIT_FAILURE;
    }
    d->char_list = char_list;

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

    return EXIT_SUCCESS;
}

int dict_chars_exists(dict_t *d, char c) {
    assert(d != NULL);
    assert(d->char_list != NULL);

    // Use the character as the index
    int index = (int)c;

    if (d->char_list[index] == '\0') {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/* See dictionary.h */
int dict_chars_update(dict_t *d, char *str) {
    assert(d != NULL);
    assert(d->char_list != NULL);
    assert(str != NULL);
    
    int i;
    int len = strnlen(str, MAXLEN);

    if (str[len] != '\0') {
        return EXIT_FAILURE;
    }

    for (i = 0; i < len; i++) {
        
        // Use each character as a hash
        int index = (int)str[i];

        d->char_list[index] = str[i];
    }
    
    return EXIT_SUCCESS;
}

/* See dictionary.h */
int dict_exists(dict_t *d, char *str) {
    if (d == NULL || d->dict == NULL || str == NULL || str[0] == '\0') {
        return EXIT_FAILURE;
    }

    return trie_exists(d->dict, str);
}

/* See dictionary.h */
int dict_add(dict_t *d, char *str) {
    if (d == NULL || d->dict == NULL || str == NULL) {
        return EXIT_FAILURE;
    }

    // Attempt to add new characters to the dictionary character list
    if (dict_chars_update(d, str) == EXIT_FAILURE) {
        return EXIT_FAILURE;
    }

    return trie_add(d->dict, str);
}

/* See dictionary.h */
int dict_read(dict_t *d, char *file) {

    // From here: https://stackoverflow.com/questions/16400886/reading-from-a-file-word-by-word
    char buffer[1024];
    FILE *f = fopen(file, "r");

    if (f == NULL) {
        return EXIT_FAILURE;
    }

    while (fscanf(f, "%1023s", buffer) == 1) {
        if (dict_add(d, buffer) != EXIT_SUCCESS) {
            return EXIT_FAILURE;
        }
    }

    fclose(f);

    return EXIT_SUCCESS;
}
