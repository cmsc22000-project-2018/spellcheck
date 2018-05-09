#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "mock_trie.h"
#include "utils.h"

/*
* See mock_trie.h
*/
trie_t* trie_new(){
    trie_t *t;
    t = malloc(sizeof(trie_t));
    int rc;

    if (t == NULL) {
      error("Could not allocate memory");
      return NULL;
    }

    rc = trie_init(t);
    if(rc != EXIT_SUCCESS)
    {
        error("Could not initialize trie");
        return NULL;
    }
    return t;
}

/*
* See mock_trie.h
*/
int trie_init(trie_t *t){
    assert(t != NULL);

    char **w;
    w = calloc(TRIE_LEN, sizeof(char*));
    if (w == NULL) {
        return EXIT_FAILURE;
    }

    t->words = w;
    return EXIT_SUCCESS;
}

/*
* See mock_trie.h
*/
int trie_free(trie_t *t){
    assert(t != NULL);
    assert(t->words != NULL);

    int i;

    for (i = 0; i < TRIE_LEN; i++) {
        if (t->words[i] != NULL) {
            free(t->words[i]);
        }
    }

    free(t->words);
    free(t);

    return EXIT_SUCCESS;
}

/*
* See mock_trie.h
*/
int trie_exists(trie_t *t, char *str) {
    int i;
    int len = strlen(str);

    for (i = 0; i < TRIE_LEN ; i++) {
        if (t->words[i] == NULL) return 0;
        if (strncmp(str, t->words[i], WORD_LEN) == 0) {
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

/*
* See mock_trie.h
*/
int trie_add(trie_t *t, char *str){
    int i = 0;
    int len = strlen(str);

    while (i < LEN && t->words[i] != NULL) {
        if (strncmp(str, t->words[i], WORD_LEN) == 0) {
            return EXIT_FAILURE;
        }
        i++;
    }

    if (i < LEN) {
        char *w;
        w = malloc(sizeof(char) * strlen(str) + 1);
        if (w == NULL) {
            return EXIT_FAILURE;
        }

        strncpy(w, str, strlen(str) + 1);

        t->words[i] = w;

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
