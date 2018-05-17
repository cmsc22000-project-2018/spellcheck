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
    zset_t *set = zset_new("set0");
    dict_t *d = dict_new();

    dict_add(d, "cds8Dfk");

    suggestions(set, d, "cds", "c8Dfk", 1);

    cr_assert_eq(zset_rank(set, "cds8Dfk"), 1, "try_delete failed %s", zset_rank(set, "cds8Dfk"));
}

Test(suggestion, delete_s1) {
    zset_t *set = zset_new("set1");
    dict_t *d = dict_new();

    dict_add(d, "cds8Dfk");

    suggestions(set, d, "", "cdisc8Dfk", 2);

    cr_assert_eq(zset_rank(set, "cds8Dfk"), 1, "try_delete failed %i", zset_rank(set, "cds8Dfk"));
}

Test(suggestion, replace_s0) {
    zset_t *set = zset_new("set2");
    dict_t *d = dict_new();

    dict_add(d, "vjikd8-");

    suggestions(set, d, "vji", "ad8-", 1);

    cr_assert_eq(zset_rank(set, "vjiad8-"), 1, "try_replace failed");
}

Test(suggestion, replace_s1) {
    zset_t *set = zset_new("set3");
    dict_t *d = dict_new();

    dict_add(d, "vjikd8-");

    suggestions(set, d, "", "vTik=8?", 2);

    cr_assert_eq(zset_rank(set, "vjikd8-"), 1, "tr_replace failed");
}