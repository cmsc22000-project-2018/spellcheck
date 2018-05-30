#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "main_functions_batch.h"
#include "main_functions_home.h"
#include "dictionary.h"

/* Note on testing for main_functions_*.c files:
 * Note that there are five parts to main_functions.c: saving, editing, interactive, batch, main.
 * The functions that do not require command line inputs have been tested in the test_main_functions files.
 * The functions that do require command line inputs are currently being researched by Deniz Turkcapar,
 * but currently use a simpler testing version, via command lines accepted in travis, to ensure that
 * each function responsible for printing a page prints a correct output.
 * For this reason, test_main_functions_interactive.c does not exist, given that the edit_interactive function, and
 * the wrapper interactive_mode function, cannot operate without command line inputs.
 *
 * Another note is that edit_batch oprates both quiet and verbose modes, but testing for verbose_mode was avoided given that
 * printing in criterion testing was discouraged.
 */


/* Test edit_batch */
Test(main_functions_batch, edit_batch)
{
	char* line = strdup("Eye have, a splling chequer");
	dict_t* dict = dict_new();
	dict = dict_read(dict, "tests/sample_dict.txt");
	if (dict == NULL) {
		fprintf(stderr, "dict_read failed\n");
		exit(0);
	}

	char* newline = edit_batch(line, dict, QUIET_MODE, 1);

	printf("%s\n", newline);
}

/* Test edit_batch */
Test(main_functions_batch, edit_batch2)
{
	char* line = strdup("It cme with thy m'y PC.");
	dict_t* dict = dict_new();
	dict = dict_read(dict, "tests/sample_dict.txt");
	if (dict == NULL) {
		fprintf(stderr, "dict_read failed\n");
		exit(0);
	}

	char* newline = edit_batch(line, dict, QUIET_MODE, 1);

	printf("%s\n", newline);
}