#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parser.h"
#include "scfunctions.h"
#include "shellstrings.h"

/* Main function */
int main(int argc, char **argv)
{
	// initialization: dictionary?
	int i = 0;
	int *quit = &i;

	if (argc == 2 || argc > 4) {
		usage();
		return 0;
	}

	if (argc == 1) {
		greet();
		while(!(*quit)) {
			main_page(quit);
		}
	}

	if (argc == 3 || argc ==4) { // batch mode
//		batch_mode(argc,argv);
	}

	return 0;
}
