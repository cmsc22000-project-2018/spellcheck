#ifndef MOCK_TRIE_H
#define MOCK_TRIE_H

#define LEN 30

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
trie_t* trie_new();


/*
 * Initializes a trie
 *
 * Parameters:
 *  - new_trie: A trie. Must point to already allocated memory.
 *
 * Returns:
 *  - EXIT_SUCCESS on success, EXIT_FAILURE if an error occurs.
 */
int trie_init(trie_t *t);


/*
 * Frees the resources associated with a trie
 *
 * Parameters:
 *  - trie: A trie. Must point to a point allocated with segment_new
 *
 * Returns:
 *  - Always returns EXIT_SUCCESS.
 */
int trie_free(trie_t *t);

/*
 * Checks if a word is in a trie
 *
 * Parameters:
 *  - trie: a trie.
 *
 * Returns:
 *  EXIT_SUCCESS if word is in the trie
 *  EXIT_FAILURE if word is not in the trie
 */
int trie_exists(trie_t *t, char *str);

/*
 * Adds a word to trie
 *
 * Parameters:
 *  - str: a string
 *  - t: a trie.
 *
 * Returns:
 *  EXIT_SUCCESS if word is in the trie
 *  EXIT_FAILURE if word is not in the trie
 */
int trie_add(trie_t *t, char *str);


#endif
