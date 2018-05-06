#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Main function */
int main(int argc, char **argv)
{
	// initialization: dictionary?
	int *quit;
	*quit = 0;

	if (argc == 2 || argc > 4) {
		usage();
		return 0;
	}

	if (argc == 1) {
		while(!(*quit)) {
			greet();
			main_help_text();
			shell_prompt();
			main_page(quit);
		}
	}

	if (argc == 3 || argc ==4) { // batch mode
		batch_mode(argc,argv);
	}

	return 0;
}
