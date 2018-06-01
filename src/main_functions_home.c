#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "main_functions_home.h"

/* See main_functions_home.h */
void help_page(bool *color) {
    shell_help(color);
	shell_prompt(color);

	// Accept any input in the command line
	parse_read_line();
}

/* See main_functions_home.h */
bool fileexists(const char *filename) {
	struct stat buffer;

	return (bool) (stat(filename, &buffer) == 0);
}

/* See main_functions_home.h */
int change_mode(char *arg) {
	int a = atoi(arg);

    if ((a == 1) || (a == 2) || (a == 3)) {
        return a;
	}

	else {
        shell_error("Input invalid: Returning to interactive mode", false);

        /*
         * The default is 3, given this function is only called in main_page(),
         * at which point interactive mode is what user probably intended
         */
	    return 3;
    }

    return 3;
}

/* See main_functions_home.h */
void main_page(bool *quit, int *mode, char *filename, char *dict, bool *color) {
	char *line;
	char **args;

	while ((*quit) == true) {
		shell_main_menu(false);
		shell_prompt(false);

		line = parse_read_line();
		args = parse_split_line(line);	// line is now split into tokens

		if ((args == NULL) || (args[2] != NULL)) { // 3 inputs, or no input: error message
			shell_error("Please type in one of the indicated commands!", false);
			
			*quit = true;
		}

		else if (!strcmp(args[0], "h")) { // Print help page, then wait for user input
			help_page(color);
			
			*quit = true;
		}

		else if (!strcmp(args[0], "f")) { // Check valid file path, then exit. If not, redo loop
			if (!fileexists(args[1])) {	//file path checking
				shell_error("Please enter a valid file path for a new edit target!", false);
				
				*quit = true;
			}

			else {
			strcpy(filename,args[1]);
			printf("\n\nInput file is now %s\n\n\n",filename);

			*quit = false;
			}
		}

		else if (!strcmp(args[0],"d")) {	// dictionary name change 
			if (!fileexists(args[1])) {	// Check file path validity for dicitonary
				shell_error("Please enter a valid file path for a new dictionary!", false);
				
				*quit = true;
			}

			else {
			dict = args[1];
			printf("\n\nDictionary file is now %s\n\n\n",dict);
			
			*quit = true;
			}
		} 

		else if (!strcmp(args[0],"q")) { // quit
			*quit = false;
			*mode = QUIT;
			
			return;
		}

		else if (!strcmp(args[0], "m")) { // change mode
			printf("Mode number accepted: %d\n",atoi(args[1]));
            *mode = change_mode(args[1]);

			if (!fileexists(filename)) {
				*quit = true;
			}

			else {
				*quit = false;
			}
		}

		else { // input bad
			shell_error("Please type in one of the indicated commands!", false);
			*quit = true;
		}

		free(line);
		free(args);
	}
}