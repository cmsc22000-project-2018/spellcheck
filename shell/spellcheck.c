#ifndef _SPELLCHECK_H
#define _SPELLCHECK_H

#include <stdio.h>
#include <stdlib.h>
#include "shellstrings.h"

/* This file will run the shell "spellcheck" for interacting with the dictionary and the file */












/* Administer Shell */

int main(int argc, char **argv)
{
	int quit=0;

	/* Case in which arg entered is only "spellcheck", in which case main page is loaded */
	if (argc=1) {
		printf("%s%s%s",greet(),main_help_text(),shell_prompt());

	}

	/* Case in which arg entered is 1 => If this is a file, enter interactive mode immediately */ 
	if (argc=2) {
	}

	/* File and mode must be entered, in order (brittle at the moment, change later) */
	if (argc=3 || 5) {
	
	}

	/* clean up - should later contain freeing functions */
	printf("Thank you for using spellcheck!\n");
	return 0;
}

#endif
