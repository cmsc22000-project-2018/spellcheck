#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <assert.h>
#include "log.c/src/log.h"
#include "shellstrings.h"
#include "parser.h"
#include "dictionary.h"
#include "word.h"
#include "main_functions_edit.h"
#include "main_functions_interactive.h"

/* See main_functions_interactive.h */
char *edit_interactive(char *line, dict_t *dict, int linenumber, bool returnflag, bool color) {
    log_debug("edit_interactive 'returnflag' value set to %s.", returnflag);

    char *line_copy = strdup(line);
    int max_no_suggestions = 2; // Should the user decide this?
    int length = strlen(line);

    // Generates an empty array where the misspelled words in a line will be stored
    char **misspelled = calloc(length, sizeof(char*));
    assert(misspelled != NULL);

    // Generates an empty array where the underline will go
    char *underline = (char *)malloc(sizeof(char) * (strlen(line) + 1));
    underline[0] = '\0';

    // Identifides misspelled words and add to misspelled
    parse_string(line, dict, underline, misspelled);
    log_trace("edit_interactive line parsed successfully.");
    // Add to underline function

    shell_interactive_line_print(linenumber, line_copy, underline, returnflag, color);
    log_trace("edit_interactive line printed successfully.");

    int i = 0;
    int j;
    // Replaces words according to user suggestions
    while (misspelled[i] != NULL) {
    	char** suggestions = generate_suggestions(dict, misspelled[i]);
        log_debug("edit_interactive suggestion generation returned.");

        shell_interactive_replacements(misspelled[i], suggestions, color);

        char choice[10];
        int check = 0;

        while (!check) {
    		shell_prompt(color);
        	check = scanf("%s", choice);

            log_trace("edit_interactive scanned value is %s.", choice);

        	if (!(choice[0] == 's') && !(choice[0] == 'd') && !(choice[0] == 'i')
        		&& !(isdigit(choice[0]) && (atoi(&choice[0]) <= max_no_suggestions))) {

                shell_error("Please enter a valid input.", color);
                log_error("edit_interactive nvalid input.");  

                check = 0;
        	}

            else {
        		check = 1;
        	}
        }

        if (choice[0] == 'd') {	// delete
        	correct_line(line_copy, misspelled[i], "");

            if (misspelled[i+1] != NULL) {
                /* if the line is the last line being edited, the last character is
                 * EOF, not \n. */
                printf("\n%s", line_copy);
                if (returnflag) {
                    printf("\n");
                }

                printf("%s", underline_misspelled_sentence(misspelled[i+1], line_copy, underline));
            }

        } else if (choice[0] == 's') { // skip
        	// print the edited line
            if (misspelled[i+1] != NULL) {
                /* if the line is the last line being edited, the last character is
                 * EOF, not \n. */
                printf("\n%s", line_copy);
                if (returnflag) {
                    printf("\n");
                }

                printf("%s", underline_misspelled_sentence(misspelled[i+1], line_copy, underline));
            }
        } else if (choice[0] == 'i') { // insert
			char c[50];
			char sig[10];
			int userconsent = 0;
			int insertcheck = 0;

			// Process of accepting replacment inputs
			while (!userconsent) {
				printf("\nEnter replacement: ");
			    insertcheck = scanf("%s", c);

				while (insertcheck < 0) {
                    log_trace("edit_interactive userntered value: '%s'.", c);

					shell_error("\n\nPlease enter a valid input.\n", color);
                    log_error("Invalid input.");
					shell_prompt(false);
					insertcheck = scanf("%s\n", c);
				}

				printf("Are you sure you want to replace \"%s\" with \"%s\"? [y, n] : ", misspelled[i], c);
				userconsent = scanf("%s", sig);
                log_trace("edit_interactive user entered value: '%s'.", sig);

				if (sig[0] == 'y') {
					userconsent = 1;
				}

                else {
					userconsent = 0;
				}
			}

			char *newword = strdup(c);
			printf("\nReplacing \"%s\" with \"%s\".\n", misspelled[i], newword);
			correct_line(line_copy, misspelled[i], newword); //modifies line function

            if (misspelled[i+1] != NULL) {
                /* if the line is the last line being edited, the last character is
                 * EOF, not \n. */
                printf("%s", line_copy);
                if (returnflag) {
                    printf("\n");
                }

                printf("%s", underline_misspelled_sentence(misspelled[i+1], line_copy, underline));
            }
        } else if (isdigit(choice[0]) && (atoi(&choice[0]) <= max_no_suggestions)) { // choose suggestion
        	// Replace misspelled word with chosen replacement
        	int c = atoi(&choice[0]) - 1;
        	printf("\nReplacing \"%s\" with \"%s\".\n", misspelled[i], suggestions[c]);
        	correct_line(line_copy, misspelled[i], suggestions[c]); //modifies line function

            if (misspelled[i+1] != NULL) {
            	/* if the line is the last line being edited, the last character is
            	 * EOF, not \n. */
             	printf("%s", line_copy);
             	if (returnflag) {
                    printf("\n");
                }

                printf("%s", underline_misspelled_sentence(misspelled[i+1], line_copy, underline));
            }
        }

        j = 0;
        if (suggestions != NULL) { 
            while (suggestions[j] != NULL) {
                free(suggestions[j]);
                j++;
            }
            free(suggestions);
        }

        i++; // added loop changer
    }

	return line_copy;
}

/* See main_functions_interactive.h */
char **interactive_mode(char *filename, dict_t *dict, bool *quit, bool color) {
	char **lines;
	lines = parse_file(filename);

    if (lines == NULL) {
        shell_error("Failed to parse file.", false);
        log_error("batch_mode file parse failed.");
        *quit = true;
        return NULL;
    }

    log_trace("edit_interactive file parsed successfully.");

	// step through phases
	int i = 0;
	bool flag = false;
	int linenumber;

	while (lines[i] != NULL) {
        log_debug("edit_interactive starting to edit line %d", i + 1);
		linenumber = i + 1;
		
        if (lines[i+1] == NULL) {
            flag = true;	// last line
        }

		lines[i] = edit_interactive(lines[i], dict, linenumber, flag, color);
		
        i++;
	}

    log_trace("edit_interactive editing finished successfully, exiting the interactive mode.");
    *quit = false;
	return lines;
}