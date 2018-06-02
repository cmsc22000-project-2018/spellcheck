#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "dictionary.h"
#include "word.h"
#include "main_functions_batch.h"
#include "main_functions_edit.h"
#include "main_functions_home.h"
#include "log.c/src/log.h"

/* See main_functions_batch.h */
char *edit_batch(char *line, dict_t *dict, int verbosity, int lnum) {
	char *line_copy = strdup(line);
    int max_no_suggestions = 2; //Should the user decide this?

    // Generates an empty array where the misspelled words in a line will be stored
    char **misspelled = calloc(strlen(line), sizeof(char *));
    if (misspelled == NULL) {
        fprintf(stderr,"edit_batch: calloc failed");
        exit(0);
    }

    // Generates an empty array where the underline will go
    char *underline = (char *)malloc(sizeof(char) * (strlen(line) + 1));
    if (underline == NULL) {
        fprintf(stderr,"edit_batch: calloc failed");
        exit(0);
    }
    underline[0] = '\0';

    // Identifies misspelled words and add to misspelled
    parse_string(line, dict, underline, misspelled);
    log_debug("parse_string completed");

    // Generates an empty array where suggestions will be filled
    char *suggestions[max_no_suggestions];
    suggestions[max_no_suggestions] = NULL;

    int i = 0;
    //Replacing words, printing if batch mode
    while (misspelled[i] != NULL) {
        // Generates suggestions and fills the variable 'suggestions'
        int rc = generate_suggestions(misspelled[i], dict, suggestions);
        log_info("rc value: %d", rc);

        /* 
         * If no suggestions are generated:
         *  - In verbose mode, print "No suggestions".
         *  - In quiet mode, save the word as is (without corrections).
         */
	    if (rc == EXIT_FAILURE) {
            if (verbosity == VERBOSE_MODE) {
                suggestions[0] = "No suggestions generated"; 
            }

            else {
                suggestions[0] = misspelled[i];
            }

            suggestions[1] = NULL;
        }

        // In verbose mode, edit the file and also print a replacement chart
	    if (verbosity == VERBOSE_MODE) {
            log_trace("printing chart");
	    	shell_verbose_chart(lnum, line, misspelled[i], suggestions);
        }

        log_trace("correcting line");
        correct_line(line_copy, misspelled[i], suggestions[0]);
	    i++;
	}

	return line_copy;
}

/* See main_functions_batch.h */
char **batch_mode(char *filename, dict_t *dict, bool *quit, int verbosity) {
	if (verbosity == VERBOSE_MODE) {
        printf("\n");
    }

	char **lines = parse_file(filename);
    log_debug("file parsed into char array");

	// If lineparse_file returns NULL
	if (lines == NULL) {
		shell_error("Failed to parse file.", false);
		
        *quit = false;

        log_error("file parse failure");
		return NULL;
	}

	if (verbosity == VERBOSE_MODE) {
        printf("LINE:CHAR\t\tWORD\t\t\tSUGGESTIONS\n");
    }

	int i = 0;

	while (lines[i] != NULL) {
        log_trace("starting loop for line %s", i + 1);
		lines[i] = edit_batch(lines[i], dict, verbosity, i + 1);
		i++;
	}

    *quit = false;

	return lines;
}