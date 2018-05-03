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

/* THIS TRIE ONLY WORKS FOR ONE SENTENCE IN THE TXT FILE, NOT WHOLE DICTIONARY OF WORDS */
/* I consulted the following GitHub link to refactor the trie implementation to help us develop spellcheck */
/* https://github.com/michaelbull/c-dictionary-trie */

/**
* A dictionary is a collection of mappings from WORDs to DESCRIPTIONs
* A WORD is a sequence of characters up to MAX_WORD_SIZE in length
* A DESCRIPTION is a sequence of characters (including spaces) up to
*   MAX_DESC_SIZE in length
*/
/*
void dictionary_initialise();

int dictionary_read_from_file(const char * filename);

int dictionary_lookup(const char * word, char * meaning);
*/

#endif
