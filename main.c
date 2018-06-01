#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "parser.h"
#include "shellstrings.h"
#include "dictionary.h"
#include "main_functions_batch.h"
#include "main_functions_interactive.h"
#include "main_functions_save.h"
#include "main_functions_edit.h"
#include "main_functions_home.h"

/*
 *	Main function
 *
 *	- parses through initial command line
 *	- in the absence of a file to parse, open main page, which can either do one of 4 things:
 *		- load a new dictionary (will replace the one that is parsed)
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
 *
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
 */

char *modename(int mode) {
	switch (mode) {
		case QUIET_MODE: return "Quiet Batch Mode"; 
		case VERBOSE_MODE: return "Verbose Batch Mode";
		case INTERACTIVE_MODE: return "Interactive Mode";
		default: break;
	}

	return "Quiet Batch Mode";
}

int main(int argc, char *argv[]) {
	// filenames up to 400 char
	char *dict = malloc(401 * sizeof(char *));
	char *filename = malloc(401 * sizeof(char *));
	char *save_file = malloc(401 * sizeof(char *));
    bool *color = malloc(sizeof(bool *));

    // By default, the color functionality is off
    *color = false;

	// Default dict name
	strcpy(dict, "tests/sample_dict.txt");

	/*
	 * 1: Quiet Batch Mode
	 * 2: Verbose Batch Mode
	 * 3: Interactive Mode
	 */
	int mode = INTERACTIVE_MODE;

	// Parse Command Line Arguments
	char c;

	// If command line contains just the file at argv[1], write it into filename
	if (fileexists(argv[1]) || fileexists(argv[3])) {
        shell_error(shell_error_format(), color);
        exit(0);
    }

    // Parse the initial command line and 
	while ((c = getopt(argc, argv, "d:i:v:s:q:c:")) != -1) {
		switch (c) {
            case 'd':
                if (!fileexists(optarg)) {  // this checks if the file actually exists
				    shell_error(shell_error_dict(""), color);
				    return EXIT_FAILURE;
                }

                strcpy(dict,optarg);

                if (mode == 3) {
                    shell_input(optarg, "dictionary", color);
                }

                break;

            case 'i':
                if (!fileexists(optarg)) {
				    shell_error(shell_error_file(""), color);
				    return EXIT_FAILURE;
                }

                mode = 3;

                strcpy(filename, optarg);

                // if file name is not valid, print error
                break;

            case 'v':
                if (!fileexists(optarg)) {
				    shell_error("Input file path invalid", color);
				    return EXIT_FAILURE;
                }

                mode = 2;

                strcpy(filename, optarg);

                break;

            case 'q':
                if (!fileexists(optarg)) {
				    shell_error("Input file path invalid", color);
				    return EXIT_FAILURE;
                }
			
                mode = 1;
			
                strcpy(filename, optarg);
			
                break;
		
            case 's':
                if (strstr(optarg,".txt\0") == NULL) {    // does not save to a *.txt file
                    shell_error("Input save file path invalid", color);
                    return EXIT_FAILURE;
                }

                strcpy(save_file,optarg);
            
                if (mode == 3) {
                    shell_input(optarg, "file save destination", color);
                }

                break;

            case 'c':
                *color = true;

                break;

            default:
                shell_error(shell_error_format(), color);
                exit(0);
        }
	}

	bool *quit = malloc(sizeof(bool *));
	*quit = true;

    while ((*quit) == true) {
        if (fileexists(filename)) {	// if file exists, then bypass main page
            *quit = false;
        }

	   /*
        * Main page: Activated if there is no file to be parsed.
        * can open help page, quit, or load filename / dictname
        */
        main_page(quit, &mode, filename, dict, color);

        if (mode == QUIT) { // user selected "quit" in main_page
            return 0;
        }

		 // Initialize dictionary, declare names of files to be used
        dict_t *new_dict = dict_new();
        int msg = dict_read(new_dict, dict);

        if (msg == EXIT_FAILURE) {
            shell_error(shell_error_dict(dict), color);
            exit(0);
        }

		// Starting to Parse file! Printing messages accordingly
        char *md = shell_modename(mode);

        if (mode == INTERACTIVE_MODE) {
            shell_start_interactive(filename, dict, md, color);
        }

        char **result = NULL;

        // Execute either interactive or batch mode, and save file at end
        switch (mode) {
            case QUIET_MODE:
                result = batch_mode(filename, new_dict, quit, QUIET_MODE); // pass in dictionary
                break;
            case VERBOSE_MODE:
                result = batch_mode(filename, new_dict, quit, VERBOSE_MODE); // pass in dictionary 
                break;
            case INTERACTIVE_MODE:
                result = interactive_mode(filename, new_dict, quit); // pass in dictionary
                break;
            default:
                break;
        }

        if (mode != VERBOSE_MODE && result != NULL) {	// Save file, a functionality unnecessary for verbose batch mode
            if (mode == INTERACTIVE_MODE) {
                shell_edit_success(color);
            }

            md = strstr(save_file, ".txt");

            if (md == NULL && mode == 1) {
                shell_print(result);
                *quit = false;
            }

            else if (md != NULL) {
                save_corrections(save_file, result);
                *quit = false;
            }

            else {
                save_page(filename, result, quit);
            }
        }
    }

    return 0;
}