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