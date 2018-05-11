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
	dic_name = "default_dict.txt";


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

	// Main Page load
	int *quit=0;
	while (!quit) {
		main_page(quit);
	}

	// Execute either interactive or batch mode, and save file at end
	switch (mode) {
		1: // batch
		2: // verbose
		3: // interactive
	}

	return 0;
}
