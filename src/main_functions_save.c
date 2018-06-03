#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <shellstrings.h>
#include <string.h>
#include "parser.h"
#include "main_functions_save.h"
#include "log.c/src/log.h"

/* See main_functions_save.h */
void save_corrections(char *filename, char **lines) {
    log_trace("save_corrections opening save file destination '%s'.", filename);
	FILE *f = fopen(filename, "w");
    assert(f != NULL);

	int i = 0;

	while (lines[i] != NULL) {
        log_trace("Writing line into file '%s'.", lines[i]);
		fprintf(f, "%s", lines[i]); // write lines into file
		
        i++;
	}

    log_trace("save_corrections closing save file destination '%s'.", filename);
	fclose(f);
}

/* See main_functions_save.h */
void save_page(char *filename, char **lines, bool *quit, bool* color) {
	int i = 1;
    char line[10];
    char *args = NULL;
    char** inputs = NULL;
    char* savefilename = NULL;
    int verify = 0;

	while (i) {
        shell_save(color);
		shell_prompt(color);
		
        i = 0;

        verify = scanf("%s", line);
        assert (!(verify < 0)); // ensure valid input

        if (strlen(line) > 2) { // ensure that only one character is entered, otherwise cannot proceed
            log_debug("parsing command input.");

            inputs = parse_split_line(line);
            strcpy(line,inputs[0]);
            args = strdup(inputs[1]);
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
            save_corrections(filename, lines);  // save to the same file destination, overwriting existing file
			*quit = false;
		}

        else if (!strcmp(line, "c")) {
            log_info("Saving modifications to new file.");

            // If a file was entered for saving, then store that file
            if (args != NULL) {
                char* testinput = strdup(testinput);
                testinput = strstr(testinput, ".txt\0");
                if (testinput == NULL) {
                    args = NULL;
                } else {
                    savefilename = strdup(args);
                }
            }
            
            while ((args == NULL) ^ i) {    // either user returns to main page, or inputs a vaid new destination
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
                save_corrections(savefilename, lines);  // save to different file destination
            }
		}

        else if (!strcmp(line, "q")) {
            log_info("Quitting program and discarding any unsaved changes.");
			*quit = false;
		}

        else {
			shell_error("Please type in one of the indicated commands.", color);   // wrong input
            log_error("Invalid command input.");
			i = 1;
		}
	}
}