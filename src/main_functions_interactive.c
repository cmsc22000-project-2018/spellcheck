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
char *edit_interactive(char *line, dict_t *dict, int linenumber, bool returnflag, bool* color) {
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
    // Add to underline function

    shell_interactive_line_print(linenumber, line_copy, underline, returnflag, color);

    // Generates an empty array where suggestions will be filled
    char *suggestions[max_no_suggestions];
    suggestions[max_no_suggestions] = NULL;

    int i = 0;

    // Replaces words according to user suggestions
    while (misspelled[i] != NULL) {
    	int rc = generate_suggestions(misspelled[i], dict, suggestions);

        shell_interactive_replacements(misspelled[i], suggestions, rc, color);

        char choice[10];
        int check = 0;

        while (!check) {
    		shell_prompt(color);
        	check = scanf("%s", choice);

        	if (!(choice[0] == 's') && !(choice[0] == 'd') && !(choice[0] == 'i')
        		&& !(isdigit(choice[0]) && (atoi(&choice[0]) <= max_no_suggestions))) {

                shell_error("Please enter a valid input", color);
               
                check = 0;
        	}

            else {
        		check = 1;
        	}
        }

        if (choice[0] == 'd') {	// delete
        	correct_line(line_copy, misspelled[i], "");

         	printf("%s", line_copy);
        	
            /* 
             * If the line is the last line being edited,
             * the last character is EOF, not \n.
             */

        	if (returnflag) {
                printf("\n");
            }

         	printf("%s", underline_misspelled_sentence(misspelled, line_copy, underline));
        }

        else if (choice[0] == 's') { // skip
        	// print the edited line
        	printf("%s", line_copy);
        	/* if the line is the last line being edited, the last character is
        	 * EOF, not \n. */
        	if (returnflag) {
                printf("\n");
            }

         	printf("%s", underline_misspelled_sentence(misspelled, line_copy, underline));
        }

        else if (choice[0] == 'i') { // insert
			char c[50];
			char sig[10];
			int userconsent = 0;
			int insertcheck = 0;

			// Process of accepting replacment inputs
			while (!userconsent) {
				printf("\nEnter replacement: ");
			    insertcheck = scanf("%s", c);

				while (insertcheck < 0) {
					shell_error("\n\nPlease enter a valid input!\n", color);
					shell_prompt(false);
					insertcheck = scanf("%s\n", c);
				}

				printf("Are you sure you wish to replace \"%s\" with \"%s\"? [y, n] : ", misspelled[i], c);
				userconsent = scanf("%s", sig);

				if (sig[0] == 'y') {
					userconsent = 1;
				}

                else {
					userconsent = 0;
				}
			}

			char *newword = strdup(c);
			printf("\nReplacing \"%s\" with \"%s\". \n", misspelled[i], newword);
			correct_line(line_copy, misspelled[i], newword); //modifies line function

         	printf("%s", line_copy);

        	/*
             *if the line is the last line being edited,
             * the last character is EOF, not \n.
             */
         	if (returnflag) {
                printf("\n");
            }

         	printf("%s", underline_misspelled_sentence(misspelled, line_copy, underline));
        } 

        else if (isdigit(choice[0]) && (atoi(&choice[0]) <= max_no_suggestions)) { // choose suggestion
        	// Replace misspelled word with chosen replacement
        	int c = atoi(&choice[0]) - 1;
        	printf("\nReplacing %s with %s.\n\n", misspelled[i], suggestions[c]);
        	correct_line(line_copy, misspelled[i], suggestions[c]); //modifies line function

        	/* if the line is the last line being edited, the last character is
        	 * EOF, not \n. */
         	printf("%s", line_copy);
         	if (returnflag) {
                printf("\n");
            }

         	printf("%s", underline_misspelled_sentence(misspelled, line_copy, underline));
        }

        i++;	// added loop changer
    }

	return line_copy;
}

/* See main_functions_interactive.h */
char **interactive_mode(char *filename, dict_t *dict, bool *quit, bool* color) {
	char **lines;
	lines = parse_file(filename);

	// step through phases
	int i = 0;
	int flag = false;
	int linenumber;

	while (lines[i] != NULL) {
		linenumber = i+1;
		
        if (lines[i+1] == NULL) {
            flag = true;	// last line
        }

		lines[i] = edit_interactive(lines[i], dict, linenumber, flag, color);
		
        i++;
	}

    *quit = true;
	return lines;
}