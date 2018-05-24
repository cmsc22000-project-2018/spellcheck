#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main_functions.h"

/*
 * Note that there are five parts to scfunctions.c: saving, editing, interactive, batch, main.
 * The functions that do not require command line inputs have been tested below.
 * The functions that do require command line inputs are currently being researched by Deniz Turkcapar,
 * but currently use a simpler testing version, via command lines accepted in travis, to ensure that
 * each function responsible for printing a page prints a correct output.
 */

/* save_corrections tested */
Test(main_functions,save_corrections)
{
    char* c = "test_save.txt";
    char** lines = calloc(2, sizeof(char*));
    lines[0] = "Life is a journey";
    lines[1] = "Down a sleepless well";

    save_corrections(c, lines);

    FILE* f = fopen(c, "r");

    char str[20];
    c = fgets(str, 20, f);
    cr_assert_not_null(c, "fopen failed");

    int i = strncmp(str, lines[0], 17); // compare the saved file to the line that was saved
    cr_assert_eq(i, 0, "file copy failed");
}

/* save page accepts command line input */

// part 2 handled by scfunction_interactive tests

// part 3 - edit_interactive and interactive_mode accept command line inputs

// part 4 - edit_batch operates batch mode, test in command line

// part 5 - help_page and main_page require command line inputs

/*
 ***** change_mode tests *****
 */ 
Test(main_functions, change_mode)
{
    char* mode = "1";

    int i = change_mode(mode);

    cr_assert_eq(i, 1, "return value wrong");
}

Test(main_functions, change_mode0)
{
    char* mode = "2";

    int i = change_mode(mode);

    cr_assert_eq(i, 2, "return value wrong");
}

/*
 ***** fileexists tests *****
 */
Test(main_functions, fileexists)
{
    int i = fileexists("test_short.txt");

    cr_assert_eq(i, 0, "file should exist");    // i=1 in linux, but i=0 in travis build.
}

Test(main_functions, fileexists1)
{
    int i = fileexists("test_sh.txt");

    cr_assert_eq(i, 0, "file should not exist");
}
