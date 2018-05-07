/*
 * A dictionary data structure based on tries
 *
 * See dictionary.h for function documentation.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include "utils.h"
#include "dictionary.h"

/* See dictionary.h */
dict_t* dict_new() {

    dict_t *d;
    int rc;

    d = malloc(sizeof(dict_t));

    if (d == NULL) {
        error("Could not allocate memory");
        return NULL;
    }

    rc = dict_init(d);
    if (rc != 0) {
        error("Could not initialize dict");
        return NULL;
    }

    return d;
}

/* See dictionary.h */
int dict_init(dict_t *d) {
    assert(d != NULL);

    trie_t *t = trie_new();
    if (t == NULL) {
        return 1;
    }
    d->dict = t;

    return 0;
}

/* See dictionary.h */
int dict_free(dict_t *d) {
    assert(d != NULL);
    assert(d->dict != NULL);

    trie_free(d->dict);
    free(d);

    return 0;
}

/* See dictionary.h */
int in_dict(char *str, dict_t *d) {
    if (d == NULL || d->dict == NULL || str == NULL || str[0] == '\0') {
        error("Invalid input to in_dict");
        return -1;
    }

    return in_trie(str, d->dict);
}

/* See dictionary.h */
int add_to_dict(char *str, dict_t *d) {
    if (d == NULL || d->dict == NULL || str == NULL) {
        error("Invalid arguments to add_to_dict");
        return -1;
    }

    return add_to_trie(str, d->dict);
}

/* See dictionary.h */
int read_to_dict(char *file, dict_t *d) {

    int rc = 1;

    // From here: https://stackoverflow.com/questions/16400886/reading-from-a-file-word-by-word
    char buffer[1024];
    FILE *f = fopen(file, "r");

    if (f == NULL) {
        return 0;
    }

    while (fscanf(f, "%1023s", buffer) == 1) {
        if (add_to_dict(buffer, d) != 1) {
            rc = -1;
        }
    }

    fclose(f);

    return rc;
}
