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
#include "log.c/src/log.h"

/* See main_functions_home.h */
void help_page(bool *color) {
    shell_help(color);
	shell_prompt(color);

	// Accept any input in the command line
	parse_read_line();
	log_trace("xiting the help page.");
}

/* See main_functions_home.h */
bool fileexists(const char *filename) {
	struct stat buffer;

	log_trace("Fileexists: filename %s", filename);

	if (stat(filename, &buffer) == 0) {
		return true;
	}
	return false;
}

/* See main_functions_home.h */
int change_mode(char *arg, bool* color) {
	log_trace("change_mode mode type: %s", arg);
	int a = atoi(arg);

    if ((a == QUIET_MODE) || (a == VERBOSE_MODE) || (a == INTERACTIVE_MODE)) {
        return a;
	}

    shell_error("change_mode mode type invalid; reverting to interactive mode.", color);
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
			log_trace("main_page printing main menu.");
			shell_main_menu(color);
		}

		shell_prompt(color);

		line = parse_read_line();
		args = parse_split_line(line);	// line is now split into tokens

		if ((args == NULL) || (args[2] != NULL)) { // 3 inputs, or no input: error message
			log_error("main_page rguments non-existent or too many argument input.");
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
				log_error("main_page invalid file input: file given does not exist.");
				shell_error("Please enter a valid file path for a new edit target.", color);
				
				print = false;
				*quit = true;
			}

			else {
				log_debug("main_page file input: %s", args[1]);
				strcpy(filename, args[1]);
				printf("\nFile input is now %s\n", filename);

				print = false;
				*quit = false;
			}
		}

		else if (!strcmp(args[0],"d")) {	// dictionary name change 
			if (!fileexists(args[1])) {	// Check file path validity for dicitonary
				log_error("main_page dictionary does not exist.");
				shell_error("Please enter a valid file path for a new dictionary.", color);
				
				print = false;
				*quit = true;
			}

			else {
				dict = args[1];
				log_info("main_page dictionary file is now %s.",dict);
			
				print = false;
				*quit = true;
			}
		} 

		else if (!strcmp(args[0], "m")) { // change mode
			log_info("main_page mode number accepted: %d.\n", atoi(args[1]));
            *mode = change_mode(args[1], color);

            print = true;
            *quit = true;
		}

		else if (!strcmp(args[0], "c")) { // color
			log_trace("main_page reverting mode colors.");
			*color = !(*color);
		}

		else if (!strcmp(args[0],"q")) { // quit
			print = false;
			*quit = false;
			log_info("main_page quitting program.");
			*mode = QUIT;
			
			return;
		}

		else { // input bad
			shell_error("Invalid file input.", color);
			log_error("main_page nvalid file input.");
			*quit = true;
		}

		free(line);
		free(args);
		log_debug("main_page reed 'line' and 'args'.");
	}
}