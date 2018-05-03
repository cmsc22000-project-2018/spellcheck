#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dictionary.h"

Test(dictionary, new)
{
    dict_t *d;

    d = dict_new();

    cr_assert_not_null(d, "dict_new() failed");
}

Test(dictionary, init)
{
    dict_t *d;
    int rc;

    d = dict_new();

    rc = dict_init(d, "init_test.txt");

    cr_assert_eq(rc, 0, "dict_init() failed");
}

Test(dictionary, free)
{
    dict_t *d;
    int rc;

    d = dict_new();

    cr_assert_not_null(d, "dict_new() failed");

    rc = dict_free(d);

    cr_assert_eq(rc, 0, "dict_free() failed");
}

/* Test arg 1 for null input for in_dict */
Test(dictionary, in_dict_null) {
    dict_t *d;
    int rc;

    d = dict_new("dict_test0.txt");

    rc = in_dict(NULL, d);

    cr_assert_eq(rc, -1, "Passing NULL in as a string in in_dict should have "
                 "returned -1, but it returned %d", rc);
}

/* Test arg 2 for null input for in_dict */
Test(dictionary, in_dict_null) {
    int rc;

    rc = in_dict("hi", NULL);

    cr_assert_eq(rc, -1, "Passing NULL in as a dictionary in in_dict should have "
                 "returned -1, but it returned %d", rc);
}

/* Test empty string input for in_dict */
Test(dictionary, in_dict_empty) {
    dict_t *d;
    int rc;

    d = dict_new("dict_test0.txt");

    rc = in_dict("", d);

    cr_assert_eq(rc, -1, "Passing an empty string in as a dictionary to in_dict "
                 "should have returned -1, but it returned %d", rc);
}

/* Helper function for testing regular input for in_dict */
check_in_dict(char *file, char *str, int expected) {
    dict_t *d;
    int rc;
    char *s;

    d = dict_new(file);
    s = malloc(strlen(str) + 1);
    s = strcpy(s, str);

    rc = in_dict(s, d);

    cr_assert_eq(rc, expected, "String %s in dictionary from %s"
                 "should return %d but in_dict returned %d",
                 s, file, expected, rc);

}

/* Test a small string for success */
Test(dictionary, in_dict_s0) {
    check_in_dict("dict_test0.txt", "hi", 1);
}

/* Test a long string for success */
Test(dictionary, in_dict_s1) {
    check_in_dict("dict_test0.txt", "dictionaryverysuperduperlongwordyayitssolongwowcrazy", 1);
}

/* Test a small string for failure */
Test(dictionary, in_dict_f0) {
    check_in_dict("dict_test0.txt", "no", 0);
}

/* Test a long string for failure */
Test(dictionary, in_dict_f1) {
    check_in_dict("dict_test0.txt", "nojfkdsjfksdjfdsjfkdsjfjfkdsjfkdsjfkdsjkfiejkdjskfsd", 0);
}

