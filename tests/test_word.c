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

/* testing word_check_cap */
Test(word, word_check_cap)
{
    char* c = "word";

    int i = word_check_cap(c);

    cr_assert_eq(i, 0, "no letter is capitalized, should return 0");
}

/* testing word_check_cap */
Test(word, word_check_cap1)
{
    char* c = "Word";

    int i = word_check_cap(c);

    cr_assert_eq(i, 1, "First letter is capitalized, should return 1");
}

/* testing word_check_cap */
Test(word, word_check_cap2)
{
    char* c = "\"!?";

    int i = word_check_cap(c);

    cr_assert_eq(i, -1, "capitalization not properly identified; should return -1");
}

/* testing word_check_cap */
Test(word, word_check_cap3)
{
    char* c = "'Twas";

    int i = word_check_cap(c);

    cr_assert_eq(i, 1, "First letter is capitalized, should return 1");
}

/* testing word_check_cap */
Test(word, word_check_cap4)
{
    char* c = "it's";

    int i = word_check_cap(c);

    cr_assert_eq(i, 0, "capitalization not properly identified; should return 0");
}

/* testing word_check_cap */
Test(word, word_check_cap5)
{
    char* c = "'TWAS";

    int i = word_check_cap(c);

    cr_assert_eq(i, 2, "capitalization not properly identified; should return 2");
}

/* testing word_check_cap */
Test(word, word_check_cap6)
{
    char* c = "WORDIT";

    int i = word_check_cap(c);

    cr_assert_eq(i, 2, "capitalization not properly identified; should return 2");
}

/* testing word_check_cap */
Test(word, word_check_cap7)
{
    char* c = "VERD'IT";

    int i = word_check_cap(c);

    cr_assert_eq(i, 2, "capitalization not properly identified; should return 2");
}

/* testing word_check_cap */
Test(word, word_check_cap8)
{
    char* c = "tEStINg";

    int i = word_check_cap(c);

    cr_assert_eq(i, 3, "capitalization not properly identified; should return 3");
}

/* testing word_check_cap */
Test(word, word_check_cap9)
{
    char* c = "PoSeiDon";

    int i = word_check_cap(c);

    cr_assert_eq(i, 3, "capitalization not properly identified; should return 3");
}

/* testing word_lowercase */
Test(word, word_lowercase)
{
    char* c = "Length";

    int i = strcmp(word_lowercase(c), "length");

    cr_assert_eq(i, 0, "decapitalization failed");
}

/* testing word_lowercase */
Test(word, word_lowercase3)
{
    char* c = "DYNAMITE";

    int i = strcmp(word_lowercase(c), "dynamite");

    cr_assert_eq(i, 0, "decapitalization failed");
}

/* testing word_lowercase */
Test(word, word_lowercase4)
{
    char* c = "Plymouth";

    int i = strcmp(word_lowercase(c), "plymouth");

    cr_assert_eq(i, 0, "decapitalization incorrect");
}

/* testing words_uppercase */
Test(word, words_uppercase)
{
    char** c = calloc(3, sizeof(char*));
    c[0] = strdup("onepiece");
    c[1] = strdup("twopiece");

    words_uppercase(c, 1);

    int i = strcmp(c[0], "Onepiece");

    cr_assert_eq(i, 0, "recapitalization failed");
}

/* testing words_uppercase */
Test(word, words_uppercase1)
{
    char** c = calloc(3, sizeof(char*));
    c[0] = strdup("onepiece");
    c[1] = strdup("twopiece");

    words_uppercase(c, 2);
    int i = strcmp(c[1], "TWOPIECE");

    cr_assert_eq(i, 0, "recapitalization failed");
}

/* testing words_uppercase */
Test(word, words_uppercase2)
{
    char** c = calloc(3, sizeof(char*));
    c[0] = strdup("onepiece");
    c[1] = strdup("twopiece");

    words_uppercase(c, 3);

    int i = strcmp(c[0], "onepiece");

    cr_assert_eq(i, 0, "recapitalization failed");
}

/* testing words_uppercase */
Test(word, words_uppercase3)
{
    char** c = calloc(3, sizeof(char*));
    c[0] = strdup("one'piece");
    c[1] = strdup("two'piece");

    words_uppercase(c, 1);

    int i = strcmp(c[0], "One'piece");

    cr_assert_eq(i, 0, "recapitalization failed");
}

/* testing words_uppercase */
Test(word, words_uppercase4)
{
    char** c = calloc(3, sizeof(char*));
    c[0] = strdup("one''piece'");
    c[1] = strdup("two''piece'");

    words_uppercase(c, 2);

    int i = strcmp(c[0], "ONE''PIECE'");

    cr_assert_eq(i, 0, "recapitalization failed");
}

/*
 * generate_suggestions testing
 */

Test(word, generate_suggestions)
{
    char* c = "splling";
    dict_t* dict = dict_new();
    int i = dict_read(dict, "tests/sample_dict.txt");
    cr_assert_eq(i, EXIT_SUCCESS, "dict_read failed");

    char** list = generate_suggestions(dict, c, 2, 2);

    cr_assert_not_null(list, "generate_suggestions returns null");

    cr_assert_not_null(list[0], "generate_suggestions[0] is null");
}

Test(word, generate_suggestions1)
{
    char* c = "splling";
    dict_t* dict = dict_new();
    int i = dict_read(dict, "tests/sample_dict.txt");
    cr_assert_eq(i, EXIT_SUCCESS, "dict_read failed");

    char** list = generate_suggestions(dict, c, 2, 2);

    cr_assert_not_null(list, "generate_suggestions returns null");

    cr_assert_not_null(list[0], "generate_suggestions[0] is null");
}