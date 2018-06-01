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
int change_mode(char *arg, bool* color) {
	int a = atoi(arg);

    if ((a == QUIET_MODE) || (a == VERBOSE_MODE) || (a == INTERACTIVE_MODE)) {
        return a;
	}

    shell_error("Invalid mode; reverting to interactive.", color);
    /*
     * The default is 3, given this function is only called in main_page(),
     * at which point interactive mode is what user probably intended
     */
	return INTERACTIVE_MODE;
}

/* See main_functions_home.h */
void main_page(bool *quit, int *mode, char *filename, char *dict, bool *color) {
	char *line;
	char **args;
	bool print = true;

	while ((*quit) == true) {
		if (print == true) {
			shell_main_menu(color);
		}

		shell_prompt(color);

		line = parse_read_line();
		args = parse_split_line(line);	// line is now split into tokens

		if ((args == NULL) || (args[2] != NULL)) { // 3 inputs, or no input: error message
			shell_error("Please type in one of the indicated commands.", color);
			
			print = false;
			*quit = true;
		}

		else if (!strcmp(args[0], "h")) { // Print help page, then wait for user input
			help_page(color);
			
			print = true;
			*quit = true;
		}

		else if (!strcmp(args[0], "f")) { // Check valid file path, then exit. If not, redo loop
			if (!fileexists(args[1])) {	//file path checking
				shell_error("Please enter a valid file path for a new edit target.", color);
				
				print = false;
				*quit = true;
			}

			else {
				strcpy(filename,args[1]);
				printf("\n\nInput file is now %s\n",filename);

				print = false;
				*quit = false;
			}
		}

		else if (!strcmp(args[0],"d")) {	// dictionary name change 
			if (!fileexists(args[1])) {	// Check file path validity for dicitonary
				shell_error("Please enter a valid file path for a new dictionary.", color);
				
				print = false;
				*quit = true;
			}

			else {
				dict = args[1];
				printf("\n\nDictionary file is now %s\n",dict);
			
				print = false;
				*quit = true;
			}
		} 

		else if (!strcmp(args[0], "m")) { // change mode
			printf("Mode number accepted: %d\n", atoi(args[1]));
            *mode = change_mode(args[1], color);

            print = true;
            *quit = true;
		}

		else if (!strcmp(args[0], "c")) { // color
			*color = !(*color);
		}

		else if (!strcmp(args[0],"q")) { // quit
			print = false;
			*quit = false;
			*mode = QUIT;
			
			return;
		}

		else { // input bad
			shell_error("Invalid file input.", color);
			*quit = true;
		}

		free(line);
		free(args);
	}
}