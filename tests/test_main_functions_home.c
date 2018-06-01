#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main_functions_home.h"

/*
 ***** change_mode tests *****
 */ 
Test(main_functions_home, change_mode)
{
    char* mode = "1";
    bool* b = false;

    int i = change_mode(mode, b);

    cr_assert_eq(i, QUIET_MODE, "return value wrong");
}

Test(main_functions_home, change_mode0)
{
    char* mode = "2";
    bool* b = false;

    int i = change_mode(mode, b);

    cr_assert_eq(i, VERBOSE_MODE, "return value wrong");
}


/*
 ***** fileexists tests *****
 */
Test(main_functions_home, fileexists)
{
    int i = fileexists("test_short.txt");

    cr_assert_eq(i, 0, "file should exist");
}

Test(main_functions_home, fileexists1)
{
    int i = fileexists("test_sh.txt");

    cr_assert_eq(i, 0, "file should not exist");
}