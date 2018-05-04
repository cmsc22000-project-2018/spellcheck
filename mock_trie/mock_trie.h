#ifndef MOCK_TRIE_H
#define MOCK_TRIE_H

#define MAX_WORD_SIZE   40
#define MAX_DESC_SIZE  200

/* A mock-trie struct */
typedef struct {
    char** words;
} trie_t;


/*
 * Allocates a new trie in the heap.
 *
 * Parameters:
 *  - word: Words in the trie
 *
 * Returns:
 *  - A trie, or NULL if a point
 *    cannot be allocated
 */
trie_t* trie_new(char **word);


/*
 * Initializes a trie
 *
 * Parameters:
 *  - new_trie: A trie. Must point to already allocated memory.
 *
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs.
 */
int trie_init(trie_t *new_trie, char **w);


/*
 * Frees the resources associated with a trie
 *
 * Parameters:
 *  - trie: A trie. Must point to a point allocated with segment_new
 *
 * Returns:
 *  - Always returns 0.
 */
int trie_free(trie_t *trie);


/*
 * Checks if a word is in a trie
 *
 * Parameters:
 *  - trie: a trie.
 *
 * Returns:
 *  1 if word is in the trie
 *  0 if word is not in the trie
 */
int in_trie(char *str, trie_t *t);

/*
 * Adds a word to trie
 *
 * Parameters:
 *  - str: a string
 *  - t: a trie.
 *
 * Returns:
 *  1 if word is in the trie
 *  0 if word is not in the trie
 */
int add_to_trie(char *str, trie_t *t);


#endif
