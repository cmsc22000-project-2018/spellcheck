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

	> ./spellcheck -d my_dict.txt -q misspelled.txt

*/


int main(int argc, char **argv) {

	// filenames up to 100 char
	char* dict_name = malloc(101*sizeof(char*));
	char* file_name = malloc(101*sizeof(char*));
	char* save_file = malloc(101*sizeof(char*));

	// default dict name
	dict_name = "sample_dict.txt";

	/*
		0: default?
		1: quiet batch
		2: verbose batch
		3: interactive
	*/
	int mode=0;

	/* Parse Command Line Args */
	// Consider using sscanf
	char c;
	while ((c=getopt(argc,argv,"d:i:v:q:s")) != -1) {
		switch(c) {
		case 'd':
			dict_name=optarg;
			greet();
			input(optarg,"dictionary");
			// if dict name doesn't point to valid file route, print error message and exit
			break;
		case 'i':
			mode=3;
			file_name=optarg;
			greet();
			input(optarg,"target file");
			// if file name is not valid, print error
			break;
		case 'v':
			mode=2;
			file_name=optarg;
			greet();
			input(optarg,"target file");
			break;
		case 'q':
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

	/* Open main page, if file path doesn't exist */
	int *quit=0;
	if (fileexists(file_name)) {
		*quit=1;

	}

	/* main page */
	main_page(quit,file_name,dict_name);
	if (!fileexists(file_name)) return 0; // user selected quit in main page

	// pass dictionary into
	

	// Execute either interactive or batch mode, and save file at end
	switch (mode) {
		case 1: *quit=1;	//quiet
			break;
		case 2: *quit=1;	//verbose
			break;
		case 3: interactive_mode(file_name, quit);
			break;
		default:
			break;
	}

	// free and exit
	free(save_file);
	free(dict_name);
	free(file_name);
	return 0;
}
