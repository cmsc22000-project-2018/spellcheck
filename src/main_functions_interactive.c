#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <assert.h>
#include "log.c/src/log.h"
#include "shellstrings.h"
#include "parser.h"
#include "dictionary.h"
#include "word.h"
#include "main_functions_edit.h"
#include "main_functions_interactive.h"

/* See main_functions_interactive.h */
char *edit_interactive(char *line, dict_t *dict, int linenumber, int nsug, bool returnflag, bool color) {
    log_debug("(edit_interactive) 'returnflag' value set to %s.", returnflag);

    char *line_copy = strdup(line);
    int max_edits = 2;

    int length = strlen(line);
    // Generates an empty array where the misspelled words in a line will be stored
    char **misspelled = calloc(length, sizeof(char*));
    assert(misspelled != NULL);

    // Generates an empty array where the underline will go
    char *underline = (char *)malloc(sizeof(char) * (strlen(line) + 1));
    underline[0] = '\0';

    // Identifies misspelled words and add to misspelled
    parse_string(line, dict, underline, misspelled);
    log_trace("(edit_interactive) Line parsed successfully.");

    shell_interactive_line_print(linenumber, line_copy, underline, returnflag, color);
    log_trace("(edit_interactive) Line printed successfully.");

    int i = 0;
    int j;
    
    // Replaces words according to user suggestions
    while (misspelled[i] != NULL) {
    	char **suggestions = generate_suggestions(dict, misspelled[i], max_edits, nsug);
        log_debug("(edit_interactive) Suggestion generation returned successfully.");

        shell_interactive_replacements(misspelled[i], suggestions, color);

        char choice[10];
        int check = 0;

        while (!check) {
            shell_prompt(color);
            check = scanf("%s", choice);

            log_trace("(edit_interactive) Scanned value is %s.", choice);

            if (!(choice[0] == 's') && !(choice[0] == 'd') && !(choice[0] == 'i')
                && !(isdigit(choice[0]) && (atoi(&choice[0]) <= nsug))) {
                shell_error("Please enter a valid input.", color);

                check = 0;
            }

            else {
                check = 1;
            }
        }

        // Delete
        if (choice[0] == 'd') {
            correct_line(line_copy, misspelled[i], "");

            if (misspelled[i+1] != NULL) {
                /* 
                 * If the line is the last line being edited,
                 * the last character is EOF, not \n.
                 */
                printf("\n%s", line_copy);
                
                if (returnflag) {
                    printf("\n");
                }

                printf("%s", underline_misspelled_sentence(misspelled[i + 1], line_copy, underline));
            }
        }

        // Skip
        else if (choice[0] == 's') {
            // Prints the edited line
            if (misspelled[i + 1] != NULL) {
                /* if the line is the last line being edited,
                 * the last character is EOF, not \n.
                 */
                printf("\n%s", line_copy);
                
                if (returnflag) {
                    printf("\n");
                }

                printf("%s", underline_misspelled_sentence(misspelled[i + 1], line_copy, underline));
            }
        }

        // Insert
        else if (choice[0] == 'i') {
            char c[50];
            char sig[10];
            int userconsent = 0;
            int insertcheck = 0;

            // Process of accepting replacment inputs
            while (!userconsent) {
                printf("\nEnter replacement: ");
                insertcheck = scanf("%s", c);

                while (insertcheck < 0) {
                    log_trace("(edit_interactive) User entered value: '%s'.", c);

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
            correct_line(line_copy, misspelled[i], newword);

            if (misspelled[i + 1] != NULL) {
                /* If the line is the last line being edited,
                 * the last character is EOF, not \n.
                 */
                printf("%s", line_copy);
                
                if (returnflag) {
                    printf("\n");
                }

                printf("%s", underline_misspelled_sentence(misspelled[i + 1], line_copy, underline));
            } 
        }

        // Choose suggestion
        else if (isdigit(choice[0]) && (atoi(&choice[0]) <= nsug)) {
            // Replaces misspelled word with chosen replacement
            int c = atoi(&choice[0]) - 1;
            printf("\nReplacing \"%s\" with \"%s\".\n", misspelled[i], suggestions[c]);
            correct_line(line_copy, misspelled[i], suggestions[c]);

            if (misspelled[i+1] != NULL) {
                /* If the line is the last line being edited,
                 * the last character is EOF, not \n.
                 */
                printf("%s", line_copy);
                
                if (returnflag) {
                    printf("\n");
                }

                printf("%s", underline_misspelled_sentence(misspelled[i + 1], line_copy, underline));
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

        i++;
    }

    return line_copy;
}

/* See main_functions_interactive.h */
int interactive_nsug_input(bool color) {
    int input;
    int check;

    printf("Enter the maximum number of suggestions to generate: ");

    while (1) {
        shell_prompt(color);

        check = scanf("%d", &input);
        log_trace("input is %d", input);

        if (check) {
            return input;
        }

        else {
            shell_error("Please enter a valid input.", color);
        }
    }
}

/* See main_functions_interactive.h */
char **interactive_mode(char *filename, dict_t *dict, bool *quit, bool color) {
    char **lines;
    lines = parse_file(filename);

    if (lines == NULL) {
        shell_error("Failed to parse file.", false);
        log_error("(batch_mode) File parse failed.");
        *quit = true;
        return NULL;
    }

    log_trace("(edit_interactive) File parsed successfully.");

    int nsug = interactive_nsug_input(color);

	// Steps through phases
	int i = 0;
	bool flag = false;
	int linenumber;

    while (lines[i] != NULL) {
        log_debug("(edit_interactive) Starting to edit line %d", i + 1);
        linenumber = i + 1;
        
        // Last line
        if (lines[i + 1] == NULL) {
            flag = true;
        }

		lines[i] = edit_interactive(lines[i], dict, linenumber, nsug, flag, color);
		
        i++;
    }

    log_trace("(edit_interactive) Editing finished successfully, exiting the interactive mode.");
    *quit = false;
    return lines;
}