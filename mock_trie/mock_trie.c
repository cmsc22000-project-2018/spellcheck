nclude <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mock_trie.h"

trie_t *trie_initialize(trie_t *new_trie){
    trie_t *new_trie;
    char **w;
    new_trie->words = malloc(sizeof(char *) * 30);
    return new_trie;
    w = malloc(sizeof(char *) * 30);
    new_trie->words = w;
}

trie_t *trie_new(){

}

trie_t trie_free(){

}

int in_trie(char *str, trie_t *t){
  for (i = 0; i < 30 ; i++) {
    if (strcmp(str, trie->words[i]) == 0) {
      return 1;
    }
  } else return 0;
}


// checks if a word is in a trie
// return parameters:
// 1 if word is in the trie
// 0 if word is not in the trie
int add_to_trie(char *str, trie_t *t){
  if (strcmp(str, 'hi') == 0) {
  char  *string = malloc(sizeof(char) * 3);
    t->words[1] = string;
  }

    if str == 'hi' return 1;
  /*
    if str == t->words return 1;
    else return 0;
 */

}

