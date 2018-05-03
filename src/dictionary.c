
/*
 * A dictionary data structure based on tries
 *
 * See dictionary.h for function documentation.
 */

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "utils.h"
#include "dictionary.h"

/* See dictionary.h */
dict_t* dict_new(char* file) {
    dict_t *d;
    int rc;

    d = malloc(sizeof(dict_t));

    if (d == NULL) {
        error("Could not allocate memory");
        return NULL;
    }

    rc = dict_init(d, file);
    if (rc != 0) {
        error("Could not initialize polygon");
        return NULL;
    }

    return d;
}

/* See dictionary.h */
int dict_init(dict_t *d, char *file) {
    assert(d != NULL);

    trie_t *t = trie_new();
    if (t == NULL) {
        return 1;
    }
    d->dict = t;

    int rc = 0;

    char buffer[1024];
    FILE *f = fopen(file, "r");
    while (fscanf(f, " %1023s", buffer) == 1) {
        if (add_to_dict(buffer, d) != 1) {
            rc = -1;
        }
    }

    return rc;
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
    assert(d != NULL);
    assert(d->dict != NULL);

    return in_trie(str, d->dict);
}

/* See dictionary.h */
int add_to_dict(char *str, dict_t *d) {
    assert(d != NULL);
    assert(d->dict != NULL);

    return add_to_trie(str, d->dict);
}
