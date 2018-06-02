#include <stdio.h>
#include <stdbool.h>
#include <criterion/criterion.h>
#include <criterion/options.h>
#include <criterion/output.h>
#include "log.c/src/log.h"

int main(int argc, char *argv[]) {
	FILE *f = fopen("criterionoutput.txt", "w");
    assert(f != NULL);
	log_set_fp(f);

    struct criterion_test_set *tests = criterion_initialize();

    criterion_options.jobs = 1;

    int result = 0;
    if (criterion_handle_args(argc, argv, true))
        result = !criterion_run_all_tests(tests);

    criterion_finalize(tests);

    fclose(f);
    remove("criterionoutput.txt");
    return result;
}
