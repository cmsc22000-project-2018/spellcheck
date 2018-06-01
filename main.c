#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>
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
 *		- launch either interactive or batch mode
 *		- save file
 *
 *  Sample inputs:
 *
 *  One input
 *	> ./spellcheck: opens main page
 *
 *  Two inputs
 *	> ./spellcheck [filename.txt]
 *
 *	Other flags:
 *	> -d [dictname.txt]: changes dictionary
 *
 *	> -i/-q/-v : interactive, quiet, verbose mode
 *
 *	> -s [filename.txt]: file saving destination 
 *
 *	> -c : colored strings
 *
 *  ...
 *  and so on, with different combinations.
 *
 *  Largest possible number of argc: 9
 *	> ./spellcheck file.txt -d my_dict.txt -q misspelled.txt -s savefilename.txt -c
 */

char *modename(int* mode) {
	switch (*mode) {
		case QUIET_MODE:
            return "Quiet Batch Mode"; 
		case VERBOSE_MODE:
            return "Verbose Batch Mode";
		case INTERACTIVE_MODE:
            return "Interactive Mode";
		default:
            break;
	}
	return "Interactive Mode";
}

int main(int argc, char *argv[]) {

	if (argc > 9) {
		shell_usage();
		exit(1);
	}

	// filenames up to 400 char
	char *dict = malloc(401 * sizeof(char *));
	char *filename = malloc(401 * sizeof(char *));
	char *save_file = malloc(401 * sizeof(char *));
    bool *color = malloc(sizeof(bool));


	// Default dict name
	strcpy(dict, "tests/sample_dict.txt");

	/*
	 * 1: Quiet Batch Mode
	 * 2: Verbose Batch Mode
	 * 3: Interactive Mode
	 */
	int *mode = malloc(sizeof(int));
    *mode = INTERACTIVE_MODE;

    // By default, the color functionality is off
    *color = false;

	// Parse Command Line Arguments
	char c;

    if (fileexists(argv[optind])) {
        strcpy(filename, argv[optind]);
        optind++;
    }

    // Parse the initial command line and 
	while ((c = getopt(argc, argv, "ivcqs:d:")) != -1) {
		switch (c) {
            case 'd':
                if (!fileexists(optarg)) {  // this checks if the file actually exists
				    shell_error("Invalid dictionary file input.", color);
				    return EXIT_FAILURE;
                }

                strcpy(dict, optarg);

                if (*mode == INTERACTIVE_MODE) {
                    shell_input(optarg, "dictionary", color);
                }

                break;

            case 'i':
                *mode = INTERACTIVE_MODE;
                break;

            case 'v':
                *mode = VERBOSE_MODE;
                break;

            case 'q':
                *mode = QUIET_MODE;
                break;
		
            case 's':
                if (strstr(optarg,".txt\0") == NULL) {    // does not save to a *.txt file
                    shell_error("Invalid file path.", color);
                    return EXIT_FAILURE;
                }

                strcpy(save_file,optarg);
            
                if (*mode == INTERACTIVE_MODE) {
                    shell_input(optarg, "file save destination", color);
                }

                break;

            case 'c':
                *color = !(*color);
                printf("color is %d\n", *color);
                break;

            case '?':
                shell_usage();
                exit(0);

            default:
                shell_error("Invalid format.", color);
                exit(0);
        }

	}

	bool *quit = malloc(sizeof(bool));
	*quit = true;

    while ((*quit) == true) {
        if (fileexists(filename)) {	// if file exists, then bypass main page
            *quit = false;
        }

	   /*
        * Main page: Activated if there is no file to be parsed.
        * can open help page, quit, or load filename / dictname
        */
        main_page(quit, mode, filename, dict, color);

        if (*mode == QUIT) { // user selected "quit" in main_page
            return 0;
        }

		 // Initialize dictionary, declare names of files to be used
        dict_t *new_dict = dict_new();
        int msg = dict_read(new_dict, dict);
        if (msg == EXIT_FAILURE) {
            shell_error("Invalid dictionary file input.", color);
            exit(0);
        }

		// Starting to Parse file! Printing messages accordingly
        char *md = shell_modename(*mode);

        if (*mode == INTERACTIVE_MODE) {
            shell_start_interactive(filename, dict, md, color);
        }

        char **result = NULL;

        // Execute either interactive or batch mode, and save file at end
        switch (*mode) {
            case QUIET_MODE:
                result = batch_mode(filename, new_dict, quit, QUIET_MODE); // pass in dictionary
                break;
            case VERBOSE_MODE:
                result = batch_mode(filename, new_dict, quit, VERBOSE_MODE); // pass in dictionary 
                break;
            case INTERACTIVE_MODE:
                result = interactive_mode(filename, new_dict, quit, color); // pass in dictionary
                break;
            default:
                break;
        }

        if (*mode != VERBOSE_MODE && result != NULL) {	// Save file, a functionality unnecessary for verbose batch mode
            if (*mode == INTERACTIVE_MODE) {
                shell_edit_success(color);
            }

            md = strstr(save_file, ".txt\0");
            if (md == NULL && *mode == QUIET_MODE) {
                shell_print(result);
                *quit = false;
            }

            else if (md != NULL) {
                save_corrections(save_file, result);
                *quit = false;
            }

            else {
                save_page(filename, result, quit, color);
            }
        }
    }

    return 0;
}