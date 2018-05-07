#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "scfunctions.h"

void save_corrections(char* filename, char** lines)
{
	FILE* f=fopen(filename,"w");
	int i=0;
	while (lines[i] != NULL) {
		fprintf(f,"%s",lines[i]);
		i++;
	}
	fclose(f);
}

void save_page(char* filename, char** lines,int* quit)
{
	int i=1;

	while (i) {
		save_page_text();
		shell_prompt();
		i=0;
		char* line;
		char** args;

		line=read_line();
		args=split_line(line);

		assert(args!=NULL);

		if (!strcmp(args[0],"w")) {
			save_corrections(filename,lines);
			*quit=0;
		} else if (!strcmp(args[0],"s")) {
			save_corrections(args[1],lines);
			*quit=0;
		} else if (!strcmp(args[0],"r")) {
			*quit=1;
		} else if (!strcmp(args[0],"q")) {
			*quit=0;
		} else {
			error_shell("please type in one of the indicated commands!");
			i=1;
		}
	}
}



/* Functions needed for interactive mode */
char* edit_interactive(char* line, int linenum)
{
	// generate_suggestions
	// select replacement
	// replace word

	// HARD-CODED VERSION
	interactive_1();
	read_line();
	interactive_2();
	read_line();

	line[18]='u';

	return line;
	// later, need a way for string to (a) preserve punctuations and (b) spaces 
}

void interactive_mode(char** filename, int* quit)
{
	char** lines;

	lines = lineparse_file(filename[1]);

	printf("%s", lines[0]);	// testing purposes

	// step through phases
	int i=0;
	while (lines[i] != NULL) {	// potential error - one empty line in the middle of two full?	
		lines[i] = edit_interactive(lines[i],i+1);
		i++;
	}

	// call save
	save_page(filename[1], lines, quit);

	// free lines
	i=0;
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
	shell_prompt();

	char* l=read_line();
	free(l);
}



void batch_mode(int argc, char** argv)
{
	if (argc == 3) {
		if (!strcmp(argv[1],"-q")) {
			// quiet
		} else if (!strcmp(argv[1],"-v")) {
			// verbose
		} else {
			usage();
			exit(0);
		}
		// move to save page
	}

	if (argc == 4) {
		if (strcmp(argv[1],"-s")) {
			usage();
			exit(0);
		}
		// save mode		
	}
}


/* main page */
int main_page(int* quit)
{
	main_help_text();
	shell_prompt();

	char* line;
	char** args;

	line = read_line();
	args = split_line(line);

	if (!strcmp(args[0],"h")) {
		help_page();
		*quit=0;
	} else if (!strcmp(args[0],"r")) {
		if(args[1] == NULL) {
			error_shell("Please indicate a file!");
			*quit=0;
			return 0;
		}
		interactive_mode(args,quit);
		*quit=0;
	} else if (!strcmp(args[0],"d")) {
		// read_to_dict;
		*quit=0;
	} else if (!strcmp(args[0],"q")) {
		*quit=1;
	} else {
		error_shell("Please type in one of the indicated commands!");
		*quit=0;
	}

	free(line);
	free(args);

	return 1;
}
