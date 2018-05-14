#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include "parser.h"
#include "shellstrings.h"
#include "scfunctions.h"
#include "dictionary.h"

/*
 *	Main function
 *
 *	- parses through initial command line
 *	- in the absence of a file to parse, open main page, which can either do one of 4 things:
 *		- load a new dictionary (will replace the one that is parsed, if
 *		- quit
 *		- 
 *
 *	- launch either interactive or batch mode
 *	- save file
 *
 *  Sample inputs:
 *
 *  One input
 *	> ./spellcheck: opens main page
 *
 *  Two inputs
 *	> Not possible to determine whether entered filename is for dict or editing
 *	> Print error messages and exit

 *  Three inputs
 *	> ./spellcheck -d [dictname.txt]: stores 
 *
 *	> ./spellcheck -i [filename.txt]: interactive mode
 *
 *	> ./spellcheck -q [filename.txt]: quiet mode
 *
 *	> ./spellcheck -v [filename.txt]: verbose mode
 *
 *  ...
 *  and so on, with different combinations.
 *
 *  Largest possible number of argc: 7
 *	> ./spellcheck -d my_dict.txt -q misspelled.txt -s savefilename.txt
 *
 */

char* modename(int mode)
{
	switch (mode) {
		case 1: return "quiet batch mode"; 
		case 2: return "verbose batch mode";
		case 3: return "interactive mode";
		default: break;
	}
	return "quiet batch mode";
}

int main(int argc, char **argv)
{
	// filenames up to 100 char
	char* dict_name = malloc(101 * sizeof(char*));
	char* file_name = malloc(101 * sizeof(char*));
	char* save_file = malloc(101 * sizeof(char*));

	// default dict name
	strcpy(dict_name,"tests/sample_dict.txt");

	/*
		1: quiet batch
		2: verbose batch
		3: interactive
	*/
	int mode = 3;

	/* Parse Command Line Args */
	// Consider using sscanf
	char c;

	/* If command line contains just the file at argv[1], write it into file_name */
	if (fileexists(argv[1])) strcpy(file_name,argv[1]);


    // Parse the initial command line and 
	while ((c = getopt(argc,argv,"d:i:v:s:q:")) != -1) {
		switch (c) {
		case 'd':
			if (!fileexists(optarg)) {  // this checks if the file actuall exists
				shell_error("Dictionary input file path invalid");
				return EXIT_FAILURE;
			}
			strcpy(dict_name,optarg);
			shell_input(optarg, "dictionary");
			break;
		case 'i':
			if (!fileexists(optarg)) {
				shell_error("Input file path invalid");
				return EXIT_FAILURE;
			}
			mode = 3;
			shell_input(optarg, "target file");
            strcpy(file_name,optarg);
			// if file name is not valid, print error
			break;
		case 'v':
			if (!fileexists(optarg)) {
				shell_error("Input file path invalid");
				return EXIT_FAILURE;
			}
			mode = 2;
            strcpy(file_name,optarg);
			shell_input(optarg, "target file");
			break;
		case 'q':
			if (!fileexists(optarg)) {
				shell_error("Input file path invalid");
				return EXIT_FAILURE;
			}
			mode = 1;
			strcpy(file_name,optarg);
			shell_input(optarg, "target file");
			break;
		case 's':
            if (strstr(optarg,".txt\0") == NULL) {    // does not save to a *.txt file
                  shell_error("Input save file path invalid");
                  return EXIT_FAILURE;
            }
			strcpy(save_file,optarg);
            shell_input(optarg,"file save destination");
			break;
		default: /* If command line contains just the file at argv[1], write it into file_name */
			shell_usage();
			break;
		}
	}

	int *quit = malloc(sizeof(int*)); // this enables return to main page, should user choose it at save_page
	*quit = 0;

  while (!(*quit)) {
	if (fileexists(file_name)) {	// if file exists, then bypass main page
		*quit = 1;
	}

	/* main page: activated if there is no file to be parsed.
	   can open help page, quit, or load filename / dictname */
	main_page(quit, &mode, file_name, dict_name);
	if ((*quit) == 2) { // user selected "quit" in main_page
		shell_outro();
		return 0;
	}

	/*
		Initialize dictionary, declare names of files to be used
	*/
	dict_t* dict = dict_new();
	if (read_to_dict(dict_name, dict) == 1) {
		printf("Dictionary Successfully Parsed!\n");
	} else {
		printf("Trouble reading dictionary, exiting program\n");
	}

	/*
		Starting to Parse file!
	 */
	char* md = modename(mode);

    if (mode != 1) {

	    printf("\n\n========================================\n"
                   "==========Editing Started With==========\n\n");
	    printf("file: %s\n", file_name);
	    printf("dictionary: %s\n", dict_name);
	    printf("mode: %s \n\n", md);
    }

	/* Pause, to confirm start */
    if (mode == 3) {
        printf("Enter any command to start %s\n\n", md);
	    parse_read_line();
    }

	char** result=NULL;
	// Execute either interactive or batch mode, and save file at end
	switch (mode) {
		case 1: result = batch_mode(file_name, dict, quit, 0); // pass in dictionary
			break;
		case 2: result = batch_mode(file_name, dict, quit, 1); // pass in dictionary 
			break;
		case 3: result = interactive_mode(file_name, dict, quit); // pass in dictionary - to implement
			break;
		default:
			break;
	}

	// Save file
    md = strstr(save_file,".txt");
	if (md != NULL) {
		save_corrections(save_file, result);
		*quit=1;
	} else {
		save_page(file_name, result, quit);
	}

	// free text array
	int k=0;
	if (result[k] != NULL) {
		free(result[k]);
		k++;
	}
	free(result);


	// free(file_name);
  }

	// free and exit
    shell_outro();
	free(quit);
	free(save_file);
	free(dict_name);
//	free(file_name);
	return 0;
}
