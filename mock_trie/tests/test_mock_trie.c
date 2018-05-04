#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mock_trie.h"

/* Checks whether a new trie is properly created */
Test(trie, new)
{
    trie_t *new_trie;
    char** word = malloc(sizeof(char *) * 70);

    new_trie = trie_new(word);

    cr_assert_not_null(new_trie, "trie_new() failed");
}

/* Checks whether a trie is initiated properly */
Test(trie, init)
{
    int rc;
    trie_t new_trie;
    char** words = malloc(sizeof(char *) * 70);

    rc = trie_init(&new_trie, words);

    cr_assert_eq(rc, 1, "trie_init() failed");

}

/* Checks whether the trie is correctly freed */
Test(trie, free)
{
    trie_t *new_trie;
    char** wordss = malloc(sizeof(char *) * 70);
    int rc;

    new_trie = trie_new(wordss);

    cr_assert_not_null(new_trie, "trie_new() failed");

    rc = trie_free(new_trie);

    cr_assert_eq(rc, 1, "trie_free() failed");
}
