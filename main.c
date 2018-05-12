#include <stdio.h>
#include <getopt.h>
#include "parser.h"
#include "shellstrings.h"
#include "scfunctions.h"
#include "dictionary.h"
#include "getopt.h"

/*
	Main function

	- parses through initial command line
	- in the absence of a file to parse, open main page, which can either do one of 4 things:
		- load a new dictionary (will replace the one that is parsed, if
		- quit
		- 

	- launch either interactive or batch mode
	- save file
 */

/*
Sample inputs:

One input
	> ./spellcheck: opens main page

Two inputs
	> Not possible to determine whether entered filename is for dict or editing
	> Print error messages and exit

Three inputs
	> ./spellcheck -d [dictname.txt]: stores 

	> ./spellcheck -i [filename.txt]: interactive mode

	> ./spellcheck -q [filename.txt]: quiet mode

	> ./spellcheck -v [filename.txt]: verbose mode

...
and so on, with different combinations.

Largest possible number of argc: 7
	> ./spellcheck -d my_dict.txt -q misspelled.txt -s savefilename.txt

*/

char* mode_name(int mode)
{
	switch (mode) {
		case 1: return "quiet batch mode"; 
		case 2: return "verbose batch mode";
		case 3: return "interactive mode";
		default: break;
	}
	return "quiet batch mode";
}


int main(int argc, char **argv) {

	// filenames up to 100 char
	char* dict_name = malloc(101*sizeof(char*));
	char* file_name = malloc(101*sizeof(char*));
	char* save_file = malloc(101*sizeof(char*));

	// default dict name
	dict_name = "sample_dict.txt";

	/*
		1: quiet batch
		2: verbose batch
		3: interactive
	*/
	int mode=3;

	/* Parse Command Line Args */
	// Consider using sscanf
	char c;

	while ((c=getopt(argc,argv,"d:i:v:q:s")) != -1) {
		switch(c) {
		case 'd':
			if (!fileexists(optarg)) {
				shell_error("Dictionary input file path invalid\n");
				return EXIT_FAILURE;
			}
			dict_name=optarg;
			greet();
			input(optarg,"dictionary");
			break;
		case 'i':
			if (!fileexists(optarg)) {
				shell_error("Input file path invalid\n");
				return EXIT_FAILURE;
			}
			mode=3;
			file_name=optarg;
			greet();
			input(optarg,"target file");
			// if file name is not valid, print error
			break;
		case 'v':
			if (!fileexists(optarg)) {
				shell_error("Input file path invalid\n");
				return EXIT_FAILURE;
			}
			mode=2;
			file_name=optarg;
			greet();
			input(optarg,"target file");
			break;
		case 'q':
			if (!fileexists(optarg)) {
				shell_error("Input file path invalid\n");
				return EXIT_FAILURE;
			}
			mode=1;
			file_name=optarg;
			greet();
			input(optarg,"target file");
			break;
		case 's':
			save_file=optarg;
			greet();
			printf("Your file will now be saved as %s\n",optarg);
			break;
		default:
			break;
		}
	}

	int *quit=0;

  while(!(*quit)) {
	if (fileexists(file_name)) {
		*quit=1;
	}

	/* main page: activated if there is no file to be parsed.
	   can open help page, quit, or load filename / dictname */
	main_page(quit,&mode,file_name,dict_name);
	if (!fileexists(file_name) && ((*quit)==2)) { // user selected "quit" in main_page
		bye();
		return 0;
	}


	/*
		Initialize dictionary, declare names of files to be used
	*/

	// ...

	/*
		Starting to Parse file!
	 */
	char* mode_name(mode);	
	printf("\n\n Editing Started With \n\n");
	printf("file: %s\n", file_name);
	printf("dictionary: %s\n\n", dict_name);
	printf("mode \n\n", mode_name);

	// Execute either interactive or batch mode, and save file at end
	switch (mode) {
		case 1: batch_mode(file_name, dict, quit, 0); // pass in dictionary
			break;
		case 2: batch_mode(file_name, dict, quit, 1); // pass in dictionary 
			break;
		case 3: interactive_mode(file_name, quit); // pass in dictionary - to implement
			break;
		default:
			break;
	}

  }

	// free and exit
	free(save_file);
	free(dict_name);
	free(file_name);
	return 0;
}
