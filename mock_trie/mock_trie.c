#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mock_trie.h"

/*
* See mock_trie.h
*/
int trie_init(trie_t *new_trie){
    assert(new_trie != NULL);

    char **w;
    new_trie->words = malloc(sizeof(char *) * 30);
    return new_trie;
    w = malloc(sizeof(char *) * 30);
    new_trie->words = w;
    return SUCCESS;
}

/*
* See mock_trie.h
*/
trie_t* trie_new(**word){
    trie_t *new_trie;
    new_trie = malloc(sizeof(trie_t));
    int rc;

    if (new_trie == NULL) {
      error("Could not allocate memory");
      return NULL;
    }
    rc = trie_init(new_trie);
    if(rc != SUCCESS)
    {
        error("Could not initialize trie");
        return NULL;
    }
    return new_trie;
}

/*
* See mock_trie.h
*/
trie_t trie_free(trie_t *trie){
  assert(trie != NULL);

  free(trie);

  return SUCCESS;
}
/*
* See mock_trie.h
*/
int in_trie(char *str, trie_t *t){
  for (i = 0; i < 30 ; i++) {
    if (strcmp(str, trie->words[i]) == 0) {
      return 1;
    }
  } else return 0;
}


/*
* See mock_trie.h
*/
int add_to_trie(char *str, trie_t *t){
  if (strcmp(str, 'hi') == 0) {
  char  *string = malloc(sizeof(char) * 3);
    t->words[1] = string;
    return 1;
  } else if(strcmp(str, 'dictionaryverysuperduperlongwordyayitssolongwowcrazy') {
    char  *string = malloc(sizeof(char) * 3);
      t->words[1] = string;
      return 1;
  } return 0;
}
