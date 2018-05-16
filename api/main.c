#include <stdio.h>
#include <stdlib.h>

#include "zset_api.h"
/* tests the functionality of the zset api */

int main() {
    zset_t *test_zset = zset_new("fruits");
    zset_add(test_zset, "candy", 42);
    zset_incr(test_zset, "bananas",3);
    zset_decr(test_zset, "bananas", 2);
    zset_score(test_zset, "bananas");
    zset_rank(test_zset, "bananas");
    zset_add(test_zset, "apples", 8);
    zset_add(test_zset, "oranges", 6);
    zset_incr(test_zset, "apples", 2);
    zset_rank(test_zset, "apples");
    zset_rank(test_zset, "bananas"); 
    zset_t *aa = zset_new("aa");
    zset_add(aa, "b", 2);
    zset_rem(aa, "b");
    zset_add(aa, "b", 2);
    zset_add(aa, "c", 3); 
    zset_card(aa);
    zset_free(test_zset);
    zset_free(aa);

    return 0;
}
