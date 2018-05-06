#ifndef MOCK_TRIE_H
#define MOCK_TRIE_H

#define MAX_WORD_SIZE   40
#define MAX_DESC_SIZE  200

char words[4][10] = {"Blue", "Red"};
/* A mock-trie struct */
typedef struct {
    char* words;
} trie_t;

void is_word(trie_t *t);

int in_trie(char *str, trie_t *t);




#endif

