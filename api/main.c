#include <stdio.h>
#include <stdlib.h>

#include "zset_api.h"
/* tests the functionality of the zset api */

int main() {
    zset_t *test_zset = zset_new("fruits");
    zset_add(test_zset, "bananas", 15);
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
    zset_add(aa, "c", 3); 
    zset_card(aa);
    char** s = malloc(sizeof(char*)*10);
    s = zset_revrange(test_zset, -3,-1);
    printf("%s\n", s[0]);
    zset_remrangebyrank(test_zset,0,-1);
    zset_remrangebyrank(aa,0,-1);
    return 0;
}
