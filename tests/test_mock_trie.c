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

/* Checks the case in which a new word is being added to the trie*/
Test(trie, added_to_trie){
  trie_t *trie1 = trie_new();
  char *s1 = (char *)malloc(sizeof(char) * 3);
  s1 = "hi";
  int added_to_trie = add_to_trie(s1, trie1);
  cr_assert_eq(added_to_trie, 1, "add_to_trie failed");
}

/* Checks the case in which the same word is being tried to add to the trie */
Test(trie, same_variable_add_to_trie){
  trie_t *trie2 = trie_new();
  char *ss1 = (char *)malloc(sizeof(char) * 3);
  ss1 = "hi";
  add_to_trie(ss1, trie2);
  int same_word_add_to_trie2 = add_to_trie(ss1, trie2);
  cr_assert_eq(same_word_add_to_trie2, 0, "add_to_trie failed");
}

/* Checks the case in which the word cannot be added to the trie */
Test(trie, cannot_add_to_trie){
  trie_t *trie3 = trie_new();
  char *sss1 = (char *)malloc(sizeof(char) * 53);
  sss1 = "nojfkdsjfksdjfdsjfkdsjfjfkdsjfkdsjfkdsjkfiejkdjskfsd";
  int cant_add_to_trie = add_to_trie(sss1, trie3);
  cr_assert_eq(cant_add_to_trie, 1, "add_to_trie failed");
}

/* Checks the case in which the word is in the trie */
Test(Trie, in_trie) {
  trie_t *triet = trie_new();
  char *q = (char *)malloc(sizeof(char) * 10);
  char *ss = (char *)malloc(sizeof(char) * 10);
  q =  "hi";
  ss = "hi";
  add_to_trie(q, triet);
  int is_in_trie = in_trie(ss, triet);
  cr_assert_eq(is_in_trie, 1, "in_trie failed");
}

/* Checks the case in which the word is not in the trie*/
Test(Trie, not_in_trie) {
  trie_t *t1 = trie_new();
  char *sq = (char *)malloc(sizeof(char) * 10);
  char *sqq = (char *)malloc(sizeof(char) * 10);
  sq =  "hi";
  sqq = "no";
  add_to_trie(sq, t1);
  int is_in_trie = in_trie(sqq, t1);
  cr_assert_eq(is_in_trie, 0, "in_trie failed");
}
