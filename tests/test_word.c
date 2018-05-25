#include <criterion/criterion.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "word.h"
#include "dictionary.h"
#include "suggestion.h"


/* testing is_in_array */
Test(word, is_in_array)
{
    char* c = strdup(".");

    int i = is_in_array(c);

    cr_assert_eq(i, 1, "testing for is_in_array, failed");
}

/* testing is_in_array */
Test(word, is_in_array0)
{
    char* c = strdup("p");

    int i = is_in_array(c);

    cr_assert_eq(i, -1, "testing for is_in_array, failed");
}

/* testing word_valid */
Test(word, word_valid)
{
    char* c = strdup(",pac");
    dict_t* dict = NULL;

    int i = word_valid(dict, c);

    cr_assert_eq(i, EXIT_FAILURE, "testing for punctuation, failed");
}

/* testing word_valid */
Test(word, word_valid1)
{
    char* c = strdup(".pac");
    dict_t* dict = NULL;

    int i = word_valid(dict, c);

    cr_assert_eq(i, EXIT_FAILURE, "testing for punctuation, failed");
}

/* testing word_valid */
Test(word, word_valid2)
{
    char* c = strdup("p'ac");
    dict_t* dict = NULL;

    int i = word_valid(dict, c);

    cr_assert_eq(i, EXIT_FAILURE, "testing for punctuation, failed");
}

/* testing generate_suggestions
 * testing currently for hard coded values. change upon dictionary implementation */
Test(word, generate_suggestions)
{
    char* c = strdup("splling");
    char* suggestions[2];
    if (suggestions == NULL) {
        fprintf(stderr,"malloc failed, generate_suggestions");
        exit(0);
    }
    dict_t* dict = NULL;

    int i = generate_suggestions(c, dict, suggestions);

    cr_assert_eq(i, EXIT_SUCCESS, "int return value incorrect");

    i = strncmp("spelling", suggestions[0], 8);
    cr_assert_eq(i, 0, "suggestion output incorrect");
}

/* testing generate_suggestions */
Test(word, generate_suggestions1)
{
    char* c = strdup("life");
    char** suggestions = calloc(2, sizeof(char*));
    if (suggestions == NULL) {
        fprintf(stderr,"malloc failed, generate_suggestions1");
        exit(0);
    }
    dict_t* dict = NULL;

    int i = generate_suggestions(c, dict, suggestions);

    cr_assert_eq(i, EXIT_FAILURE, "int return value incorrect");
}

/* testing generate_suggestions */
Test(word, generate_suggestions2)
{
    char* c = strdup("chequer");
    char** suggestions = calloc(2, sizeof(char*));
    if (suggestions == NULL) {
        fprintf(stderr,"malloc failed, generate_suggestions2");
        exit(0);
    }
    dict_t* dict = NULL;

    int i = generate_suggestions(c, dict, suggestions);

    cr_assert_eq(i, EXIT_SUCCESS, "int return value incorrect");

    i = strncmp("cheque", suggestions[1], 7);
    cr_assert_eq(i, 0, "suggestion output incorrect");
}

/* testing generate_suggestions */
Test(word, generate_suggestions3)
{
    char* c = strdup("cme");
    dict_t* dict = NULL;
    char** suggestions = calloc(2, sizeof(char*));
    if (suggestions == NULL) {
        fprintf(stderr,"malloc failed, generate_suggestions3");
        exit(0);
    }
    int i = generate_suggestions(c, dict, suggestions);

    cr_assert_eq(i, EXIT_SUCCESS, "int return value incorrect");

    i = strncmp("come", suggestions[0], 5);
    cr_assert_eq(i, 0, "suggestion output incorrect");
}