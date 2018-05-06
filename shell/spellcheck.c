#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "scfunctions.h"


/* Main function */
int main(int argc, char **argv)
{
	// initialization: dictionary?
	int *quit;
	*quit = 0;

	if (argc == 2 || argc > 4) {
		usage();
		return 1;
	}

	if (argc == 1) {
		greet();
		main_help_text();
		shell_prompt();
		while (!(*quit))	{
			main_page(quit);
		}
	}

	if (argc == 3 || argc ==4) { // batch mode
		batch_mode(argc,argv);
	}

	return 0;
}
