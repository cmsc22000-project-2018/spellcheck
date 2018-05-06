#ifndef _SPELLCHECK_H
#define _SPELLCHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"

#define BUFFER_SIZE 256

/* Functions needed for saving */
save_page()
{
	save_page_text();

	char* line;
	char** args;

	line=lsh_read_line();
	args=lsh_split_line();

	assert(args!=NULL);

	switch(args[0]) {

	}
}


/* Functions needed for batch mode */
batch_mode(int argc, char **argv)
{
	// implmenent after having null
}


/* Functions needed for interactive mode */

void interactive(char** filename, int* quit)
{
	// load file
	int *n, *s;
	char** lines;

	lines = lineparse_file(filename[1], *n, *s);	// discovered not necessary~

	// step through phases
	lines = edit_interactive();

	// call save
	save_page(lines);

	// free lines
	int i=0;
	while(lines[i]!=NULL) {
		free(lines[i]);
		i++;
	}
	free(lines);
}

/* Prints help page. Returns to main page via loop in main function */
void help_page()
{
	help_page_text();
	getchar();
}

void main_page(int* quit)
{
	char* line;
	char** args;

	line = lsh_read_line();
	args = lsh_split_line(line);

	switch (args[0])
	{
		case "h": help_page();
			*quit=0;
			break;
		case "r": // check num of args
			 interactive_mode(args[1],quit);	// quitting determined on case-by-case
			break;
		case "d": // read_to_dict(args[1],
			*quit=0;
			break;
		case "q": *quit=1;
			break;
		default: error_shell("Please type in one of the indicated commands!\n");
			*quit=0;
	}

	free(line);
	free(args);
}

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


#endif
