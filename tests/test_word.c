#include <criterion/criterion.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "word.h"
#include "dictionary.h"
#include "log.c/src/log.h"

/* testing valid_word */
Test(word, valid_word)
{
    char* c = strdup("have");
    dict_t* dict = dict_new();
    dict_read(dict, "tests/sample_dict.txt");

    int i = valid_word(dict, c);

    cr_assert_eq(i, true, "testing for punctuation, failed");
}


/* testing valid_word */
Test(word, valid_word0)
{
    char* c = strdup(";checker");
    dict_t* dict = dict_new();
    dict_read(dict, "tests/sample_dict.txt");

    int i = valid_word(dict, c);

    cr_assert_eq(i, false, "testing for punctuation, failed");
}

/* testing valid_word */
Test(word, valid_word1)
{
    char* c = strdup("p'ac");
    dict_t* dict = dict_new();
    dict_read(dict, "tests/sample_dict.txt");

    int i = valid_word(dict, c);

    cr_assert_eq(i, false, "testing for punctuation, failed");
}

/* testing valid_word */
Test(word, valid_word2)
{
    char* c = strdup("ac");
    dict_t* dict = dict_new();
    dict_read(dict, "tests/sample_dict.txt");

    int i = valid_word(dict, c);

    cr_assert_eq(i, false, "testing for punctuation, failed");
}

/* testing generate_suggestions
 * testing currently for hard coded values. change upon dictionary implementation */
Test(word, generate_suggestions)
{
    char* c = strdup("splling");
    char** suggestions = calloc(2, sizeof(char*));
    if (suggestions == NULL) {
        fprintf(stderr,"malloc failed, generate_suggestions");
        exit(0);
    }
    dict_t* dict = dict_new();
    dict_read(dict, "tests/sample_dict.txt");

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
    dict_t* dict = dict_new();
    dict_read(dict, "tests/sample_dict.txt");

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
    dict_t* dict = dict_new();
    dict_read(dict, "tests/sample_dict.txt");

    int i = generate_suggestions(c, dict, suggestions);

    cr_assert_eq(i, EXIT_SUCCESS, "int return value incorrect");

    i = strncmp("cheque", suggestions[1], 7);
    cr_assert_eq(i, 0, "suggestion output incorrect");
}

/* testing generate_suggestions */
Test(word, generate_suggestions3)
{
    char* c = strdup("cme");
    char** suggestions = calloc(2, sizeof(char*));
    if (suggestions == NULL) {
        fprintf(stderr,"malloc failed, generate_suggestions3");
        exit(0);
    }
    dict_t* dict = dict_new();
    dict_read(dict, "tests/sample_dict.txt");

    int i = generate_suggestions(c, dict, suggestions);

    cr_assert_eq(i, EXIT_SUCCESS, "int return value incorrect");

    i = strncmp("come", suggestions[0], 5);
    cr_assert_eq(i, 0, "suggestion output incorrect");
}

/* testing generate_suggestions */
Test(word, generate_suggestions4)
{
    char* c = strdup("cme");
    char** suggestions = calloc(2, sizeof(char*));
    if (suggestions == NULL) {
        fprintf(stderr,"malloc failed, generate_suggestions3");
        exit(0);
    }
    dict_t* dict = NULL;

    int i = generate_suggestions(c, dict, suggestions);

    cr_assert_eq(i, EXIT_FAILURE, "int return value incorrect");

    i = strncmp("no suggestions", suggestions[0], 14);
    cr_assert_eq(i, 0, "suggestion output incorrect");
}
