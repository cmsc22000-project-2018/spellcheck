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
int trie_init(trie_t *new_trie, char **w){
    assert(new_trie != NULL);

    new_trie->words = w;
    return 1;
}

/*
* See mock_trie.h
*/
trie_t* trie_new(char **word){
    trie_t *new_trie;
    new_trie = malloc(sizeof(trie_t));
    int rc;

    if (new_trie == NULL) {
      error("Could not allocate memory");
      return NULL;
    }
    rc = trie_init(new_trie, word);
    if(rc != 1)
    {
        error("Could not initialize trie");
        return NULL;
    }
    return new_trie;
}

/*
* See mock_trie.h
*/
int trie_free(trie_t *trie){
  assert(trie != NULL);

  free(trie);

  return 1;
}
/*
* See mock_trie.h
*/
int in_trie(char *str, trie_t *t){
  int i;
  for (i = 0; i < 30 ; i++) {
    if (strcmp(str, t->words[i]) == 0) {
      return 1;
    }
  }
  return 0;
}



/*
* See mock_trie.h
*/
int add_to_trie(char *str, trie_t *t){
  char example1[50];
  char example2[60];
  strcpy(example1, "hi");
  strcpy(example2, "dictionaryverysuperduperlongwordyayitssolongwowcrazy");
  if (strcmp(str, example1) == 0) {
  char  *string = malloc(sizeof(char) * 3);
    t->words[1] = string;
    return 1;
  } else if(strcmp(str, example2) == 0) {
    char  *string = malloc(sizeof(char) * 60);
      t->words[1] = string;
      return 1;
  } return 0;
}
