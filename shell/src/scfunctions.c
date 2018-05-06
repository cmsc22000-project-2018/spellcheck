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
}

void save_page(char* filename, char** lines,int* quit)
{
	int i=1;

	while (i) {
		save_page_text();
		i=0;
		char* line;
		char** args;

		line=read_line();
		args=split_line(line);

		assert(args!=NULL);

		if (!strcmp(args[0],"w")) {
			save_corrections(filename,lines);
			*quit=1;
		} else if (!strcmp(args[0],"s")) {
			save_corrections(args[1],lines);
			*quit=1;
		} else if (!strcmp(args[0],"r")) {
			*quit=0;
		} else if (!strcmp(args[0],"q")) {
			*quit=1;
		} else {
			error_shell("please type in one of the indicated commands!\n");
			*quit=0;
			i=1;
		}
	}
}


/* Functions needed for batch mode */
//void batch_mode(int argc, char **argv)
//{
//	// implmenent after having interactive success
//}


/* Functions needed for interactive mode */
char* edit_interactive(char* line)
{
	return line;
	// need a way for string to (a) preserve punctuations and (b) 
	// @Sarika this would be where the program needs replace_word, ignore_word, alternate_spelling

}

void interactive_mode(char** filename, int* quit)
{
	char** lines;

	lines = lineparse_file(filename[1]);

	// step through phases
	int i=0;
	while (lines[i] != NULL) {	// potential error - one empty line in the middle of two full?	
		lines[i] = edit_interactive(lines[i]);
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
	getchar();
}

void main_page(int* quit)
{
	char* line;
	char** args;

	line = read_line();
	args = split_line(line);

	if (!strcmp(args[0],"h")) {
		help_page();
		*quit=0;
	} else if (!strcmp(args[0],"r")) {
		interactive_mode(args,quit);
		*quit=0;
	} else if (!strcmp(args[0],"d")) {
		// read_to_dict;
		*quit=0;
	} else if (!strcmp(args[0],"q")) {
		*quit=1;
	} else {
		error_shell("Please type in one of the indicated commands!\n");
		*quit=0;
	}

	free(line);
	free(args);
}
