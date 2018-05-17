#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "suggestion.h"
#include "dictionary.h"


Test(suggestion, has_children_s0) {
    dict_t *d = dict_new();
    dict_add(d, "abc");

    cr_assert_eq(has_children(d, "ab"), 0, "has_children failed");
}

Test(suggestion, has_children_f0) {
    dict_t *d = dict_new();
    dict_add(d, "abc");

    cr_assert_eq(has_children(d, "ac"), 1, "has_children failed");
}

Test(suggestion, delete_s0) {
    zset_t *set = zset_new("set");
    dict_t *d = dict_new();

    dict_add(d, "cds8Dfk");

    suggestions(set, d, "cdsc", "8Dfk", 1);

    cr_assert_eq(zset_rank(set, "cds8Dfk"), 1, "try_delete failed");
}

Test(suggestion, delete_s1) {
    zset_t *set = zset_new("set");
    dict_t *d = dict_new();

    dict_add(d, "cds8Dk");

    suggestions(set, d, "", "cdsc8Dfk", 2);

    cr_assert_eq(zset_rank(set, "cds8Dfk"), 1, "try_delete failed");
}