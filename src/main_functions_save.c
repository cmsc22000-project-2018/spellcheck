#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <shellstrings.h>
#include <string.h>
#include "main_functions_save.h"

/* See main_functions_save.h */
void save_corrections(char *filename, char **lines) {
	FILE *f = fopen(filename, "w");
    assert(f != NULL);

	int i = 0;

	while (lines[i] != NULL) {
		fprintf(f, "%s", lines[i]); // write lines into file
		
        i++;
	}

	fclose(f);
}

/* See main_functions_save.h */
void save_page(char *filename, char **lines, bool *quit) {
	int i = 1;
    char line[20];
    char *args = NULL;
    int verify = 0;

	while (i) {
        shell_save(false);
		shell_prompt(false);
		
        i = 0;

        verify = scanf("%s", line);
        assert (!(verify < 0)); // ensure valid input

        if (strlen(line) > 2) { // ensure that only one character is entered, otherwise cannot proceed
            shell_error("Please type in one of the indicated commands!", false);
            i = 1;
        }

        else if (!strcmp(line,"p")) {
        	shell_print(lines);
        	i = 1;
        }

        else if (!strcmp(line, "r")) {
        	*quit = true;
        }

        else if (!strcmp(line, "s")) {
			save_corrections(filename, lines);  // save to the same file destination, overwriting existing file
			*quit = false;
		}

        else if (!strcmp(line, "c")) {
            while ((args == NULL) ^ i) {    // either user returns to main page, or inputs a vaid new destination
                printf("\n\nEnter a viable file name (*.txt), or enter 'r' to return to the save page.\n\n");
                
                shell_prompt(false);
                
                verify = scanf("%s", line);
                assert (!(verify < 0));

                args = strstr(line, ".txt");
                
                if (!strcmp(line, "r")) {
                    i = 1;
                }
            }

            *quit = false;

            if (i == 0) {
                save_corrections(line, lines);  // save to different file destination
            }
		}

        else if (!strcmp(line, "q")) {
			*quit = false;
		}

        else {
			shell_error("Please type in one of the indicated commands!", false);   // wrong input
			i = 1;
		}
	}
}