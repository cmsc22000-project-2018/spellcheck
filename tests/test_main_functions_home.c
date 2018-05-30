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

    int i = change_mode(mode);

    cr_assert_eq(i, QUIET_MODE, "return value wrong");
}

Test(main_functions_home, change_mode0)
{
    char* mode = "2";

    int i = change_mode(mode);

    cr_assert_eq(i, VERBOSE_MODE, "return value wrong");
}

Test(main_functions_home, change_mode1)
{
    char* mode = "-1";

    int i = change_mode(mode);

    cr_assert_eq(i, INTERACTIVE_MODE, "return value wrong");
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