#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mock_trie.h"

/* Checks whether a new trie is properly created */
Test(trie, new)
{
    trie_t *new_trie;
    char** word

    point_t  *center;

    new_trie = trie_new(word);

    cr_assert_not_null(new_trie, "trie_new() failed");
}

/* Checks whether a trie is initiated properly */
Test(trie, init)
{
    trie_t new_trie;

    rc = trie_init(&new_trie);

    cr_assert_eq(rc, SUCCESS, "trie_init() failed");

}

/* Checks whether the trie is correctly freed */
Test(trie, free)
{
    trie_t *new_trie;
    char** word;

    int rc;

    new_trie = trie_new(word);

    cr_assert_not_null(new_trie, "trie_new() failed");

    rc = trie_free(new_trie);

    cr_assert_eq(rc, SUCCESS, "trie_free() failed");
}
