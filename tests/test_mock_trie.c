#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "mock_trie.h"
#include <string.h>
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
  //  char** words = malloc(sizeof(char *) * 70);

    rc = trie_init(&new_trie);

    cr_assert_eq(rc, EXIT_SUCCESS, "trie_init() failed");

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

    cr_assert_eq(rc, EXIT_SUCCESS, "trie_free() failed");
}

/* Checks the case in which a new word is being added to the trie*/
Test(trie, added_to_trie){
  trie_t *trie1 = trie_new();
  char *s1 = (char *)malloc(sizeof(char) * 3);
  s1 = "hi";
  int added_to_trie = trie_add(trie1, s1);
  cr_assert_eq(added_to_trie, EXIT_SUCCESS, "trie_add failed");
}

/* Checks the case in which the same word is being tried to add to the trie */
Test(trie, same_variable_trie_add){
  trie_t *trie2 = trie_new();
  char *ss1 = (char *)malloc(sizeof(char) * 3);
  ss1 = "hi";
  trie_add(trie2, ss1);
  int same_word_trie_add2 = trie_add(trie2, ss1);
  cr_assert_eq(same_word_trie_add2, EXIT_FAILURE, "trie_add failed");
}

/* Checks the case in which the word cannot be added to the trie */
Test(trie, cannot_trie_add){
  trie_t *trie3 = trie_new();
  char *sss1 = (char *)malloc(sizeof(char) * 53);
  sss1 = "nojfkdsjfksdjfdsjfkdsjfjfkdsjfkdsjfkdsjkfiejkdjskfsd";
  int cant_trie_add = trie_add(trie3, sss1);
  cr_assert_eq(cant_trie_add, EXIT_FAILURE, "trie_add failed");
}

/* Checks the case in which the word is in the trie */
Test(trie, trie_exists) {
  trie_t *triet = trie_new();
  char *q = (char *)malloc(sizeof(char) * 10);
  char *ss = (char *)malloc(sizeof(char) * 10);
  q =  "hi";
  ss = "hi";
  trie_add(triet, q);
  int is_trie_exists = trie_exists(triet, ss);
  cr_assert_eq(is_trie_exists, EXIT_SUCCESS, "trie_exists failed");
}

/* Checks the case in which the word is not in the trie*/
Test(trie, not_trie_exists) {
  trie_t *t1 = trie_new();
  char *sq = (char *)malloc(sizeof(char) * 10);
  char *sqq = (char *)malloc(sizeof(char) * 10);
  sq =  "hi";
  sqq = "no";
  trie_add(t1, sq);
  int is_trie_exists = trie_exists(t1, sqq);
  cr_assert_eq(is_trie_exists, EXIT_FAILURE, "trie_exists failed");
}
