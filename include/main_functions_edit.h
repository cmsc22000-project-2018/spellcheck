#ifndef INCLUDE_MAIN_FUNCTIONS_EDIT_H
#define INCLUDE_MAIN_FUNCTIONS_EDIT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dictionary.h"

/**
 * \file main_functions_edit.h
 * String editing functions for the shell.
 */

/**
 * \brief Determines whether a character is a punctuation character or not.
 *
 * \param letter: A character.
 * \return true if the character is a punctuation character, false otherwise.
 */
bool is_in_punct_array(char letter);

/**
 * \brief Removes any punctuation characters at the beginning of a string (word).
 *
 * \param word: A string (word).
 */
void remove_prefix_punctuation(char *word);

/**
 * \brief Removes any punctuation characters at the end of a string (word).
 *
 * \param word: A string (word).
 */
void remove_trailing_punctuation(char *word); 

/**
 * \brief Combines remove_trailing_punctuation() and remove_prefix_punctuation() to remove trailing and prefix punctuation characters without modifying the original word.
 *
 * \param word: A string (word).
 * \return Input string (word) with punctuation characters removed.
 */
char *remove_punctuation(char *word);

/**
 * \brief Underlines a list misspelled words in a given sentence.
 *
 * \param misspelled: Array of strings (list of misspelled words).
 * \param sentence: Dentence to be modified.
 * \param underline: String of underline characters.
 *
 * \return Underline for the misspelled words in the input sentence.
 */
char *underline_misspelled_sentence(char **misspelled, char *sentence, char *underline);

/**
 * \brief Adds a misspelled word to a list of misspelled words.
 *
 * \param word: A string (word).
 * \param misspelled: Array of strings (list of misspelled words).
 *
 * \returns int as pseudo-boolean (EXIT_SUCCESS ot EXIT_FAILURE).
 */
int add_to_misspelled(char *word, char **misspelled);

/**
 * \brief Given a line, generates a list of misspelled words and underlines them.
 *
 * \param string: Line to be parsed.
 * \param dict: Dictionary file being input.
 * \param underline: String of underline characters.
 * \param misspelled: Array of strings (list of misspelled words).
 */
void parse_string(char *string, dict_t *dict, char *underline, char **misspelled);

/**
 * \brief Replaces a word in a line with the word suggestion chosen by the user.
 *
 * \param line: Line to be modified.
 * \param old_word: String (Misspelled word).
 * \param new_word: String (Corrected word).
 * \return Modified (Corrected) line.
 */
char *correct_line(char *line, char *old_word, char *new_word);

#endif