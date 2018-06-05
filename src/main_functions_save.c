#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "main_functions_save.h"
#include "log.c/src/log.h"

/* See main_functions_save.h */
void save_corrections(char *filename, char **lines) {
    log_trace("(save_corrections) Opening save file destination '%s'.", filename);
    FILE *f = fopen(filename, "w");
    assert(f != NULL);

    int i = 0;

    while (lines[i] != NULL) {
        log_trace("Writing line into file '%s'.", lines[i]);
        // Writes lines into file
        fprintf(f, "%s", lines[i]);

        i++;
    }

    log_trace("(save_corrections) Closing save file destination '%s'.", filename);
    fclose(f);
}

/* See main_functions_save.h */
void save_page(char *filename, char **lines, bool *quit, bool color) {
    int i = 1;
    char line[10];
    char *args = NULL;
    char **inputs = NULL;
    char *savefilename = NULL;
    int verify = 0;

    while (i) {
        shell_save_message(color);
        shell_prompt(color);

        i = 0;

        verify = scanf("%s", line);
        // Ensures valid input
        assert (!(verify < 0));

        // Ensures that only one character is entered, otherwise cannot proceed
        if (strlen(line) > 2) {
            log_debug("Parsing command input.");

            inputs = parse_split_line(line);
            strcpy(line,inputs[0]);
            args = strdup(inputs[1]);
            printf("Arguments: %s\n", args);
        }

        if (!strcmp(line,"p")) {
            shell_print(lines);
            log_info("Lines printed successfully.");
            i = 1;
        }

        else if (!strcmp(line, "r")) {
            log_info("Returning to previous page.");
            *quit = true;
        }

        else if (!strcmp(line, "s")) {
            log_info("Saving modifications to existing file.");
            // Saves to the same file destination, overwriting existing file
            save_corrections(filename, lines);
            *quit = false;
        }

        else if (!strcmp(line, "c")) {
            log_info("Saving modifications to new file.");

            // If a file was entered for saving, then stores that file
            if (args != NULL) {
                char *testinput = NULL;
                testinput = strdup(args);
                testinput = strstr(testinput, ".txt\0");
                
                if (testinput == NULL) {
                    args = NULL;
                }

                else {
                    savefilename = strdup(args);
                }
            }

            // Either user returns to main page, or inputs a valid new destination
            while ((args == NULL) ^ i) {
                printf("\n\nEnter a viable file name (*.txt), or enter 'r' to return to the save page.\n\n");

                shell_prompt(color);

                verify = scanf("%s", line);
                assert (!(verify < 0));

                log_debug("File entered is '%s'.", line);
                args = strstr(line, ".txt\0");

                if (!strcmp(line, "r")) {
                    i = 1;
                }

                if (args != NULL) {
                    savefilename = strdup(line);
                }
            }

            *quit = false;

            if (i == 0) {
                log_trace("Entering save_corrections().");
                // Saves to different file destination
                save_corrections(savefilename, lines);
            }
        }

        else if (!strcmp(line, "q")) {
            log_info("Quitting program and discarding any unsaved changes.");
            *quit = false;
        }

        // Bad input
        else {
            shell_error("Please type in one of the indicated commands.", color);
            log_error("Invalid command input.");
            i = 1;
        }
    }
}