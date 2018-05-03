/* THIS TRIE ONLY WORKS FOR ONE SENTENCE IN THE TXT FILE, NOT WHOLE DICTIONARY OF WORDS */
/* I consulted the following GitHub link to refactor the trie implementation to help us develop spellcheck */
/* https://github.com/michaelbull/c-dictionary-trie */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mock_trie.h"

/*
#define ALPHABET_SIZE 26

#define false 0
#define true 1

struct trie tree;

struct trie_node
{
    char *value;

    // *2 as we must account for a-z as well as A-Z
    struct trie_node *children[ALPHABET_SIZE * 2];
};

struct trie
{
    struct trie_node root;
};

/**
* Converts a character to an integer value based upon its position in
* the alphabet, or returns -1 if the character is not in the alphabet.
*/

/*
int letter_to_int(char letter)
{
    if (letter >= 'A' && letter <= 'Z')
    {
        return letter - 'A' + 26;
    }
    else if (letter >= 'a' && letter <= 'z')
    {
        return letter - 'a';
    }
    return -1;
}

/**
* Prints and identifies an invalid character in a word
* based upon its index within the word.
*
* e.g.
*   word: "plat%eau"
*              ^
*/
/*
void print_invalid_word(const char *word, int index)
{
    printf("  word: \"%s\"\n", word);
    printf("         ");
    int i;
    for (i = 0; i < index; i++)
    {
        printf(" ");
    }
    printf("^\n");
}

/**
* Inserts a word and its meaning into the trie.
*/
/*
int trie_insert(struct trie_node *node, const char *word, char *description)
{
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        int letter = letter_to_int(word[i]);
        if (letter == -1)
        {
            // invalid character in the string, cannot be inserted into the trie
            printf("failed to insert due to invalid character in word\n");
            print_invalid_word(word, i);
            printf("  description: \"%s\"\n", description);
            return false;
        }

        struct trie_node *parent = node;
        node = node->children[letter];

        if (!node)
        {
            node = malloc(sizeof(struct trie_node));
            parent->children[letter] = node;
        }
    }

    /*
    * this will prove very efficient we are only allocating enough memory
    * for every character in the description, which will save a lot of space
    * that would otherwise be allocated to the full MAX_DESC_SIZE
    */
    /*
    int len = strlen(description);
    node->value = malloc(len + 1);
    strncpy(node->value, description, len);
    return true;
}

/**
* Traverses through a trie from the root node and searches
* for a word's description based on the individual letters
* that make up the word.
*/
/*
char *trie_get(struct trie_node *node, const char *word)
{
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        int letter = letter_to_int(word[i]);
        if (letter == -1)
        {
            return false;
        }

        node = node->children[letter];
        if (!node)
        {
            return false; // not found
        }
    }
    return node->value;
}

void dictionary_initialise()
{
    tree = (struct trie) {}; // zeroes the tree
}

int dictionary_read_from_file(const char * filename)
{
    // attempts to open the file in read only mode
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        printf("could not find/open file \"%s\"\n", filename);
        return false;
    }

    char word[MAX_WORD_SIZE];
    char desc[MAX_DESC_SIZE];

    int count = 0;

    // ensure that at least two items are being parsed (word & desc)
    while (fscanf(file, "%s %[^\n]", word, desc) > 1)
    {
        if (!trie_insert(&tree.root, word, desc))
        {
            fclose(file);
            return false;
        }
        else
        {
            count++;
        }
    }

    fclose(file);
    printf("parsed file \"%s\" with %i entries\n", filename, count);
    return true;
}

int dictionary_lookup(const char *word, char *meaning)
{
    // check for invalid letters in input
    int i;
    for (i = 0; i < strlen(word); i++)
    {
        int letter = letter_to_int(word[i]);
        if (letter == -1)
        {
            printf("invalid character in word\n");
            print_invalid_word(word, i);
            return false;
        }
    }

    // grab the description from the tree
    char *description = trie_get(&tree.root, word);

    if (!description)
    {
        return false;
    }

    // copy the description into the user supplied buffer
    strcpy(meaning, description);

    return true;
}
*/
void is_word(trie_t *t){
    fprintf(stderr, "is_word not implemented yet\n");
    if (t->word == 'b' || t->word == 'B') {
      printf("B\n Bl\n Blu\n Blue\n ");
    }
    if (t->word == 'bl' || t->word == 'BL') {
      printf("Bl\n Blu\n Blue\n");
    }
    if (t->word == 'blu' || t->word == 'BLU') {
      printf("Blu\n Blue\n");
    }
    if (t->word == 'blue' || t->word == 'BLUE') {
      printf("Blue\n");
    }
    if (t->word == 'r' || t->word == 'R') {
      printf("R\n Re\n Red\n");
    }
    if (t->word == 're' || t->word == 'RE') {
      printf("Re\n Red\n");
    }
    if (t->word == 'red' || t->word == 'RED') {
      printf("Red\n");
    }
    else printf("Error: Not a word in the dictionary\n");
}

// checks if a word is in a trie
// return parameters:
// 1 if word is in the trie
// 0 if word is not in the trie
int in_trie(char *str, trie_t *t){
    fprintf(stderr, "in_trie not implemented yet\n");
    return 0;
  /*
    if str == t->words return 1;
    else return 0;
 */

}
