#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main_functions_save.h"

/* Note on testing for main_functions_*.c files:
 * Note that there are five parts to main_functions.c: saving, editing, interactive, batch, main.
 * The functions that do not require command line inputs have been tested in the test_main_functions files.
 * The functions that do require command line inputs are currently being researched by Deniz Turkcapar,
 * but currently use a simpler testing version, via command lines accepted in travis, to ensure that
 * each function responsible for printing a page prints a correct output.
 * For this reason, test_main_functions_interactive.c does not exist, given that the edit_interactive function, and
 * the wrapper interactive_mode function, cannot operate without command line inputs.
 */

/* save_corrections tested */
Test(main_functions_save, save_corrections)
{
    char* c = "test_save.txt";
    char** lines = calloc(3, sizeof(char*));
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

/* save_page accepts command line input */