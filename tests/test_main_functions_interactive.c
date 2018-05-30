#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main_functions_edit.h"
#include <string.h>

/* Note on testing for main_functions_*.c files:
 * Note that there are five parts to main_functions.c: saving, editing, interactive, batch, main.
 * The functions that do not require command line inputs have been tested in the test_main_functions files.
 * The functions that do require command line inputs are currently being researched by Deniz Turkcapar,
 * but currently use a simpler testing version, via command lines accepted in travis, to ensure that
 * each function responsible for printing a page prints a correct output.
 * For this reason, test_main_functions_interactive.c does not exist, given that the edit_interactive function, and
 * the wrapper interactive_mode function, cannot operate without command line inputs.
 */


/*
 ***** add_to_misspelled tests *****
 */
void check_add_to_misspelled(char *word, char** misspelled) {
	add_to_misspelled(word, misspelled);
	int result = -1;
	int i = 0;
	while (misspelled[i] != NULL) {
		if (strcmp(misspelled[i], word) == 0) {
			result = 0;
		}
		i++;
	}

	cr_assert_eq(0, result, "check_add_to_badwords failed");

}

Test(main_functions_edit, check_add_to_misspelled) {
	char *badword = "wrod";
	char* badwords[3] = {NULL, NULL, NULL};
	check_add_to_misspelled(badword, badwords);

}

/*
 ***** correct_line tests *****
 */
void test_correct_line(char* line, char* old_word, char* new_word, char* expected) {

	char* corrected = correct_line(line, old_word, new_word);

	int result = strcmp(corrected, expected);

    cr_assert_eq(result, 0, "correct_line test failed");
}

Test(main_functions_edit, correct_line1) {
	char *line_code = "I don't know hw to spell";
	char *line = (char *)malloc(strlen(line_code)+1);
	strcpy(line, line_code);
	char *old_word_code = "hw";
	char *old_word = (char *)malloc(strlen(old_word_code)+1);
	strcpy(old_word, old_word_code);
	char *new_word_code = "how";
	char *new_word = (char *)malloc(strlen(new_word_code)+1);
	strcpy(new_word, new_word_code);

	char *expected = "I don't know how to spell";
    test_correct_line(line, old_word, new_word, expected);
}

Test(main_functions_edit, correct_line2) {
	char *line_code = "I dont know how to spell";
	char *line = (char *)malloc(strlen(line_code)+1);
	strcpy(line, line_code);
	char *old_word_code = "dont";
	char *old_word = (char *)malloc(strlen(old_word_code)+1);
	strcpy(old_word, old_word_code);
	char *new_word_code = "don't";
	char *new_word = (char *)malloc(strlen(new_word_code)+1);
	strcpy(new_word, new_word_code);

	char *expected = "I don't know how to spell";
    test_correct_line(line, old_word, new_word, expected);
}

Test(main_functions_edit, correct_line3) {
	char *line_code = "spl";
	char *line = (char *)malloc(strlen(line_code)+1);
	strcpy(line, line_code);
	char *old_word_code = "spl";
	char *old_word = (char *)malloc(strlen(old_word_code)+1);
	strcpy(old_word, old_word_code);
	char *new_word_code = "spell";
	char *new_word = (char *)malloc(strlen(new_word_code)+1);
	strcpy(new_word, new_word_code);

	char *expected = "spell";
    test_correct_line(line, old_word, new_word, expected);
}


/*
 ***** underline_misspelled_sentence tests *****
 */
void check_underline_misspelled_sentence(char** badwords, char* sentence, char* underline, char* expected) {
	char *underlined = underline_misspelled_sentence(badwords, sentence, underline);

	int result = strcmp(underlined, expected);

    cr_assert_eq(result, 0, "underline_misspelled test failed");
}

Test(main_functions_edit, underline_misspelled_sentence) {
	char **badwords = (char **)malloc((sizeof(char*)*3));
	char *line = "bd splling is bad";
	char *underline = (char *)malloc(sizeof(char) * (strlen(line) + 1));
	badwords[0] = "bd";
	badwords[1] = "splling";
	badwords[2] = NULL;
	
	char *expected = "^^ ^^^^^^^";
    check_underline_misspelled_sentence(badwords, line,underline, expected);
}


Test(main_functions_edit, underline_misspelled_sentence2) {
	char *line = "bd splling is bd";
	char **badwords = (char **)malloc((sizeof(char*)*4));
	char *underline = (char *)malloc(sizeof(char) * (strlen(line) + 1));
	badwords[0] = "bd";
	badwords[1] = "splling";
	badwords[2] = "bd";
	badwords[3] = NULL;
	

	char *expected = "^^ ^^^^^^^    ^^";
    check_underline_misspelled_sentence(badwords, line, underline, expected);
}


/*
 ***** is_in_punct_array tests *****
 */

void check_is_in_punct_array(char letter, int expected) {
	int result = is_in_punct_array(letter);

    cr_assert_eq(expected, result, "check_is_in_punct_array test failed");
}


Test(main_functions_edit, is_in_punct_array) {
    check_is_in_punct_array('"', EXIT_SUCCESS);
}

Test(main_functions_edit, is_in_punct_array3) {
    check_is_in_punct_array('?', EXIT_SUCCESS);
}

Test(main_functions_edit, is_in_punct_array4) {
    check_is_in_punct_array('0', EXIT_FAILURE);
}


Test(main_functions_edit, is_in_punct_array2) {
    check_is_in_punct_array('a', EXIT_FAILURE);
}


/*
 ***** remove_prefix_punctuation tests *****
 */

void check_remove_prefix_punctuation(char* word, char* expected) {
	remove_prefix_punctuation(word);

	int result = strcmp(word, expected);

    cr_assert_eq(result, 0, "remove_prefix_punctuation test failed");
}

Test(main_functions_edit, remove_prefix_punctuation) {
	char buffer[8] = "...words";
    char* expected = "words"; 
    check_remove_prefix_punctuation(buffer, expected);
}

Test(main_functions_edit, remove_prefix_punctuation2) {
	char buffer[7] = "..words";
    char* expected = "words"; 
    check_remove_prefix_punctuation(buffer, expected);
}

Test(main_functions_edit, remove_prefix_punctuation3) {
	char buffer[9] = "??words?";
    char* expected = "words?"; 
    check_remove_prefix_punctuation(buffer, expected);
}

/*
 ***** remove_trailing_punctuation tests *****
 */

void check_remove_trailing_punctuation(char* word, char* expected) {
	remove_trailing_punctuation(word);

	int result = strcmp(word, expected);

    cr_assert_eq(result, 0, "remove_trailing_punctuation test failed");
}

Test(main_functions_edit, remove_trailing_punctuation1) {
    char* sample = "...words...";
    char *buffer = (char *) malloc(sizeof(char) * (strlen(sample) + 1));
	strcpy(buffer, sample);
    char* expected = "...words"; 
    check_remove_trailing_punctuation(buffer, expected);
}

Test(main_functions_edit, remove_trailing_punctuation2) {
	char buffer[6] = "words.";
    char* expected = "words"; 
    check_remove_trailing_punctuation(buffer, expected);
}

Test(main_functions_edit, remove_trailing_punctuation3) {
	char buffer[8] = "??words?";
    char* expected = "??words"; 
    check_remove_trailing_punctuation(buffer, expected);
}

Test(main_functions_edit, remove_trailing_punctuation4) {
    char* sample = "words.!?!?!.";
    char *buffer = (char *) malloc(sizeof(char) * (strlen(sample) + 1));
	strcpy(buffer, sample);
    char* expected = "words"; 
    check_remove_trailing_punctuation(buffer, expected);
}