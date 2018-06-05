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
void help_page(bool color) {
    shell_help(color);
    shell_prompt(color);

    // Accept any input in the command line
    parse_read_line();
    log_trace("Exiting help page.");
}

/* See main_functions_home.h */
bool fileexists(const char *filename) {
    struct stat buffer;

    if (stat(filename, &buffer) == 0) {
        return true;
    }

    return false;
}

/* See main_functions_home.h */
int change_mode(char *arg, bool color) {
    log_trace("(change_mode) Mode type: %s.", arg);
    int a = atoi(arg);

    if ((a == QUIET_MODE) || (a == VERBOSE_MODE) || (a == INTERACTIVE_MODE)) {
        return a;
    }

    shell_error("(change_mode) Mode type invalid; reverting to interactive mode.", color);

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
            log_trace("(main_page) Printing the main menu.");
            shell_main_menu(*color);
        }

        shell_prompt(*color);

        // Line is being split into tokens
        line = parse_read_line();
        args = parse_split_line(line);

        // 3 inputs, or error message if no input
        if ((args == NULL) || (args[2] != NULL)) {
            log_error("(main_page) Arguments non-existent or too many arguments input.");
            shell_error("Please type in one of the indicated commands.", *color);

            print = false;
            *quit = true;
        }

        // Prints help page, then waits for user input
        else if (!strcmp(args[0], "h")) {
            help_page(*color);

            print = true;
            *quit = true;
        }

        // Checks valid file path, then exits. If not, redoes loop
        else if (!strcmp(args[0], "f")) {
            // File path checking
            if (!fileexists(args[1])) {
                log_error("(main_page) Invalid file input: File given does not exist.");
                shell_error("Please enter a valid file path for a new edit target.", *color);

                print = false;
                *quit = true;
            }

            else {
                log_debug("(main_page) File input: '%s'.", args[1]);
                strcpy(filename, args[1]);
                printf("\nFile input is now '%s'.\n", filename);

                print = false;
                *quit = false;
            }
        }

        // Dictionary name change
        else if (!strcmp(args[0], "d")) {
            // Checks file path validity for dicitonary
            if (!fileexists(args[1])) {
                log_error("(main_page) Dictionary does not exist.");
                shell_error("Please enter a valid file path for a new dictionary.", *color);

                print = false;
                *quit = true;
            }

            else {
                strcpy(dict, args[1]);
                log_info("(main_page) Dictionary file is now '%s'.",dict);
                shell_input(args[1], "dictionary file", *color);

                print = true;
                *quit = true;
            }
        }

        // Change mode
        else if (!strcmp(args[0], "m")) {
            log_info("(main_page) Mode number accepted: %d.\n", atoi(args[1]));
            *mode = change_mode(args[1], color);

            print = true;
            *quit = true;
        }

        // Color
        else if (!strcmp(args[0], "c")) {
            log_trace("(main_page) Reverting mode colors.");
            *color = !(*color);
            print = true;
        }

        // Quit
        else if (!strcmp(args[0], "q")) {
            print = false;
            *quit = false;
            log_info("(main_page) Quitting program.");
            *mode = QUIT;

            return;
        }

        // Input bad
        else {
            shell_error("Invalid command line input.", *color);
            log_error("(main_page) Invalid command line input.");
            *quit = true;
        }

        free(line);
        free(args);
        log_debug("(main_page) Freed 'line' and 'args'.");
    }
}