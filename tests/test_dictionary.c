#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dictionary.h"

Test(dictionary, new) {
    dict_t *d;

    d = dict_new();

    cr_assert_not_null(d, "dict_new() failed");
}

Test(dictionary, init) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = dict_init(dict);

    cr_assert_eq(rc, 0, "dict_init() failed");
}

Test(dictionary, free) {
    dict_t *d;
    int rc;

    d = dict_new();

    cr_assert_not_null(d, "dict_new() failed");

    rc = dict_free(d);

    cr_assert_eq(rc, 0, "dict_free() failed");
}

/*
************ add_to_dict tests ****************************
*/

/* Test arg 1 for null input for add_to_dict */
Test(dictionary, add_to_dict_null0) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = add_to_dict(NULL, d);

    cr_assert_eq(rc, -1, "Passing NULL in as a string in add_to_dict should have "
                 "returned -1, but it returned %d", rc);
}

/* Test arg 2 for null input for add_to_dict */
Test(dictionary, add_to_dict_null1) {
    int rc;

    rc = add_to_dict("hi", NULL);

    cr_assert_eq(rc, -1, "Passing NULL in as a dictionary in add_to_dict should have "
                 "returned -1, but it returned %d", rc);
}

/* Test empty string input for add_to_dict */
Test(dictionary, add_to_dict_empty) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = add_to_dict("", d);

    cr_assert_eq(rc, -1, "Passing an empty string in as a dictionary to add_to_dict "
                 "should have returned -1, but it returned %d", rc);
}

/* Helper function for testing regular input for add_to_dict */
check_add_to_dict(char *file, char *str, int expected) {
    dict_t *d;
    int rc;
    char *s;

    d = dict_new();
    s = malloc(strlen(str) + 1);
    s = strcpy(s, str);

    cr_assert_eq(1, read_to_dict(file, d), "Read to dict failed");

    rc = add_to_dict(s, d);

    cr_assert_eq(rc, expected, "Putting string %s in dictionary from %s"
                 "should return %d but add_to_dict returned %d",
                 s, file, expected, rc);
}

/* Test adding a small string for failure */
Test(dictionary, add_to_dict_f0) {
    check_add_to_dict("dict_test0.txt", "hi", 0);
}

/* Test adding a long string for failure */
Test(dictionary, add_to_dict_f0) {
    check_add_to_dict("dict_test0.txt",
                  "dictionaryverysuperduperlongwordyayitssolongwowcrazy", 0);
}

/* Test adding a small string for success */
Test(dictionary, add_to_dict_s0) {
    check_add_to_dict("dict_test0.txt", "no", 1);
}

/* Test adding a long string for success */
Test(dictionary, add_to_dict_s1) {
    check_add_to_dict("dict_test0.txt",
                  "nojfkdsjfksdjfdsjfkdsjfjfkdsjfkdsjfkdsjkfiejkdjskfsd", 1);
}

/*
************ read_to_dict tests ****************************
*/

/* Test arg 1 for null input in read_to_dict */
Test(dictionary, read_to_dict_null0) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = read_to_dict(NULL, d);

    cr_assert_eq(rc, 0, "Passing NULL in as a string in read_to_dict should have "
                 "returned 0, but it returned %d", rc);
}

/* Test arg 2 for null input in read_to_dict */
Test(dictionary, read_to_dict_null1) {
    int rc;

    rc = read_to_dict("dict_test0.txt", NULL);

    cr_assert_eq(rc, 0, "Passing NULL in as a dictionary in read_to_dict should have "
                 "returned 0, but it returned %d", rc);
}

/* Test bad filename input in read_to_dict */
Test(dictionary, read_to_dict_noname) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = read_to_dict("DNE.txt", d);

    cr_assert_eq(rc, 0, "Passing NULL in as a string in read_to_dict should have "
                 "returned 0, but it returned %d", rc);
}

void check_read_to_dict(char *file, int expected) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = read_to_dict(file, d);

    cr_assert_eq(rc, 1, "Passing file %s in read_to_dict should have "
                 "returned %d, but it returned %d", file, expected, rc);
}

/* Test for regular input in read_to_dict 1 */
Test(dictionary, read_to_dict0) {
    check_read_to_dict("dict_test0.txt", 1);
}



/*
************ in_dict tests ****************************
*/

/* Test arg 1 for null input for in_dict */
Test(dictionary, in_dict_null0) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = in_dict(NULL, d);

    cr_assert_eq(rc, -1, "Passing NULL in as a string in in_dict should have "
                 "returned -1, but it returned %d", rc);
}

/* Test arg 2 for null input for in_dict */
Test(dictionary, in_dict_null1) {
    int rc;

    rc = in_dict("hi", NULL);

    cr_assert_eq(rc, -1, "Passing NULL in as a dictionary in in_dict should have "
                 "returned -1, but it returned %d", rc);
}

/* Test empty string input for in_dict */
Test(dictionary, in_dict_empty) {
    dict_t *d;
    int rc;

    d = dict_new();

    rc = in_dict("", d);

    cr_assert_eq(rc, -1, "Passing an empty string in as a dictionary to in_dict "
                 "should have returned -1, but it returned %d", rc);
}

/* Helper function for testing regular input for in_dict */
check_in_dict(char *file, char *str, int expected) {
    dict_t *d;
    int rc;
    char *s;

    d = dict_new();
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
    check_in_dict("dict_test0.txt",
                  "dictionaryverysuperduperlongwordyayitssolongwowcrazy", 1);
}

/* Test a small string for failure */
Test(dictionary, in_dict_f0) {
    check_in_dict("dict_test0.txt", "no", 0);
}

/* Test a long string for failure */
Test(dictionary, in_dict_f1) {
    check_in_dict("dict_test0.txt",
                  "nojfkdsjfksdjfdsjfkdsjfjfkdsjfkdsjfkdsjkfiejkdjskfsd", 0);
}
