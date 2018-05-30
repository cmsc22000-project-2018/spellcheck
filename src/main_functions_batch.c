#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "dictionary.h"
#include "word.h"
#include "main_functions_edit.h"
#include "main_functions_batch.h"
#include "main_functions_home.h"

/* See main_functions_batch.h */
char* edit_batch(char* line, dict_t* dict, int verbosity, int lnum)
{
	char *line_copy = strdup(line);
    int max_no_suggestions = 2; //should the user decide this?
    int length = strlen(line);
    char **misspelled; //generates an empty array where the misspelled words in a line will be stored

    misspelled = calloc(length, sizeof(char*));
    if (misspelled == NULL) {
    	fprintf(stderr,"edit_interactive: calloc failed");
    	exit(0);
    }

    char *underline = (char *)malloc(sizeof(char) * (strlen(line) + 1)); //generate an empty array where the underline will go
    underline[0] = '\0';

    parse_string(line, dict, underline, misspelled); //identify misspelled words and add to misspelled
    char *suggestions[max_no_suggestions]; //generates empty array where suggestions will be filled
    suggestions[max_no_suggestions] = NULL;

    int i = 0;
    //replacing words, printing out if batch mode
    while (misspelled[i] != NULL) {
        int rc = generate_suggestions(misspelled[i], dict, suggestions);

        /* if no suggestions are generated,
         * in verbose - print "no suggestions"
         * in quiet - save the word as is, without corrections
         */
	    if (rc == EXIT_FAILURE) {
            if (verbosity == VERBOSE_MODE) {
                suggestions[0] = "No suggestions generated"; 
            } else {
                suggestions[0] = misspelled[i];
            }

            suggestions[1] = NULL;
        }

    	if (verbosity == QUIET_MODE) {   // in quiet mode, edit the file
            correct_line(line_copy, misspelled[i], suggestions[0]);
        }

	    if (verbosity == VERBOSE_MODE) { // in verbose mode, print out lines
	    	shell_verbose_chart(lnum, misspelled[i], suggestions);
        }

	    i++;
	}

	return line_copy;
}

/* See main_functions_batch.h */
char** batch_mode(char* filename, dict_t* dict, bool* quit, int verbosity)
{
	if (verbosity == VERBOSE_MODE) printf("\n");

	char** lines;
	lines = parse_file(filename);
	// if lineparse_file returns NULL
	if (lines == NULL) {
		shell_error("file parsing error: check txt file");
		*quit = false;
		return NULL;
	}

	if (verbosity == VERBOSE_MODE) printf("LINE\t\t\tWORD\t\t\tSUGGESTIONS\n");

	int i=0;
	while (lines[i] != NULL) {
		lines[i] = edit_batch(lines[i], dict, verbosity, i + 1);
		i++;
	}

    *quit = false;
	return lines;
}
