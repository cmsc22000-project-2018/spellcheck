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


/* testing word_cap_status */
Test(word, word_cap_status)
{
    cr_assert_eq(word_cap_status('L'), 1, "capitalization not properly identified");
}

/* testing word_cap_status */
Test(word, word_cap_status1)
{
    cr_assert_eq(word_cap_status('Z'), 1, "capitalization not properly identified");
}

/* testing word_cap_status */
Test(word, word_cap_status2)
{
    cr_assert_eq(word_cap_status('!'), 0, "punctuation; should fail");
}

/* testing word_cap_status */
Test(word, word_cap_status3)
{
    cr_assert_eq(word_cap_status('a'), 0, "non_capitalized; should fail");
}

/* testing word_cap_status */
Test(word, word_cap_status4)
{
    cr_assert_eq(word_cap_status(' '), 0, "non_capitalized; should fail");
}

/* testing word_cap_status */
Test(word, word_cap_status5)
{
    cr_assert_eq(word_cap_status('.'), 0, "punctuation; should fail");
}

/* testing word_cap_status */
Test(word, word_cap_status6)
{
    cr_assert_eq(word_cap_status('a'), 0, "non_capitalized; should fail");
}

/* testing word_check_cap */
Test(word, word_check_cap)
{
    char* c = "word";

    int i = word_check_cap(c);

    cr_assert_eq(i, 0, "capitalization not properly identified; should return 0");
}

/* testing word_check_cap */
Test(word, word_check_cap1)
{
    char* c = "Word";

    int i = word_check_cap(c);

    cr_assert_eq(i, 0, "capitalization not properly identified; should return 0");
}

/* testing word_check_cap */
Test(word, word_check_cap2)
{
    char* c = "\"";

    int i = word_check_cap(c);

    cr_assert_eq(i, -1, "capitalization not properly identified; should return -1");
}

/* testing word_check_cap */
Test(word, word_check_cap3)
{
    char* c = "'Twas";

    int i = word_check_cap(c);

    cr_assert_eq(i, 1, "capitalization not properly identified; should return 1");
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
    char* c = "WORDIT";

    int i = word_check_cap(c);

    cr_assert_eq(i, 2, "capitalization not properly identified; should return 2");
}

/* testing word_check_cap */
Test(word, word_check_cap8)
{
    char* c = "WORDIT";

    int i = word_check_cap(c);

    cr_assert_eq(i, 2, "capitalization not properly identified; should return 2");
}

/* testing word_check_cap */
Test(word, word_check_cap9)
{
    char* c = "PoSeiDon";

    int i = word_check_cap(c);

    cr_assert_eq(i, 3, "capitalization not properly identified; should return 3");
}

/* testing word_check_cap */
Test(word, word_check_cap10)
{
    char* c = "aTHena";

    int i = word_check_cap(c);

    cr_assert_eq(i, 3, "capitalization not properly identified; should return 3");
}

/* testing word_check_cap */
Test(word, word_check_cap11)
{
    char* c = "'TH'OUGHT";

    int i = word_check_cap(c);

    cr_assert_eq(i, 2, "capitalization not properly identified; should return 2");
}

/* testing word_decap */
Test(word, word_decap)
{
    char* c = "Length";

    int i = strcmp(word_decap(c), "length");

    cr_assert_eq(i, 0, "decapitalization failed");
}

/* testing word_decap */
Test(word, word_decap1)
{
    char* c = "Length";

    int i = strcmp(word_decap(c), "length");

    cr_assert_eq(i, 0, "decapitalization failed");
}

/* testing word_decap */
Test(word, word_decap2)
{
    char* c = "Tin'Ny";

    int i = strcmp(word_decap(c), "tin'ny");

    cr_assert_eq(i, 0, "decapitalization failed");
}

/* testing word_decap */
Test(word, word_decap3)
{
    char* c = "DYNAMITE";

    int i = strcmp(word_decap(c), "dynamite");

    cr_assert_eq(i, 0, "decapitalization failed");
}

/* testing word_decap */
Test(word, word_decap4)
{
    char* c = "plymouth";

    int i = strcmp(word_decap(c), "plymouth");

    cr_assert_eq(i, 0, "decapitalization failed");
}

// To be written more, after implementation
Test(word, word_recap)
{
/* sample
    flag 1
    char* c = "checkout";
    word_recap(c, 1);

 */


}

/* testing generate_suggestions */
Test(word, generate_suggestions)
{
    char* c = strdup("splling");
    char* suggestions[2];
    if (suggestions == NULL) {
        fprintf(stderr,"malloc failed, generate_suggestions");
        exit(0);
    }
    dict_t* dict = dict_new();
    int i = dict_read(dict, "text1.txt");
    assert(i != EXIT_FAILURE);

    i = generate_suggestions(dict, c, suggestions, 2, 2);

    cr_assert_eq(i, EXIT_SUCCESS, "int return value incorrect");

    i = strncmp("spelling", suggestions[0], 8);
    cr_assert_eq(i, 0, "suggestion output incorrect");
}