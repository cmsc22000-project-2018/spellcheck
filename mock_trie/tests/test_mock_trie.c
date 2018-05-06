#include <criterion/criterion.h>
#include <stdlib.h>
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

Test(string, compare){
  char *s1 = malloc(sizeof(char*));
  char *s2 = malloc(sizeof(char*));
  strcpy(s1, "hi");
  strcpy(s2, "hi");

  int result = compstr(s1, s2);
  printf("%d\n", result);
  cr_assert_eq(result, 1, "compstr failed");
}

Test(string, compare_different){
  char *s11 = malloc(sizeof(char*));
  char *s22 = malloc(sizeof(char*));
  strcpy(s11, "hi");
  strcpy(s22, "day");

  int results = compstr(s11, s22);
  printf("%d\n", results);
  cr_assert_eq(results, 0, "compstr failed");
}

Test(trie, added_to_trie){
  trie_t *trie1 = trie_new();
  char *s1 = (char *)malloc(sizeof(char));
  strcpy(s1, "hi");
  int added_to_trie = add_to_trie(s1, trie1);
  printf("%d\n", added_to_trie);
  cr_assert_eq(added_to_trie, 1, "add_to_trie failed");
}

Test(trie, same_variable_add_to_trie){
  trie_t *trie2 = trie_new();
  char *ss1 = (char *)malloc(sizeof(char));
  strcpy(ss1, "hi");
  int same_word_add_to_trie = add_to_trie(ss1, trie2);
  int same_word_add_to_trie2 = add_to_trie(ss1, trie2);
  cr_assert_eq(same_word_add_to_trie2, 0, "add_to_trie failed");
}

Test(trie, cannot_add_to_trie){
  trie_t *trie3 = trie_new();
  char *sss1 = (char *)malloc(sizeof(char));
  strcpy(sss1, "asdfghjkljhgfdsxcvbnkuytfdfghjkjhgfdcvbnmjhgfdscvbnjhgfdcvbnhgfdcvb");
  int cant_add_to_trie = add_to_trie(sss1, trie3);
  cr_assert_eq(cant_add_to_trie, -1, "add_to_trie failed");
}

/*
Test(Trie, in_trie){
  trie_t *t = trie_new();
  char *s = (char *)malloc(sizeof(char) * 10);
  char *ss = (char *)malloc(sizeof(char) * 10);
  strcpy(ss, "hi");
  strcpy(s, "hi");
  t->words = s;
  int is_in_trie = in_trie(ss, t);
}

Test(Trie, not_in_trie){

}


*/
