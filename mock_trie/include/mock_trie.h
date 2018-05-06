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
 *
 * Returns:
 *  - 0 on success, 1 if an error occurs.
 */
int trie_init(trie_t *t);


/*
 * Frees the resources associated with a trie
 *
 * Parameters:
 *  - trie: A trie. Must point to a point allocated with segment_new
 *
 * Returns:
 *  - Always returns 0.
 */
int trie_free(trie_t *t);


/*
 * Compares the given two strings to see if they are equal (the same)
 *
 * Parameters:
 *  - s1: a string
 *  - s2: a string
 * Returns:
 *  1 if strings are the same
 *  0 if strings are different
 */
int compstr(char *s1, char *s2);

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
